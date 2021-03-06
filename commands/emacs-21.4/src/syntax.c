/* GNU Emacs routines to deal with syntax tables; also word and list parsing.
   Copyright (C) 1985, 87, 93, 94, 95, 97, 1998, 1999 Free Software Foundation, Inc.

This file is part of GNU Emacs.

GNU Emacs is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU Emacs is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Emacs; see the file COPYING.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */


#include <config.h>
#include <ctype.h>
#include "lisp.h"
#include "commands.h"
#include "buffer.h"
#include "charset.h"

/* Make syntax table lookup grant data in gl_state.  */
#define SYNTAX_ENTRY_VIA_PROPERTY

#include "syntax.h"
#include "intervals.h"

/* We use these constants in place for comment-style and
   string-ender-char to distinguish  comments/strings started by
   comment_fence and string_fence codes.  */

#define ST_COMMENT_STYLE (256 + 1)
#define ST_STRING_STYLE (256 + 2)
#include "category.h"

Lisp_Object Qsyntax_table_p, Qsyntax_table, Qscan_error;

int words_include_escapes;
int parse_sexp_lookup_properties;

/* Nonzero means `scan-sexps' treat all multibyte characters as symbol.  */
int multibyte_syntax_as_symbol;

/* Used as a temporary in SYNTAX_ENTRY and other macros in syntax.h,
   if not compiled with GCC.  No need to mark it, since it is used
   only very temporarily.  */
Lisp_Object syntax_temp;

/* Non-zero means an open parenthesis in column 0 is always considered
   to be the start of a defun.  Zero means an open parenthesis in
   column 0 has no special meaning.  */

int open_paren_in_column_0_is_defun_start;

/* This is the internal form of the parse state used in parse-partial-sexp.  */

struct lisp_parse_state
  {
    int depth;		/* Depth at end of parsing.  */
    int instring;	/* -1 if not within string, else desired terminator.  */
    int incomment;	/* -1 if in unnestable comment else comment nesting */
    int comstyle;	/* comment style a=0, or b=1, or ST_COMMENT_STYLE.  */
    int quoted;		/* Nonzero if just after an escape char at end of parsing */
    int thislevelstart;	/* Char number of most recent start-of-expression at current level */
    int prevlevelstart; /* Char number of start of containing expression */
    int location;	/* Char number at which parsing stopped.  */
    int mindepth;	/* Minimum depth seen while scanning.  */
    int comstr_start;	/* Position just after last comment/string starter.  */
    Lisp_Object levelstarts;	/* Char numbers of starts-of-expression
				   of levels (starting from outermost).  */
  };

/* These variables are a cache for finding the start of a defun.
   find_start_pos is the place for which the defun start was found.
   find_start_value is the defun start position found for it.
   find_start_value_byte is the corresponding byte position.
   find_start_buffer is the buffer it was found in.
   find_start_begv is the BEGV value when it was found.
   find_start_modiff is the value of MODIFF when it was found.  */

static int find_start_pos;
static int find_start_value;
static int find_start_value_byte;
static struct buffer *find_start_buffer;
static int find_start_begv;
static int find_start_modiff;


static int find_defun_start P_ ((int, int));
static int back_comment P_ ((int, int, int, int, int, int *, int *));
static int char_quoted P_ ((int, int));
static Lisp_Object skip_chars P_ ((int, int, Lisp_Object, Lisp_Object));
static Lisp_Object scan_lists P_ ((int, int, int, int));
static void scan_sexps_forward P_ ((struct lisp_parse_state *,
				    int, int, int, int,
				    int, Lisp_Object, int));


struct gl_state_s gl_state;		/* Global state of syntax parser.  */

INTERVAL interval_of ();
#define INTERVALS_AT_ONCE 10		/* 1 + max-number of intervals
					   to scan to property-change.  */

/* Update gl_state to an appropriate interval which contains CHARPOS.  The
   sign of COUNT give the relative position of CHARPOS wrt the previously
   valid interval.  If INIT, only [be]_property fields of gl_state are
   valid at start, the rest is filled basing on OBJECT.

   `gl_state.*_i' are the intervals, and CHARPOS is further in the search
   direction than the intervals - or in an interval.  We update the
   current syntax-table basing on the property of this interval, and
   update the interval to start further than CHARPOS - or be
   NULL_INTERVAL.  We also update lim_property to be the next value of
   charpos to call this subroutine again - or be before/after the
   start/end of OBJECT.  */

void
update_syntax_table (charpos, count, init, object)
     int charpos, count, init;
     Lisp_Object object;
{
  Lisp_Object tmp_table;
  int cnt = 0, invalidate = 1;
  INTERVAL i, oldi;

  if (init)
    {
      gl_state.start = gl_state.b_property;
      gl_state.stop = gl_state.e_property;
      gl_state.forward_i = interval_of (charpos, object);
      i = gl_state.backward_i = gl_state.forward_i;
      gl_state.left_ok = gl_state.right_ok = 1;
      invalidate = 0;
      if (NULL_INTERVAL_P (i))
	return;
      /* interval_of updates only ->position of the return value, so
	 update the parents manually to speed up update_interval.  */
      while (!NULL_PARENT (i)) 
	{
	  if (AM_RIGHT_CHILD (i))
	    INTERVAL_PARENT (i)->position = i->position
	      - LEFT_TOTAL_LENGTH (i) + TOTAL_LENGTH (i) /* right end */
	      - TOTAL_LENGTH (INTERVAL_PARENT (i))
	      + LEFT_TOTAL_LENGTH (INTERVAL_PARENT (i));
	  else
	    INTERVAL_PARENT (i)->position = i->position - LEFT_TOTAL_LENGTH (i)
	      + TOTAL_LENGTH (i);
	  i = INTERVAL_PARENT (i);
	}
      i = gl_state.forward_i;
      gl_state.b_property = i->position - 1 - gl_state.offset;
      gl_state.e_property = INTERVAL_LAST_POS (i) - gl_state.offset;
      goto update;
    }
  oldi = i = count > 0 ? gl_state.forward_i : gl_state.backward_i;

  /* We are guaranteed to be called with CHARPOS either in i,
     or further off.  */
  if (NULL_INTERVAL_P (i))
    error ("Error in syntax_table logic for to-the-end intervals");
  else if (charpos < i->position)		/* Move left.  */
    {
      if (count > 0)
	error ("Error in syntax_table logic for intervals <-");
      /* Update the interval.  */
      i = update_interval (i, charpos);
      if (!gl_state.left_ok || oldi->position != INTERVAL_LAST_POS (i))
	{
	  invalidate = 0;
	  gl_state.right_ok = 1;	/* Invalidate the other end.  */
	  gl_state.forward_i = i;
	  gl_state.e_property = INTERVAL_LAST_POS (i) - gl_state.offset;
	}
    }
  else if (charpos >= INTERVAL_LAST_POS (i)) /* Move right.  */
    {
      if (count < 0)
	error ("Error in syntax_table logic for intervals ->");
      /* Update the interval.  */
      i = update_interval (i, charpos);
      if (!gl_state.right_ok || i->position != INTERVAL_LAST_POS (oldi))
	{
	  invalidate = 0;
	  gl_state.left_ok = 1;		/* Invalidate the other end.  */
	  gl_state.backward_i = i;
	  gl_state.b_property = i->position - 1 - gl_state.offset;
	}
    }
  else if (count > 0 ? gl_state.right_ok : gl_state.left_ok)
    {
      /* We do not need to recalculate tmp_table.  */
      tmp_table = gl_state.old_prop;
    }

  update:
  tmp_table = textget (i->plist, Qsyntax_table);

  if (invalidate)
    invalidate = !EQ (tmp_table, gl_state.old_prop); /* Need to invalidate? */
      
  if (invalidate)		/* Did not get to adjacent interval.  */
    {				/* with the same table => */
				/* invalidate the old range.  */
      if (count > 0)
	{
	  gl_state.backward_i = i;
	  gl_state.left_ok = 1;		/* Invalidate the other end.  */
	  gl_state.b_property = i->position - 1 - gl_state.offset;
	} 
      else 
	{
	  gl_state.forward_i = i;	
	  gl_state.right_ok = 1;	/* Invalidate the other end.  */
	  gl_state.e_property = INTERVAL_LAST_POS (i) - gl_state.offset;
	}
    }

  gl_state.current_syntax_table = tmp_table;
  gl_state.old_prop = tmp_table;
  if (EQ (Fsyntax_table_p (tmp_table), Qt))
    {
      gl_state.use_global = 0;
    } 
  else if (CONSP (tmp_table))
    {
      gl_state.use_global = 1;
      gl_state.global_code = tmp_table;
    }
  else 
    {
      gl_state.use_global = 0;
      gl_state.current_syntax_table = current_buffer->syntax_table;
    }

  while (!NULL_INTERVAL_P (i))
    {
      if (cnt && !EQ (tmp_table, textget (i->plist, Qsyntax_table)))
	{
	  if (count > 0)
	    gl_state.right_ok = 0;
	  else 
	    gl_state.left_ok = 0;
	  break;	  
	}
      else if (cnt == INTERVALS_AT_ONCE) 
	{
	  if (count > 0)
	    gl_state.right_ok = 1;
	  else 
	    gl_state.left_ok = 1;
	  break;
	}
      cnt++;
      i = count > 0 ? next_interval (i) : previous_interval (i);
    }
  if (NULL_INTERVAL_P (i)) 
    {					/* This property goes to the end.  */
      if (count > 0)
	gl_state.e_property = gl_state.stop;
      else
	gl_state.b_property = gl_state.start;
    } 
  else 
    {
      if (count > 0) 
	{
	  gl_state.e_property = i->position - gl_state.offset;
	  gl_state.forward_i = i;
	}
      else 
	{
	  gl_state.b_property = i->position + LENGTH (i) - 1 - gl_state.offset;
	  gl_state.backward_i = i;
	}
    }    
}

/* Returns TRUE if char at CHARPOS is quoted.
   Global syntax-table data should be set up already to be good at CHARPOS
   or after.  On return global syntax data is good for lookup at CHARPOS. */

static int
char_quoted (charpos, bytepos)
     register int charpos, bytepos;
{
  register enum syntaxcode code;
  register int beg = BEGV;
  register int quoted = 0;
  int orig = charpos;

  DEC_BOTH (charpos, bytepos);

  while (bytepos >= beg)
    {
      UPDATE_SYNTAX_TABLE_BACKWARD (charpos);
      code = SYNTAX (FETCH_CHAR (bytepos));
      if (! (code == Scharquote || code == Sescape))
	break;

      DEC_BOTH (charpos, bytepos);
      quoted = !quoted;
    }

  UPDATE_SYNTAX_TABLE (orig);
  return quoted;
}

/* Return the bytepos one character after BYTEPOS.
   We assume that BYTEPOS is not at the end of the buffer.  */

INLINE int
inc_bytepos (bytepos)
     int bytepos;
{
  if (NILP (current_buffer->enable_multibyte_characters))
    return bytepos + 1;

  INC_POS (bytepos);
  return bytepos;
}

/* Return the bytepos one character before BYTEPOS.
   We assume that BYTEPOS is not at the start of the buffer.  */

INLINE int
dec_bytepos (bytepos)
     int bytepos;
{
  if (NILP (current_buffer->enable_multibyte_characters))
    return bytepos - 1;

  DEC_POS (bytepos);
  return bytepos;
}

/* Return a defun-start position before before POS and not too far before.
   It should be the last one before POS, or nearly the last.

   When open_paren_in_column_0_is_defun_start is nonzero,
   the beginning of every line is treated as a defun-start.

   We record the information about where the scan started
   and what its result was, so that another call in the same area
   can return the same value very quickly.

   There is no promise at which position the global syntax data is
   valid on return from the subroutine, so the caller should explicitly
   update the global data.  */

static int
find_defun_start (pos, pos_byte)
     int pos, pos_byte;
{
  int opoint = PT, opoint_byte = PT_BYTE;

  /* Use previous finding, if it's valid and applies to this inquiry.  */
  if (current_buffer == find_start_buffer
      /* Reuse the defun-start even if POS is a little farther on.
	 POS might be in the next defun, but that's ok.
	 Our value may not be the best possible, but will still be usable.  */
      && pos <= find_start_pos + 1000
      && pos >= find_start_value
      && BEGV == find_start_begv
      && MODIFF == find_start_modiff)
    return find_start_value;

  /* Back up to start of line.  */
  scan_newline (pos, pos_byte, BEGV, BEGV_BYTE, -1, 1);

  /* We optimize syntax-table lookup for rare updates.  Thus we accept
     only those `^\s(' which are good in global _and_ text-property
     syntax-tables.  */
  gl_state.current_syntax_table = current_buffer->syntax_table;
  gl_state.use_global = 0;
  if (open_paren_in_column_0_is_defun_start)
    {
      while (PT > BEGV)
	{
	  /* Open-paren at start of line means we may have found our
	     defun-start.  */
	  if (SYNTAX (FETCH_CHAR (PT_BYTE)) == Sopen)
	    {
	      SETUP_SYNTAX_TABLE (PT + 1, -1);	/* Try again... */
	      if (SYNTAX (FETCH_CHAR (PT_BYTE)) == Sopen)
		break;
	      /* Now fallback to the default value.  */
	      gl_state.current_syntax_table = current_buffer->syntax_table;
	      gl_state.use_global = 0;
	    }
	  /* Move to beg of previous line.  */
	  scan_newline (PT, PT_BYTE, BEGV, BEGV_BYTE, -2, 1);
	}
    }

  /* Record what we found, for the next try.  */
  find_start_value = PT;
  find_start_value_byte = PT_BYTE;
  find_start_buffer = current_buffer;
  find_start_modiff = MODIFF;
  find_start_begv = BEGV;
  find_start_pos = pos;

  TEMP_SET_PT_BOTH (opoint, opoint_byte);

  return find_start_value;
}

/* Return the SYNTAX_COMEND_FIRST of the character before POS, POS_BYTE.  */

static int
prev_char_comend_first (pos, pos_byte)
     int pos, pos_byte;
{
  int c, val;

  DEC_BOTH (pos, pos_byte);
  UPDATE_SYNTAX_TABLE_BACKWARD (pos);
  c = FETCH_CHAR (pos_byte);
  val = SYNTAX_COMEND_FIRST (c);
  UPDATE_SYNTAX_TABLE_FORWARD (pos + 1);
  return val;
}

/* Return the SYNTAX_COMSTART_FIRST of the character before POS, POS_BYTE.  */

/* static int
 * prev_char_comstart_first (pos, pos_byte)
 *      int pos, pos_byte;
 * {
 *   int c, val;
 * 
 *   DEC_BOTH (pos, pos_byte);
 *   UPDATE_SYNTAX_TABLE_BACKWARD (pos);
 *   c = FETCH_CHAR (pos_byte);
 *   val = SYNTAX_COMSTART_FIRST (c);
 *   UPDATE_SYNTAX_TABLE_FORWARD (pos + 1);
 *   return val;
 * } */

/* Checks whether charpos FROM is at the end of a comment.
   FROM_BYTE is the bytepos corresponding to FROM.
   Do not move back before STOP.

   Return a positive value if we find a comment ending at FROM/FROM_BYTE;
   return -1 otherwise.

   If successful, store the charpos of the comment's beginning
   into *CHARPOS_PTR, and the bytepos into *BYTEPOS_PTR.

   Global syntax data remains valid for backward search starting at
   the returned value (or at FROM, if the search was not successful).  */

static int
back_comment (from, from_byte, stop, comnested, comstyle, charpos_ptr, bytepos_ptr)
     int from, from_byte, stop;
     int comnested, comstyle;
     int *charpos_ptr, *bytepos_ptr;
{
  /* Look back, counting the parity of string-quotes,
     and recording the comment-starters seen.
     When we reach a safe place, assume that's not in a string;
     then step the main scan to the earliest comment-starter seen
     an even number of string quotes away from the safe place.

     OFROM[I] is position of the earliest comment-starter seen
     which is I+2X quotes from the comment-end.
     PARITY is current parity of quotes from the comment end.  */
  int string_style = -1;	/* Presumed outside of any string. */
  int string_lossage = 0;
  /* Not a real lossage: indicates that we have passed a matching comment
     starter plus an non-matching comment-ender, meaning that any matching
     comment-starter we might see later could be a false positive (hidden
     inside another comment).
     Test case:  { a (* b } c (* d *) */
  int comment_lossage = 0;
  int comment_end = from;
  int comment_end_byte = from_byte;
  int comstart_pos = 0;
  int comstart_byte;
  /* Place where the containing defun starts,
     or 0 if we didn't come across it yet.  */
  int defun_start = 0;
  int defun_start_byte = 0;
  register enum syntaxcode code;
  int nesting = 1;		/* current comment nesting */
  int c;
  int syntax = 0;

  /* FIXME: A }} comment-ender style leads to incorrect behavior
     in the case of {{ c }}} because we ignore the last two chars which are
     assumed to be comment-enders although they aren't.  */

  /* At beginning of range to scan, we're outside of strings;
     that determines quote parity to the comment-end.  */
  while (from != stop)
    {
      int temp_byte, prev_syntax;
      int com2start, com2end;

      /* Move back and examine a character.  */
      DEC_BOTH (from, from_byte);
      UPDATE_SYNTAX_TABLE_BACKWARD (from);

      prev_syntax = syntax;
      c = FETCH_CHAR (from_byte);
      syntax = SYNTAX_WITH_FLAGS (c);
      code = SYNTAX (c);

      /* Check for 2-char comment markers.  */
      com2start = (SYNTAX_FLAGS_COMSTART_FIRST (syntax)
		   && SYNTAX_FLAGS_COMSTART_SECOND (prev_syntax)
		   && comstyle == SYNTAX_FLAGS_COMMENT_STYLE (prev_syntax)
		   && (SYNTAX_FLAGS_COMMENT_NESTED (prev_syntax)
		       || SYNTAX_FLAGS_COMMENT_NESTED (syntax)) == comnested);
      com2end = (SYNTAX_FLAGS_COMEND_FIRST (syntax)
		 && SYNTAX_FLAGS_COMEND_SECOND (prev_syntax));

      /* Nasty cases with overlapping 2-char comment markers:
	 - snmp-mode: -- c -- foo -- c --
	              --- c --
		      ------ c --
	 - c-mode:    *||*
		      |* *|* *|
		      |*| |* |*|
		      ///   */

      /* If a 2-char comment sequence partly overlaps with another,
	 we don't try to be clever.  */
      if (from > stop && (com2end || com2start))
	{
	  int next = from, next_byte = from_byte, next_c, next_syntax;
	  DEC_BOTH (next, next_byte);
	  UPDATE_SYNTAX_TABLE_BACKWARD (next);
	  next_c = FETCH_CHAR (next_byte);
	  next_syntax = SYNTAX_WITH_FLAGS (next_c);
	  if (((com2start || comnested)
	       && SYNTAX_FLAGS_COMEND_SECOND (syntax)
	       && SYNTAX_FLAGS_COMEND_FIRST (next_syntax))
	      || ((com2end || comnested)
		  && SYNTAX_FLAGS_COMSTART_SECOND (syntax)
		  && comstyle == SYNTAX_FLAGS_COMMENT_STYLE (syntax)
		  && SYNTAX_FLAGS_COMSTART_FIRST (next_syntax)))
	    goto lossage;
	  /* UPDATE_SYNTAX_TABLE_FORWARD (next + 1); */
	}

      if (com2start && comstart_pos == 0)
	/* We're looking at a comment starter.  But it might be a comment
	   ender as well (see snmp-mode).  The first time we see one, we
	   need to consider it as a comment starter,
	   and the subsequent times as a comment ender.  */
	com2end = 0;

      /* Turn a 2-char comment sequences into the appropriate syntax.  */
      if (com2end)
	code = Sendcomment;
      else if (com2start)
	code = Scomment;
      /* Ignore comment starters of a different style.  */
      else if (code == Scomment
	       && (comstyle != SYNTAX_FLAGS_COMMENT_STYLE (syntax)
		   || SYNTAX_FLAGS_COMMENT_NESTED (syntax) != comnested))
	continue;

      /* Ignore escaped characters, except comment-enders.  */
      if (code != Sendcomment && char_quoted (from, from_byte))
	continue;

      switch (code)
	{
	case Sstring_fence:
	case Scomment_fence:
	  c = (code == Sstring_fence ? ST_STRING_STYLE : ST_COMMENT_STYLE);
	case Sstring:
	  /* Track parity of quotes.  */
	  if (string_style == -1)
	    /* Entering a string.  */
	    string_style = c;
	  else if (string_style == c)
	    /* Leaving the string.  */
	    string_style = -1;
	  else
	    /* If we have two kinds of string delimiters.
	       There's no way to grok this scanning backwards.  */
	    string_lossage = 1;
	  break;
	  
	case Scomment:
	  /* We've already checked that it is the relevant comstyle.  */
	  if (string_style != -1 || comment_lossage || string_lossage)
	    /* There are odd string quotes involved, so let's be careful.
	       Test case in Pascal: " { " a { " } */
	    goto lossage;

	  if (!comnested)
	    {
	      /* Record best comment-starter so far.  */
	      comstart_pos = from;
	      comstart_byte = from_byte;
	    }
	  else if (--nesting <= 0)
	    /* nested comments have to be balanced, so we don't need to
	       keep looking for earlier ones.  We use here the same (slightly
	       incorrect) reasoning as below:  since it is followed by uniform
	       paired string quotes, this comment-start has to be outside of
	       strings, else the comment-end itself would be inside a string. */
	    goto done;
	  break;

	case Sendcomment:
	  if (SYNTAX_FLAGS_COMMENT_STYLE (syntax) == comstyle
	      && (SYNTAX_FLAGS_COMMENT_NESTED (prev_syntax)
		  || SYNTAX_FLAGS_COMMENT_NESTED (syntax)) == comnested)
	    /* This is the same style of comment ender as ours. */
	    {
	      if (comnested)
		nesting++;
	      else
		/* Anything before that can't count because it would match
		   this comment-ender rather than ours.  */
		from = stop;	/* Break out of the loop.  */
	    }
	  else if (comstart_pos != 0 || c != '\n')
	    /* We're mixing comment styles here, so we'd better be careful.
	       The (comstart_pos != 0 || c != '\n') check is not quite correct
	       (we should just always set comment_lossage), but removing it
	       would imply that any multiline comment in C would go through
	       lossage, which seems overkill.
	       The failure should only happen in the rare cases such as
	         { (* } *)   */
	    comment_lossage = 1;
	  break;

	case Sopen:
	  /* Assume a defun-start point is outside of strings.  */
	  if (open_paren_in_column_0_is_defun_start
	      && (from == stop
		  || (temp_byte = dec_bytepos (from_byte),
		      FETCH_CHAR (temp_byte) == '\n')))
	    {
	      defun_start = from;
	      defun_start_byte = from_byte;
	      from = stop;	/* Break out of the loop.  */
	    }
	  break;

	default:
	  break;
	}
    }

  if (comstart_pos == 0)
    {
      from = comment_end;
      from_byte = comment_end_byte;
      UPDATE_SYNTAX_TABLE_FORWARD (comment_end - 1);
    }
  /* If comstart_pos is set and we get here (ie. didn't jump to `lossage'
     or `done'), then we've found the beginning of the non-nested comment.  */
  else if (1)	/* !comnested */
    {
      from = comstart_pos;
      from_byte = comstart_byte;
      /* Globals are correct now.  */
    }
  else
    {
      struct lisp_parse_state state;
    lossage:
      /* We had two kinds of string delimiters mixed up
	 together.  Decode this going forwards.
	 Scan fwd from a known safe place (beginning-of-defun)
	 to the one in question; this records where we
	 last passed a comment starter.  */
      /* If we did not already find the defun start, find it now.  */
      if (defun_start == 0)
	{
	  defun_start = find_defun_start (comment_end, comment_end_byte);
	  defun_start_byte = find_start_value_byte;
	}
      do
	{
	  scan_sexps_forward (&state,
			      defun_start, defun_start_byte,
			      comment_end, -10000, 0, Qnil, 0);
	  defun_start = comment_end;
	  if (state.incomment == (comnested ? 1 : -1)
	      && state.comstyle == comstyle)
	    from = state.comstr_start;
	  else
	    {
	      from = comment_end;
	      if (state.incomment)
		/* If comment_end is inside some other comment, maybe ours
		   is nested, so we need to try again from within the
		   surrounding comment.  Example: { a (* " *)  */
		{
		  /* FIXME: We should advance by one or two chars. */
		  defun_start = state.comstr_start + 2;
		  defun_start_byte = CHAR_TO_BYTE (defun_start);
		}
	    }
	} while (defun_start < comment_end);

      from_byte = CHAR_TO_BYTE (from);
      UPDATE_SYNTAX_TABLE_FORWARD (from - 1);
    }
    
 done:
  *charpos_ptr = from;
  *bytepos_ptr = from_byte;

  return (from == comment_end) ? -1 : from;
}

DEFUN ("syntax-table-p", Fsyntax_table_p, Ssyntax_table_p, 1, 1, 0,
  "Return t if OBJECT is a syntax table.\n\
Currently, any char-table counts as a syntax table.")
  (object)
     Lisp_Object object;
{
  if (CHAR_TABLE_P (object)
      && EQ (XCHAR_TABLE (object)->purpose, Qsyntax_table))
    return Qt;
  return Qnil;
}

static void
check_syntax_table (obj)
     Lisp_Object obj;
{
  if (!(CHAR_TABLE_P (obj)
	&& EQ (XCHAR_TABLE (obj)->purpose, Qsyntax_table)))
    wrong_type_argument (Qsyntax_table_p, obj);
}   

DEFUN ("syntax-table", Fsyntax_table, Ssyntax_table, 0, 0, 0,
  "Return the current syntax table.\n\
This is the one specified by the current buffer.")
  ()
{
  return current_buffer->syntax_table;
}

DEFUN ("standard-syntax-table", Fstandard_syntax_table,
   Sstandard_syntax_table, 0, 0, 0,
  "Return the standard syntax table.\n\
This is the one used for new buffers.")
  ()
{
  return Vstandard_syntax_table;
}

DEFUN ("copy-syntax-table", Fcopy_syntax_table, Scopy_syntax_table, 0, 1, 0,
  "Construct a new syntax table and return it.\n\
It is a copy of the TABLE, which defaults to the standard syntax table.")
  (table)
     Lisp_Object table;
{
  Lisp_Object copy;

  if (!NILP (table))
    check_syntax_table (table);
  else
    table = Vstandard_syntax_table;

  copy = Fcopy_sequence (table);

  /* Only the standard syntax table should have a default element.
     Other syntax tables should inherit from parents instead.  */
  XCHAR_TABLE (copy)->defalt = Qnil;

  /* Copied syntax tables should all have parents.
     If we copied one with no parent, such as the standard syntax table,
     use the standard syntax table as the copy's parent.  */
  if (NILP (XCHAR_TABLE (copy)->parent))
    Fset_char_table_parent (copy, Vstandard_syntax_table);
  return copy;
}

DEFUN ("set-syntax-table", Fset_syntax_table, Sset_syntax_table, 1, 1, 0,
  "Select a new syntax table for the current buffer.\n\
One argument, a syntax table.")
  (table)
     Lisp_Object table;
{
  int idx;
  check_syntax_table (table);
  current_buffer->syntax_table = table;
  /* Indicate that this buffer now has a specified syntax table.  */
  idx = PER_BUFFER_VAR_IDX (syntax_table);
  SET_PER_BUFFER_VALUE_P (current_buffer, idx, 1);
  return table;
}

/* Convert a letter which signifies a syntax code
 into the code it signifies.
 This is used by modify-syntax-entry, and other things.  */

unsigned char syntax_spec_code[0400] =
  { 0377, 0377, 0377, 0377, 0377, 0377, 0377, 0377,
    0377, 0377, 0377, 0377, 0377, 0377, 0377, 0377,
    0377, 0377, 0377, 0377, 0377, 0377, 0377, 0377,
    0377, 0377, 0377, 0377, 0377, 0377, 0377, 0377,
    (char) Swhitespace, (char) Scomment_fence, (char) Sstring, 0377,
        (char) Smath, 0377, 0377, (char) Squote,
    (char) Sopen, (char) Sclose, 0377, 0377,
	0377, (char) Swhitespace, (char) Spunct, (char) Scharquote,
    0377, 0377, 0377, 0377, 0377, 0377, 0377, 0377,
    0377, 0377, 0377, 0377,
	(char) Scomment, 0377, (char) Sendcomment, 0377,
    (char) Sinherit, 0377, 0377, 0377, 0377, 0377, 0377, 0377,   /* @, A ... */
    0377, 0377, 0377, 0377, 0377, 0377, 0377, 0377,
    0377, 0377, 0377, 0377, 0377, 0377, 0377, (char) Sword,
    0377, 0377, 0377, 0377, (char) Sescape, 0377, 0377, (char) Ssymbol,
    0377, 0377, 0377, 0377, 0377, 0377, 0377, 0377,   /* `, a, ... */
    0377, 0377, 0377, 0377, 0377, 0377, 0377, 0377,
    0377, 0377, 0377, 0377, 0377, 0377, 0377, (char) Sword,
    0377, 0377, 0377, 0377, (char) Sstring_fence, 0377, 0377, 0377
  };

/* Indexed by syntax code, give the letter that describes it.  */

char syntax_code_spec[16] =
  {
    ' ', '.', 'w', '_', '(', ')', '\'', '\"', '$', '\\', '/', '<', '>', '@',
    '!', '|'
  };

/* Indexed by syntax code, give the object (cons of syntax code and
   nil) to be stored in syntax table.  Since these objects can be
   shared among syntax tables, we generate them in advance.  By
   sharing objects, the function `describe-syntax' can give a more
   compact listing.  */
static Lisp_Object Vsyntax_code_object;


/* Look up the value for CHARACTER in syntax table TABLE's parent
   and its parents.  SYNTAX_ENTRY calls this, when TABLE itself has nil
   for CHARACTER.  It's actually used only when not compiled with GCC.  */

Lisp_Object
syntax_parent_lookup (table, character)
     Lisp_Object table;
     int character;
{
  Lisp_Object value;

  while (1)
    {
      table = XCHAR_TABLE (table)->parent;
      if (NILP (table))
	return Qnil;

      value = XCHAR_TABLE (table)->contents[character];
      if (!NILP (value))
	return value;
    }
}

DEFUN ("char-syntax", Fchar_syntax, Schar_syntax, 1, 1, 0,
  "Return the syntax code of CHARACTER, described by a character.\n\
For example, if CHARACTER is a word constituent,\n\
the character `w' is returned.\n\
The characters that correspond to various syntax codes\n\
are listed in the documentation of `modify-syntax-entry'.")
  (character)
     Lisp_Object character;
{
  int char_int;
  gl_state.current_syntax_table = current_buffer->syntax_table;

  gl_state.use_global = 0;
  CHECK_NUMBER (character, 0);
  char_int = XINT (character);
  return make_number (syntax_code_spec[(int) SYNTAX (char_int)]);
}

DEFUN ("matching-paren", Fmatching_paren, Smatching_paren, 1, 1, 0,
  "Return the matching parenthesis of CHARACTER, or nil if none.")
  (character)
     Lisp_Object character;
{
  int char_int, code;
  gl_state.current_syntax_table = current_buffer->syntax_table;
  gl_state.use_global = 0;
  CHECK_NUMBER (character, 0);
  char_int = XINT (character);
  code = SYNTAX (char_int);
  if (code == Sopen || code == Sclose)
    return SYNTAX_MATCH (char_int);
  return Qnil;
}

DEFUN ("string-to-syntax", Fstring_to_syntax, Sstring_to_syntax, 1, 1, 0,
  "Convert a syntax specification STRING into syntax cell form.\n\
STRING should be a string as it is allowed as argument of\n\
`modify-syntax-entry'.  Value is the equivalent cons cell\n\
\(CODE . MATCHING-CHAR) that can be used as value of a `syntax-table'\n\
text property.")
  (string)
     Lisp_Object string;
{
  register unsigned char *p;
  register enum syntaxcode code;
  int val;
  Lisp_Object match;

  CHECK_STRING (string, 0);

  p = XSTRING (string)->data;
  code = (enum syntaxcode) syntax_spec_code[*p++];
  if (((int) code & 0377) == 0377)
    error ("invalid syntax description letter: %c", p[-1]);

  if (code == Sinherit)
    return Qnil;

  if (*p)
    {
      int len;
      int character = (STRING_CHAR_AND_LENGTH
		       (p, STRING_BYTES (XSTRING (string)) - 1, len));
      XSETINT (match, character);
      if (XFASTINT (match) == ' ')
	match = Qnil;
      p += len;
    }
  else
    match = Qnil;

  val = (int) code;
  while (*p)
    switch (*p++)
      {
      case '1':
	val |= 1 << 16;
	break;

      case '2':
	val |= 1 << 17;
	break;

      case '3':
	val |= 1 << 18;
	break;

      case '4':
	val |= 1 << 19;
	break;

      case 'p':
	val |= 1 << 20;
	break;

      case 'b':
	val |= 1 << 21;
	break;

      case 'n':
	val |= 1 << 22;
	break;
      }
	
  if (val < XVECTOR (Vsyntax_code_object)->size && NILP (match))
    return XVECTOR (Vsyntax_code_object)->contents[val];
  else
    /* Since we can't use a shared object, let's make a new one.  */
    return Fcons (make_number (val), match);
}

/* This comment supplies the doc string for modify-syntax-entry,
   for make-docfile to see.  We cannot put this in the real DEFUN
   due to limits in the Unix cpp.

DEFUN ("modify-syntax-entry", foo, bar, 2, 3, 0,
  "Set syntax for character CHAR according to string S.\n\
The syntax is changed only for table TABLE, which defaults to\n\
 the current buffer's syntax table.\n\
The first character of S should be one of the following:\n\
  Space or -  whitespace syntax.    w   word constituent.\n\
  _           symbol constituent.   .   punctuation.\n\
  (           open-parenthesis.     )   close-parenthesis.\n\
  \"           string quote.         \\   escape.\n\
  $           paired delimiter.     '   expression quote or prefix operator.\n\
  <           comment starter.      >   comment ender.\n\
  /           character-quote.      @   inherit from `standard-syntax-table'.\n\
  |           generic string fence. !   generic comment fence.\n\
\n\
Only single-character comment start and end sequences are represented thus.\n\
Two-character sequences are represented as described below.\n\
The second character of S is the matching parenthesis,\n\
 used only if the first character is `(' or `)'.\n\
Any additional characters are flags.\n\
Defined flags are the characters 1, 2, 3, 4, b, p, and n.\n\
 1 means CHAR is the start of a two-char comment start sequence.\n\
 2 means CHAR is the second character of such a sequence.\n\
 3 means CHAR is the start of a two-char comment end sequence.\n\
 4 means CHAR is the second character of such a sequence.\n\
\n\
There can be up to two orthogonal comment sequences.  This is to support\n\
language modes such as C++.  By default, all comment sequences are of style\n\
a, but you can set the comment sequence style to b (on the second character\n\
of a comment-start, or the first character of a comment-end sequence) using\n\
this flag:\n\
 b means CHAR is part of comment sequence b.\n\
 n means CHAR is part of a nestable comment sequence.\n\
\n\
 p means CHAR is a prefix character for `backward-prefix-chars';\n\
   such characters are treated as whitespace when they occur\n\
   between expressions.")
  (char, s, table)
*/

DEFUN ("modify-syntax-entry", Fmodify_syntax_entry, Smodify_syntax_entry, 2, 3, 
  /* I really don't know why this is interactive
     help-form should at least be made useful whilst reading the second arg
   */
  "cSet syntax for character: \nsSet syntax for %s to: ",
  0 /* See immediately above */)
  (c, newentry, syntax_table)
     Lisp_Object c, newentry, syntax_table;
{
  CHECK_NUMBER (c, 0);

  if (NILP (syntax_table))
    syntax_table = current_buffer->syntax_table;
  else
    check_syntax_table (syntax_table);

  SET_RAW_SYNTAX_ENTRY (syntax_table, XINT (c), Fstring_to_syntax (newentry));
  return Qnil;
}

/* Dump syntax table to buffer in human-readable format */

static void
describe_syntax (value)
    Lisp_Object value;
{
  register enum syntaxcode code;
  char desc, start1, start2, end1, end2, prefix, comstyle, comnested;
  char str[2];
  Lisp_Object first, match_lisp;

  Findent_to (make_number (16), make_number (1));

  if (NILP (value))
    {
      insert_string ("default\n");
      return;
    }

  if (CHAR_TABLE_P (value))
    {
      insert_string ("deeper char-table ...\n");
      return;
    }

  if (!CONSP (value))
    {
      insert_string ("invalid\n");
      return;
    }

  first = XCAR (value);
  match_lisp = XCDR (value);

  if (!INTEGERP (first) || !(NILP (match_lisp) || INTEGERP (match_lisp)))
    {
      insert_string ("invalid\n");
      return;
    }

  code = (enum syntaxcode) (XINT (first) & 0377);
  start1 = (XINT (first) >> 16) & 1;
  start2 = (XINT (first) >> 17) & 1;
  end1 = (XINT (first) >> 18) & 1;
  end2 = (XINT (first) >> 19) & 1;
  prefix = (XINT (first) >> 20) & 1;
  comstyle = (XINT (first) >> 21) & 1;
  comnested = (XINT (first) >> 22) & 1;

  if ((int) code < 0 || (int) code >= (int) Smax)
    {
      insert_string ("invalid");
      return;
    }
  desc = syntax_code_spec[(int) code];

  str[0] = desc, str[1] = 0;
  insert (str, 1);

  if (NILP (match_lisp))
    insert (" ", 1);
  else
    insert_char (XINT (match_lisp));

  if (start1)
    insert ("1", 1);
  if (start2)
    insert ("2", 1);

  if (end1)
    insert ("3", 1);
  if (end2)
    insert ("4", 1);

  if (prefix)
    insert ("p", 1);
  if (comstyle)
    insert ("b", 1);
  if (comnested)
    insert ("n", 1);

  insert_string ("\twhich means: ");

  switch (SWITCH_ENUM_CAST (code))
    {
    case Swhitespace:
      insert_string ("whitespace"); break;
    case Spunct:
      insert_string ("punctuation"); break;
    case Sword:
      insert_string ("word"); break;
    case Ssymbol:
      insert_string ("symbol"); break;
    case Sopen:
      insert_string ("open"); break;
    case Sclose:
      insert_string ("close"); break;
    case Squote:
      insert_string ("prefix"); break;
    case Sstring:
      insert_string ("string"); break;
    case Smath:
      insert_string ("math"); break;
    case Sescape:
      insert_string ("escape"); break;
    case Scharquote:
      insert_string ("charquote"); break;
    case Scomment:
      insert_string ("comment"); break;
    case Sendcomment:
      insert_string ("endcomment"); break;
    case Sinherit:
      insert_string ("inherit"); break;
    case Scomment_fence:
      insert_string ("comment fence"); break;
    case Sstring_fence:
      insert_string ("string fence"); break;
    default:
      insert_string ("invalid");
      return;
    }

  if (!NILP (match_lisp))
    {
      insert_string (", matches ");
      insert_char (XINT (match_lisp));
    }

  if (start1)
    insert_string (",\n\t  is the first character of a comment-start sequence");
  if (start2)
    insert_string (",\n\t  is the second character of a comment-start sequence");

  if (end1)
    insert_string (",\n\t  is the first character of a comment-end sequence");
  if (end2)
    insert_string (",\n\t  is the second character of a comment-end sequence");
  if (comstyle)
    insert_string (" (comment style b)");
  if (comnested)
    insert_string (" (nestable)");

  if (prefix)
    insert_string (",\n\t  is a prefix character for `backward-prefix-chars'");

  insert_string ("\n");
}

static Lisp_Object
describe_syntax_1 (vector)
     Lisp_Object vector;
{
  struct buffer *old = current_buffer;
  set_buffer_internal (XBUFFER (Vstandard_output));
  describe_vector (vector, Qnil, describe_syntax, 0, Qnil, Qnil, (int *) 0, 0);
  while (! NILP (XCHAR_TABLE (vector)->parent))
    {
      vector = XCHAR_TABLE (vector)->parent;
      insert_string ("\nThe parent syntax table is:");
      describe_vector (vector, Qnil, describe_syntax, 0, Qnil, Qnil,
		       (int *) 0, 0);
    }
	
  call0 (intern ("help-mode"));
  set_buffer_internal (old);
  return Qnil;
}

DEFUN ("describe-syntax", Fdescribe_syntax, Sdescribe_syntax, 0, 0, "",
  "Describe the syntax specifications in the syntax table.\n\
The descriptions are inserted in a buffer, which is then displayed.")
  ()
{
  internal_with_output_to_temp_buffer
     ("*Help*", describe_syntax_1, current_buffer->syntax_table);

  return Qnil;
}

int parse_sexp_ignore_comments;

/* Return the position across COUNT words from FROM.
   If that many words cannot be found before the end of the buffer, return 0.
   COUNT negative means scan backward and stop at word beginning.  */

int
scan_words (from, count)
     register int from, count;
{
  register int beg = BEGV;
  register int end = ZV;
  register int from_byte = CHAR_TO_BYTE (from);
  register enum syntaxcode code;
  int ch0, ch1;

  immediate_quit = 1;
  QUIT;

  SETUP_SYNTAX_TABLE (from, count);

  while (count > 0)
    {
      while (1)
	{
	  if (from == end)
	    {
	      immediate_quit = 0;
	      return 0;
	    }
	  UPDATE_SYNTAX_TABLE_FORWARD (from);
	  ch0 = FETCH_CHAR (from_byte);
	  code = SYNTAX (ch0);
	  INC_BOTH (from, from_byte);
	  if (words_include_escapes
	      && (code == Sescape || code == Scharquote))
	    break;
	  if (code == Sword)
	    break;
	}
      /* Now CH0 is a character which begins a word and FROM is the
         position of the next character.  */
      while (1)
	{
	  if (from == end) break;
	  UPDATE_SYNTAX_TABLE_FORWARD (from);
	  ch1 = FETCH_CHAR (from_byte);
	  code = SYNTAX (ch1);
	  if (!(words_include_escapes
		&& (code == Sescape || code == Scharquote)))
	    if (code != Sword || WORD_BOUNDARY_P (ch0, ch1))
	      break;
	  INC_BOTH (from, from_byte);
	  ch0 = ch1;
	}
      count--;
    }
  while (count < 0)
    {
      while (1)
	{
	  if (from == beg)
	    {
	      immediate_quit = 0;
	      return 0;
	    }
	  DEC_BOTH (from, from_byte);
	  UPDATE_SYNTAX_TABLE_BACKWARD (from);
	  ch1 = FETCH_CHAR (from_byte);
	  code = SYNTAX (ch1);
	  if (words_include_escapes
	      && (code == Sescape || code == Scharquote))
	    break;
	  if (code == Sword)
	    break;
	}
      /* Now CH1 is a character which ends a word and FROM is the
         position of it.  */
      while (1)
	{
	  int temp_byte;

	  if (from == beg)
	    break;
	  temp_byte = dec_bytepos (from_byte);
	  UPDATE_SYNTAX_TABLE_BACKWARD (from);
	  ch0 = FETCH_CHAR (temp_byte);
	  code = SYNTAX (ch0);
	  if (!(words_include_escapes
		&& (code == Sescape || code == Scharquote)))
	    if (code != Sword || WORD_BOUNDARY_P (ch0, ch1))
	      break;
	  DEC_BOTH (from, from_byte);
	  ch1 = ch0;
	}
      count++;
    }

  immediate_quit = 0;

  return from;
}

DEFUN ("forward-word", Fforward_word, Sforward_word, 1, 1, "p",
  "Move point forward ARG words (backward if ARG is negative).\n\
Normally returns t.\n\
If an edge of the buffer or a field boundary is reached, point is left there\n\
and the function returns nil.  Field boundaries are not noticed if\n\
`inhibit-field-text-motion' is non-nil.")
  (count)
     Lisp_Object count;
{
  int orig_val, val;
  CHECK_NUMBER (count, 0);

  val = orig_val = scan_words (PT, XINT (count));
  if (! orig_val)
    val = XINT (count) > 0 ? ZV : BEGV;

  /* Avoid jumping out of an input field.  */
  val = XFASTINT (Fconstrain_to_field (make_number (val), make_number (PT),
				       Qt, Qnil, Qnil));
  
  SET_PT (val);
  return val == orig_val ? Qt : Qnil;
}

Lisp_Object skip_chars ();

DEFUN ("skip-chars-forward", Fskip_chars_forward, Sskip_chars_forward, 1, 2, 0,
  "Move point forward, stopping before a char not in STRING, or at pos LIM.\n\
STRING is like the inside of a `[...]' in a regular expression\n\
except that `]' is never special and `\\' quotes `^', `-' or `\\'\n\
 (but not as the end of a range; quoting is never needed there).\n\
Thus, with arg \"a-zA-Z\", this skips letters stopping before first nonletter.\n\
With arg \"^a-zA-Z\", skips nonletters stopping before first letter.\n\
Returns the distance traveled, either zero or positive.")
  (string, lim)
     Lisp_Object string, lim;
{
  return skip_chars (1, 0, string, lim);
}

DEFUN ("skip-chars-backward", Fskip_chars_backward, Sskip_chars_backward, 1, 2, 0,
  "Move point backward, stopping after a char not in STRING, or at pos LIM.\n\
See `skip-chars-forward' for details.\n\
Returns the distance traveled, either zero or negative.")
  (string, lim)
     Lisp_Object string, lim;
{
  return skip_chars (0, 0, string, lim);
}

DEFUN ("skip-syntax-forward", Fskip_syntax_forward, Sskip_syntax_forward, 1, 2, 0,
  "Move point forward across chars in specified syntax classes.\n\
SYNTAX is a string of syntax code characters.\n\
Stop before a char whose syntax is not in SYNTAX, or at position LIM.\n\
If SYNTAX starts with ^, skip characters whose syntax is NOT in SYNTAX.\n\
This function returns the distance traveled, either zero or positive.")
  (syntax, lim)
     Lisp_Object syntax, lim;
{
  return skip_chars (1, 1, syntax, lim);
}

DEFUN ("skip-syntax-backward", Fskip_syntax_backward, Sskip_syntax_backward, 1, 2, 0,
  "Move point backward across chars in specified syntax classes.\n\
SYNTAX is a string of syntax code characters.\n\
Stop on reaching a char whose syntax is not in SYNTAX, or at position LIM.\n\
If SYNTAX starts with ^, skip characters whose syntax is NOT in SYNTAX.\n\
This function returns the distance traveled, either zero or negative.")
  (syntax, lim)
     Lisp_Object syntax, lim;
{
  return skip_chars (0, 1, syntax, lim);
}

static Lisp_Object
skip_chars (forwardp, syntaxp, string, lim)
     int forwardp, syntaxp;
     Lisp_Object string, lim;
{
  register unsigned int c;
  unsigned char fastmap[0400];
  /* If SYNTAXP is 0, STRING may contain multi-byte form of characters
     of which codes don't fit in FASTMAP.  In that case, set the
     ranges of characters in CHAR_RANGES.  */
  int *char_ranges;
  int n_char_ranges = 0;
  int negate = 0;
  register int i, i_byte;
  int multibyte = !NILP (current_buffer->enable_multibyte_characters);
  int string_multibyte;
  int size_byte;
  unsigned char *str;
  int len;

  CHECK_STRING (string, 0);
  char_ranges = (int *) alloca (XSTRING (string)->size * (sizeof (int)) * 2);
  string_multibyte = STRING_MULTIBYTE (string);
  str = XSTRING (string)->data;
  size_byte = STRING_BYTES (XSTRING (string));

  /* Adjust the multibyteness of the string to that of the buffer.  */
  if (multibyte != string_multibyte)
    {
      int nbytes;

      if (multibyte)
	nbytes = count_size_as_multibyte (XSTRING (string)->data,
					  XSTRING (string)->size);
      else
	nbytes = XSTRING (string)->size;
      if (nbytes != size_byte)
	{
	  str = (unsigned char *) alloca (nbytes);
	  copy_text (XSTRING (string)->data, str, size_byte,
		     string_multibyte, multibyte);
	  size_byte = nbytes;
	}
    }

  if (NILP (lim))
    XSETINT (lim, forwardp ? ZV : BEGV);
  else
    CHECK_NUMBER_COERCE_MARKER (lim, 0);

  /* In any case, don't allow scan outside bounds of buffer.  */
  if (XINT (lim) > ZV)
    XSETFASTINT (lim, ZV);
  if (XINT (lim) < BEGV)
    XSETFASTINT (lim, BEGV);

  bzero (fastmap, sizeof fastmap);

  i_byte = 0;

  if (i_byte < size_byte
      && XSTRING (string)->data[0] == '^')
    {
      negate = 1; i_byte++;
    }

  /* Find the characters specified and set their elements of fastmap.
     If syntaxp, each character counts as itself.
     Otherwise, handle backslashes and ranges specially.  */

  while (i_byte < size_byte)
    {
      c = STRING_CHAR_AND_LENGTH (str + i_byte, size_byte - i_byte, len);
      i_byte += len;

      if (syntaxp)
	fastmap[syntax_spec_code[c & 0377]] = 1;
      else
	{
	  if (c == '\\')
	    {
	      if (i_byte == size_byte)
		break;

	      c = STRING_CHAR_AND_LENGTH (str+i_byte, size_byte-i_byte, len);
	      i_byte += len;
	    }
	  if (i_byte < size_byte
	      && str[i_byte] == '-')
	    {
	      unsigned int c2;

	      /* Skip over the dash.  */
	      i_byte++;

	      if (i_byte == size_byte)
		break;

	      /* Get the end of the range.  */
	      c2 =STRING_CHAR_AND_LENGTH (str+i_byte, size_byte-i_byte, len);
	      i_byte += len;

	      if (SINGLE_BYTE_CHAR_P (c))
		{
		  if (! SINGLE_BYTE_CHAR_P (c2))
		    {
		      /* Handle a range starting with a character of
			 less than 256, and ending with a character of
			 not less than 256.  Split that into two
			 ranges, the low one ending at 0377, and the
			 high one starting at the smallest character
			 in the charset of C2 and ending at C2.  */
		      int charset = CHAR_CHARSET (c2);
		      int c1 = MAKE_CHAR (charset, 0, 0);

		      char_ranges[n_char_ranges++] = c1;
		      char_ranges[n_char_ranges++] = c2;
		      c2 = 0377;
		    }
		  while (c <= c2)
		    {
		      fastmap[c] = 1;
		      c++;
		    }
		}
	      else if (c <= c2)	/* Both C and C2 are multibyte char.  */
		{
		  char_ranges[n_char_ranges++] = c;
		  char_ranges[n_char_ranges++] = c2;
		}
	    }
	  else
	    {
	      if (SINGLE_BYTE_CHAR_P (c))
		fastmap[c] = 1;
	      else
		{
		  char_ranges[n_char_ranges++] = c;
		  char_ranges[n_char_ranges++] = c;
		}
	    }
	}
    }

  /* If ^ was the first character, complement the fastmap.  */
  if (negate)
    for (i = 0; i < sizeof fastmap; i++)
      fastmap[i] ^= 1;

  {
    int start_point = PT;
    int pos = PT;
    int pos_byte = PT_BYTE;

    immediate_quit = 1;
    if (syntaxp)
      {
        SETUP_SYNTAX_TABLE (pos, forwardp ? 1 : -1);
	if (forwardp)
	  {
	    if (multibyte)
	      {
		if (pos < XINT (lim))
		  while (fastmap[(int) SYNTAX (FETCH_CHAR (pos_byte))])
		    {
		      /* Since we already checked for multibyteness,
			 avoid using INC_BOTH which checks again.  */
		      INC_POS (pos_byte);
		      pos++;
		      if (pos >= XINT (lim))
		    	break;
		      UPDATE_SYNTAX_TABLE_FORWARD (pos);
		    }
	      }
	    else
	      {
		while (pos < XINT (lim)
		       && fastmap[(int) SYNTAX (FETCH_BYTE (pos))])
		  {
		    pos++;
		    UPDATE_SYNTAX_TABLE_FORWARD (pos);
		  }
	      }
	  }
	else
	  {
	    if (multibyte)
	      {
		while (pos > XINT (lim))
		  {
		    int savepos = pos_byte;
		    /* Since we already checked for multibyteness,
		       avoid using DEC_BOTH which checks again.  */
		    pos--;
		    DEC_POS (pos_byte);
		    UPDATE_SYNTAX_TABLE_BACKWARD (pos);
		    if (!fastmap[(int) SYNTAX (FETCH_CHAR (pos_byte))])
		      {
			pos++;
			pos_byte = savepos;
			break;
		      }
		  }
	      }
	    else
	      {
		if (pos > XINT (lim))
		  while (fastmap[(int) SYNTAX (FETCH_BYTE (pos - 1))])
		    {
		      pos--;
		      if (pos <= XINT (lim))
			break;
		      UPDATE_SYNTAX_TABLE_BACKWARD (pos - 1);
		    }
	      }
	  }
      }
    else
      {
	if (forwardp)
	  {
	    if (multibyte)
	      while (pos < XINT (lim))
		{
		  c = FETCH_MULTIBYTE_CHAR (pos_byte);
		  if (SINGLE_BYTE_CHAR_P (c))
		    {
		      if (!fastmap[c])
			break;
		    }
		  else
		    {
		      /* If we are looking at a multibyte character,
			 we must look up the character in the table
			 CHAR_RANGES.  If there's no data in the
			 table, that character is not what we want to
			 skip.  */

		      /* The following code do the right thing even if
			 n_char_ranges is zero (i.e. no data in
			 CHAR_RANGES).  */
		      for (i = 0; i < n_char_ranges; i += 2)
			if (c >= char_ranges[i] && c <= char_ranges[i + 1])
			  break;
		      if (!(negate ^ (i < n_char_ranges)))
			break;
		    }
		  INC_BOTH (pos, pos_byte);
		}
	    else
	      while (pos < XINT (lim) && fastmap[FETCH_BYTE (pos)])
		pos++;
	  }
	else
	  {
	    if (multibyte)
	      while (pos > XINT (lim))
		{
		  int prev_pos_byte = pos_byte;

		  DEC_POS (prev_pos_byte);
		  c = FETCH_MULTIBYTE_CHAR (prev_pos_byte);
		  if (SINGLE_BYTE_CHAR_P (c))
		    {
		      if (!fastmap[c])
			break;
		    }
		  else
		    {
		      /* See the comment in the previous similar code.  */
		      for (i = 0; i < n_char_ranges; i += 2)
			if (c >= char_ranges[i] && c <= char_ranges[i + 1])
			  break;
		      if (!(negate ^ (i < n_char_ranges)))
			break;
		    }
		  pos--;
		  pos_byte = prev_pos_byte;
		}
	    else
	      while (pos > XINT (lim) && fastmap[FETCH_BYTE (pos - 1)])
		pos--;
	  }
      }

#if 0 /* Not needed now that a position in mid-character
	 cannot be specified in Lisp.  */
    if (multibyte
	/* INC_POS or DEC_POS might have moved POS over LIM.  */
	&& (forwardp ? (pos > XINT (lim)) : (pos < XINT (lim))))
      pos = XINT (lim);
#endif

    if (! multibyte)
      pos_byte = pos;

    SET_PT_BOTH (pos, pos_byte);
    immediate_quit = 0;

    return make_number (PT - start_point);
  }
}

/* Jump over a comment, assuming we are at the beginning of one.
   FROM is the current position.
   FROM_BYTE is the bytepos corresponding to FROM.
   Do not move past STOP (a charpos).
   The comment over which we have to jump is of style STYLE
     (either SYNTAX_COMMENT_STYLE(foo) or ST_COMMENT_STYLE).
   NESTING should be positive to indicate the nesting at the beginning
     for nested comments and should be zero or negative else.
     ST_COMMENT_STYLE cannot be nested.
   PREV_SYNTAX is the SYNTAX_WITH_FLAGS of the previous character
     (or 0 If the search cannot start in the middle of a two-character).

   If successful, return 1 and store the charpos of the comment's end
   into *CHARPOS_PTR and the corresponding bytepos into *BYTEPOS_PTR.
   Else, return 0 and store the charpos STOP into *CHARPOS_PTR, the
   corresponding bytepos into *BYTEPOS_PTR and the current nesting
   (as defined for state.incomment) in *INCOMMENT_PTR.

   The comment end is the last character of the comment rather than the
     character just after the comment.

   Global syntax data is assumed to initially be valid for FROM and
   remains valid for forward search starting at the returned position. */

static int
forw_comment (from, from_byte, stop, nesting, style, prev_syntax,
	      charpos_ptr, bytepos_ptr, incomment_ptr)
     int from, from_byte, stop;
     int nesting, style, prev_syntax;
     int *charpos_ptr, *bytepos_ptr, *incomment_ptr;
{
  register int c, c1;
  register enum syntaxcode code;
  register int syntax;

  if (nesting <= 0) nesting = -1;

  /* Enter the loop in the middle so that we find
     a 2-char comment ender if we start in the middle of it.  */
  syntax = prev_syntax;
  if (syntax != 0) goto forw_incomment;

  while (1)
    {
      if (from == stop)
	{
	  *incomment_ptr = nesting;
	  *charpos_ptr = from;
	  *bytepos_ptr = from_byte;
	  return 0;
	}
      c = FETCH_CHAR (from_byte);
      syntax = SYNTAX_WITH_FLAGS (c);
      code = syntax & 0xff;
      if (code == Sendcomment
	  && SYNTAX_FLAGS_COMMENT_STYLE (syntax) == style
	  && (SYNTAX_FLAGS_COMMENT_NESTED (syntax) ?
	      (nesting > 0 && --nesting == 0) : nesting < 0))
	/* we have encountered a comment end of the same style
	   as the comment sequence which began this comment
	   section */
	break;
      if (code == Scomment_fence
	  && style == ST_COMMENT_STYLE)
	/* we have encountered a comment end of the same style
	   as the comment sequence which began this comment
	   section.  */
	break;
      if (nesting > 0
	  && code == Scomment
	  && SYNTAX_FLAGS_COMMENT_NESTED (syntax)
	  && SYNTAX_FLAGS_COMMENT_STYLE (syntax) == style)
	/* we have encountered a nested comment of the same style
	   as the comment sequence which began this comment section */
	nesting++;
      INC_BOTH (from, from_byte);
      UPDATE_SYNTAX_TABLE_FORWARD (from);
      
    forw_incomment:
      if (from < stop && SYNTAX_FLAGS_COMEND_FIRST (syntax)
	  && SYNTAX_FLAGS_COMMENT_STYLE (syntax) == style
	  && (c1 = FETCH_CHAR (from_byte),
	      SYNTAX_COMEND_SECOND (c1))
	  && ((SYNTAX_FLAGS_COMMENT_NESTED (syntax) ||
	       SYNTAX_COMMENT_NESTED (c1)) ? nesting > 0 : nesting < 0))
	{
	  if (--nesting <= 0)
	    /* we have encountered a comment end of the same style
	       as the comment sequence which began this comment
	       section */
	    break;
	  else
	    {
	      INC_BOTH (from, from_byte);
	      UPDATE_SYNTAX_TABLE_FORWARD (from);
	    }
	}
      if (nesting > 0
	  && from < stop
	  && SYNTAX_FLAGS_COMSTART_FIRST (syntax)
	  && (c1 = FETCH_CHAR (from_byte),
	      SYNTAX_COMMENT_STYLE (c1) == style
	      && SYNTAX_COMSTART_SECOND (c1))
	  && (SYNTAX_FLAGS_COMMENT_NESTED (syntax) ||
	      SYNTAX_COMMENT_NESTED (c1)))
	/* we have encountered a nested comment of the same style
	   as the comment sequence which began this comment
	   section */
	{
	  INC_BOTH (from, from_byte);
	  UPDATE_SYNTAX_TABLE_FORWARD (from);
	  nesting++;
	}
    }
  *charpos_ptr = from;
  *bytepos_ptr = from_byte;
  return 1;
}

DEFUN ("forward-comment", Fforward_comment, Sforward_comment, 1, 1, 0,
  "Move forward across up to N comments.  If N is negative, move backward.\n\
Stop scanning if we find something other than a comment or whitespace.\n\
Set point to where scanning stops.\n\
If N comments are found as expected, with nothing except whitespace\n\
between them, return t; otherwise return nil.")
  (count)
     Lisp_Object count;
{
  register int from;
  int from_byte;
  register int stop;
  register int c, c1;
  register enum syntaxcode code;
  int comstyle = 0;	    /* style of comment encountered */
  int comnested = 0;	    /* whether the comment is nestable or not */
  int found;
  int count1;
  int out_charpos, out_bytepos;
  int dummy;

  CHECK_NUMBER (count, 0);
  count1 = XINT (count);
  stop = count1 > 0 ? ZV : BEGV;

  immediate_quit = 1;
  QUIT;

  from = PT;
  from_byte = PT_BYTE;

  SETUP_SYNTAX_TABLE (from, count1);
  while (count1 > 0)
    {
      do
	{
	  int comstart_first;

	  if (from == stop)
	    {
	      SET_PT_BOTH (from, from_byte);
	      immediate_quit = 0;
	      return Qnil;
	    }
	  c = FETCH_CHAR (from_byte);
	  code = SYNTAX (c);
	  comstart_first = SYNTAX_COMSTART_FIRST (c);
	  comnested = SYNTAX_COMMENT_NESTED (c);
	  comstyle = SYNTAX_COMMENT_STYLE (c);
	  INC_BOTH (from, from_byte);
	  UPDATE_SYNTAX_TABLE_FORWARD (from);
	  if (from < stop && comstart_first
	      && (c1 = FETCH_CHAR (from_byte),
		  SYNTAX_COMSTART_SECOND (c1)))
	    {
	      /* We have encountered a comment start sequence and we 
		 are ignoring all text inside comments.  We must record
		 the comment style this sequence begins so that later,
		 only a comment end of the same style actually ends
		 the comment section.  */
	      code = Scomment;
	      comstyle = SYNTAX_COMMENT_STYLE (c1);
	      comnested = comnested || SYNTAX_COMMENT_NESTED (c1);
	      INC_BOTH (from, from_byte);
	      UPDATE_SYNTAX_TABLE_FORWARD (from);
	    }
	}
      while (code == Swhitespace || (code == Sendcomment && c == '\n'));

      if (code == Scomment_fence)
	comstyle = ST_COMMENT_STYLE;
      else if (code != Scomment)
	{
	  immediate_quit = 0;
	  DEC_BOTH (from, from_byte);
	  SET_PT_BOTH (from, from_byte);
	  return Qnil;
	}
      /* We're at the start of a comment.  */
      found = forw_comment (from, from_byte, stop, comnested, comstyle, 0,
			    &out_charpos, &out_bytepos, &dummy);
      from = out_charpos; from_byte = out_bytepos;
      if (!found)
	{
	  immediate_quit = 0;
	  SET_PT_BOTH (from, from_byte);
	  return Qnil;
	}
      INC_BOTH (from, from_byte);
      UPDATE_SYNTAX_TABLE_FORWARD (from);
      /* We have skipped one comment.  */
      count1--;
    }

  while (count1 < 0)
    {
      while (1)
	{
	  int quoted;

	  if (from <= stop)
	    {
	      SET_PT_BOTH (BEGV, BEGV_BYTE);
	      immediate_quit = 0;
	      return Qnil;
	    }

	  DEC_BOTH (from, from_byte);
	  /* char_quoted does UPDATE_SYNTAX_TABLE_BACKWARD (from).  */
	  quoted = char_quoted (from, from_byte);
	  if (quoted)
	    {
	      DEC_BOTH (from, from_byte);
	      goto leave;
	    }
	  c = FETCH_CHAR (from_byte);
	  code = SYNTAX (c);
	  comstyle = 0;
	  comnested = SYNTAX_COMMENT_NESTED (c);
	  if (code == Sendcomment)
	    comstyle = SYNTAX_COMMENT_STYLE (c);
	  if (from > stop && SYNTAX_COMEND_SECOND (c)
	      && prev_char_comend_first (from, from_byte)
	      && !char_quoted (from - 1, dec_bytepos (from_byte)))
	    {
	      /* We must record the comment style encountered so that
		 later, we can match only the proper comment begin
		 sequence of the same style.  */
	      DEC_BOTH (from, from_byte);
	      code = Sendcomment;
	      /* Calling char_quoted, above, set up global syntax position
		 at the new value of FROM.  */
	      c1 = FETCH_CHAR (from_byte);
	      comstyle = SYNTAX_COMMENT_STYLE (c1);
	      comnested = comnested || SYNTAX_COMMENT_NESTED (c1);
	    }

	  if (code == Scomment_fence)
	    {
	      /* Skip until first preceding unquoted comment_fence.  */
	      int found = 0, ini = from, ini_byte = from_byte;
	      
	      while (1)
		{
		  DEC_BOTH (from, from_byte);
		  if (from == stop)
		    break;
		  UPDATE_SYNTAX_TABLE_BACKWARD (from);
		  c = FETCH_CHAR (from_byte);
		  if (SYNTAX (c) == Scomment_fence
		      && !char_quoted (from, from_byte)) 
		    {
		      found = 1; 
		      break;
		    }
		}
	      if (found == 0)
		{
		  from = ini;		/* Set point to ini + 1.  */
		  from_byte = ini_byte;
		  goto leave;
		}
	    }
	  else if (code == Sendcomment)
	    {
	      found = back_comment (from, from_byte, stop, comnested, comstyle,
				    &out_charpos, &out_bytepos);
	      if (found == -1)
		{
		  if (c == '\n')
		    /* This end-of-line is not an end-of-comment.
		       Treat it like a whitespace.
		       CC-mode (and maybe others) relies on this behavior.  */
		    ;
		  else
		    {
		      /* Failure: we should go back to the end of this
			 not-quite-endcomment.  */
		      if (SYNTAX(c) != code)
			/* It was a two-char Sendcomment.  */
			INC_BOTH (from, from_byte);
		      goto leave;
		    }
		}
	      else
		{
		  /* We have skipped one comment.  */
		  from = out_charpos, from_byte = out_bytepos;
		  break;
		}
	    }
	  else if (code != Swhitespace)
	    {
	    leave:
	      immediate_quit = 0;
	      INC_BOTH (from, from_byte);
	      SET_PT_BOTH (from, from_byte);
	      return Qnil;
	    }
	}

      count1++;
    }

  SET_PT_BOTH (from, from_byte);
  immediate_quit = 0;
  return Qt;
}

/* Return syntax code of character C if C is a single byte character
   or `multibyte_symbol_p' is zero.  Otherwise, return Ssymbol.  */

#define SYNTAX_WITH_MULTIBYTE_CHECK(c)			\
  ((SINGLE_BYTE_CHAR_P (c) || !multibyte_symbol_p)	\
   ? SYNTAX (c) : Ssymbol)

static Lisp_Object
scan_lists (from, count, depth, sexpflag)
     register int from;
     int count, depth, sexpflag;
{
  Lisp_Object val;
  register int stop = count > 0 ? ZV : BEGV;
  register int c, c1;
  int stringterm;
  int quoted;
  int mathexit = 0;
  register enum syntaxcode code, temp_code;
  int min_depth = depth;    /* Err out if depth gets less than this.  */
  int comstyle = 0;	    /* style of comment encountered */
  int comnested = 0;	    /* whether the comment is nestable or not */
  int temp_pos;
  int last_good = from;
  int found;
  int from_byte;
  int out_bytepos, out_charpos;
  int temp, dummy;
  int multibyte_symbol_p = sexpflag && multibyte_syntax_as_symbol;

  if (depth > 0) min_depth = 0;

  if (from > ZV) from = ZV;
  if (from < BEGV) from = BEGV;

  from_byte = CHAR_TO_BYTE (from);

  immediate_quit = 1;
  QUIT;

  SETUP_SYNTAX_TABLE (from, count);
  while (count > 0)
    {
      while (from < stop)
	{
	  int comstart_first, prefix;
	  UPDATE_SYNTAX_TABLE_FORWARD (from);
	  c = FETCH_CHAR (from_byte);
	  code = SYNTAX_WITH_MULTIBYTE_CHECK (c);
	  comstart_first = SYNTAX_COMSTART_FIRST (c);
	  comnested = SYNTAX_COMMENT_NESTED (c);
	  comstyle = SYNTAX_COMMENT_STYLE (c);
	  prefix = SYNTAX_PREFIX (c);
	  if (depth == min_depth)
	    last_good = from;
	  INC_BOTH (from, from_byte);
	  UPDATE_SYNTAX_TABLE_FORWARD (from);
	  if (from < stop && comstart_first
	      && SYNTAX_COMSTART_SECOND (FETCH_CHAR (from_byte))
	      && parse_sexp_ignore_comments)
	    {
	      /* we have encountered a comment start sequence and we 
		 are ignoring all text inside comments.  We must record
		 the comment style this sequence begins so that later,
		 only a comment end of the same style actually ends
		 the comment section */
	      code = Scomment;
	      c1 = FETCH_CHAR (from_byte);
	      comstyle = SYNTAX_COMMENT_STYLE (c1);
	      comnested = comnested || SYNTAX_COMMENT_NESTED (c1);
	      INC_BOTH (from, from_byte);
	      UPDATE_SYNTAX_TABLE_FORWARD (from);
	    }
	  
	  if (prefix)
	    continue;

	  switch (SWITCH_ENUM_CAST (code))
	    {
	    case Sescape:
	    case Scharquote:
	      if (from == stop) goto lose;
	      INC_BOTH (from, from_byte);
	      /* treat following character as a word constituent */
	    case Sword:
	    case Ssymbol:
	      if (depth || !sexpflag) break;
	      /* This word counts as a sexp; return at end of it.  */
	      while (from < stop)
		{
		  UPDATE_SYNTAX_TABLE_FORWARD (from);

		  /* Some compilers can't handle this inside the switch.  */
		  c = FETCH_CHAR (from_byte);
		  temp = SYNTAX_WITH_MULTIBYTE_CHECK (c);
		  switch (temp)
		    {
		    case Scharquote:
		    case Sescape:
		      INC_BOTH (from, from_byte);
		      if (from == stop) goto lose;
		      break;
		    case Sword:
		    case Ssymbol:
		    case Squote:
		      break;
		    default:
		      goto done;
		    }
		  INC_BOTH (from, from_byte);
		}
	      goto done;

	    case Scomment_fence:
	      comstyle = ST_COMMENT_STYLE;
	      /* FALLTHROUGH */
	    case Scomment:
	      if (!parse_sexp_ignore_comments) break;
	      UPDATE_SYNTAX_TABLE_FORWARD (from);
	      found = forw_comment (from, from_byte, stop,
				    comnested, comstyle, 0,
				    &out_charpos, &out_bytepos, &dummy);
	      from = out_charpos, from_byte = out_bytepos;
	      if (!found)
		{
		  if (depth == 0)
		    goto done;
		  goto lose;
		}
	      INC_BOTH (from, from_byte);
	      UPDATE_SYNTAX_TABLE_FORWARD (from);
	      break;

	    case Smath:
	      if (!sexpflag)
		break;
	      if (from != stop && c == FETCH_CHAR (from_byte))
		{
		  INC_BOTH (from, from_byte);
		}
	      if (mathexit)
		{
		  mathexit = 0;
		  goto close1;
		}
	      mathexit = 1;

	    case Sopen:
	      if (!++depth) goto done;
	      break;

	    case Sclose:
	    close1:
	      if (!--depth) goto done;
	      if (depth < min_depth)
		Fsignal (Qscan_error,
			 Fcons (build_string ("Containing expression ends prematurely"),
				Fcons (make_number (last_good),
				       Fcons (make_number (from), Qnil))));
	      break;

	    case Sstring:
	    case Sstring_fence:
	      temp_pos = dec_bytepos (from_byte);
	      stringterm = FETCH_CHAR (temp_pos);
	      while (1)
		{
		  if (from >= stop) goto lose;
		  UPDATE_SYNTAX_TABLE_FORWARD (from);
		  c = FETCH_CHAR (from_byte);
		  if (code == Sstring
		      ? (c == stringterm
			 && SYNTAX_WITH_MULTIBYTE_CHECK (c) == Sstring)
		      : SYNTAX_WITH_MULTIBYTE_CHECK (c) == Sstring_fence)
		    break;

		  /* Some compilers can't handle this inside the switch.  */
		  temp = SYNTAX_WITH_MULTIBYTE_CHECK (c);
		  switch (temp)
		    {
		    case Scharquote:
		    case Sescape:
		      INC_BOTH (from, from_byte);
		    }
		  INC_BOTH (from, from_byte);
		}
	      INC_BOTH (from, from_byte);
	      if (!depth && sexpflag) goto done;
	      break;
	    }
	}

      /* Reached end of buffer.  Error if within object, return nil if between */
      if (depth) goto lose;

      immediate_quit = 0;
      return Qnil;

      /* End of object reached */
    done:
      count--;
    }

  while (count < 0)
    {
      while (from > stop)
	{
	  DEC_BOTH (from, from_byte);
	  UPDATE_SYNTAX_TABLE_BACKWARD (from);
	  c = FETCH_CHAR (from_byte);
	  code = SYNTAX_WITH_MULTIBYTE_CHECK (c);
	  if (depth == min_depth)
	    last_good = from;
	  comstyle = 0;
	  comnested = SYNTAX_COMMENT_NESTED (c);
	  if (code == Sendcomment)
	    comstyle = SYNTAX_COMMENT_STYLE (c);
	  if (from > stop && SYNTAX_COMEND_SECOND (c)
	      && prev_char_comend_first (from, from_byte)
	      && parse_sexp_ignore_comments)
	    {
	      /* We must record the comment style encountered so that
		 later, we can match only the proper comment begin
		 sequence of the same style.  */
	      DEC_BOTH (from, from_byte);
	      UPDATE_SYNTAX_TABLE_BACKWARD (from);
	      code = Sendcomment;
	      c1 = FETCH_CHAR (from_byte);
	      comstyle = SYNTAX_COMMENT_STYLE (c1);
	      comnested = comnested || SYNTAX_COMMENT_NESTED (c1);
	    }
	  
	  /* Quoting turns anything except a comment-ender
	     into a word character.  Note that this cannot be true
	     if we decremented FROM in the if-statement above.  */
	  if (code != Sendcomment && char_quoted (from, from_byte))
	    code = Sword;
	  else if (SYNTAX_PREFIX (c))
	    continue;

	  switch (SWITCH_ENUM_CAST (code))
	    {
	    case Sword:
	    case Ssymbol:
	    case Sescape:
	    case Scharquote:
	      if (depth || !sexpflag) break;
	      /* This word counts as a sexp; count object finished
		 after passing it.  */
	      while (from > stop)
		{
		  temp_pos = from_byte;
		  if (! NILP (current_buffer->enable_multibyte_characters))
		    DEC_POS (temp_pos);
		  else
		    temp_pos--;
		  UPDATE_SYNTAX_TABLE_BACKWARD (from - 1);
		  c1 = FETCH_CHAR (temp_pos);
		  temp_code = SYNTAX_WITH_MULTIBYTE_CHECK (c1);
		  /* Don't allow comment-end to be quoted.  */
		  if (temp_code == Sendcomment)
		    goto done2;
		  quoted = char_quoted (from - 1, temp_pos);
		  if (quoted)
		    {
		      DEC_BOTH (from, from_byte);
		      temp_pos = dec_bytepos (temp_pos);
		      UPDATE_SYNTAX_TABLE_BACKWARD (from - 1);
		    }
		  c1 = FETCH_CHAR (temp_pos);
		  temp_code = SYNTAX_WITH_MULTIBYTE_CHECK (c1);
		  if (! (quoted || temp_code == Sword
			 || temp_code == Ssymbol
			 || temp_code == Squote))
            	    goto done2;
		  DEC_BOTH (from, from_byte);
		}
	      goto done2;

	    case Smath:
	      if (!sexpflag)
		break;
	      temp_pos = dec_bytepos (from_byte);
	      UPDATE_SYNTAX_TABLE_BACKWARD (from - 1);
	      if (from != stop && c == FETCH_CHAR (temp_pos))
		DEC_BOTH (from, from_byte);
	      if (mathexit)
		{
		  mathexit = 0;
		  goto open2;
		}
	      mathexit = 1;

	    case Sclose:
	      if (!++depth) goto done2;
	      break;

	    case Sopen:
	    open2:
	      if (!--depth) goto done2;
	      if (depth < min_depth)
		Fsignal (Qscan_error,
			 Fcons (build_string ("Containing expression ends prematurely"),
				Fcons (make_number (last_good),
				       Fcons (make_number (from), Qnil))));
	      break;

	    case Sendcomment:
	      if (!parse_sexp_ignore_comments)
		break;
	      found = back_comment (from, from_byte, stop, comnested, comstyle,
				    &out_charpos, &out_bytepos);
	      /* FIXME:  if found == -1, then it really wasn't a comment-end.
		 For single-char Sendcomment, we can't do much about it apart
		 from skipping the char.
		 For 2-char endcomments, we could try again, taking both
		 chars as separate entities, but it's a lot of trouble
		 for very little gain, so we don't bother either.  -sm */
	      if (found != -1)
		from = out_charpos, from_byte = out_bytepos;
	      break;

	    case Scomment_fence:
	    case Sstring_fence:
	      while (1)
		{
		  DEC_BOTH (from, from_byte);
		  if (from == stop) goto lose;
		  UPDATE_SYNTAX_TABLE_BACKWARD (from);
		  if (!char_quoted (from, from_byte) 
		      && (c = FETCH_CHAR (from_byte),
			  SYNTAX_WITH_MULTIBYTE_CHECK (c) == code))
		    break;
		}
	      if (code == Sstring_fence && !depth && sexpflag) goto done2;
	      break;
	      
	    case Sstring:
	      stringterm = FETCH_CHAR (from_byte);
	      while (1)
		{
		  if (from == stop) goto lose;
		  temp_pos = from_byte;
		  if (! NILP (current_buffer->enable_multibyte_characters))
		    DEC_POS (temp_pos);
		  else
		    temp_pos--;
		  UPDATE_SYNTAX_TABLE_BACKWARD (from - 1);
		  if (!char_quoted (from - 1, temp_pos)
		      && stringterm == (c = FETCH_CHAR (temp_pos))
		      && SYNTAX_WITH_MULTIBYTE_CHECK (c) == Sstring)
		    break;
		  DEC_BOTH (from, from_byte);
		}
	      DEC_BOTH (from, from_byte);
	      if (!depth && sexpflag) goto done2;
	      break;
	    }
	}

      /* Reached start of buffer.  Error if within object, return nil if between */
      if (depth) goto lose;

      immediate_quit = 0;
      return Qnil;

    done2:
      count++;
    }


  immediate_quit = 0;
  XSETFASTINT (val, from);
  return val;

 lose:
  Fsignal (Qscan_error,
	   Fcons (build_string ("Unbalanced parentheses"),
		  Fcons (make_number (last_good),
			 Fcons (make_number (from), Qnil))));

  /* NOTREACHED */
}

DEFUN ("scan-lists", Fscan_lists, Sscan_lists, 3, 3, 0,
  "Scan from character number FROM by COUNT lists.\n\
Returns the character number of the position thus found.\n\
\n\
If DEPTH is nonzero, paren depth begins counting from that value,\n\
only places where the depth in parentheses becomes zero\n\
are candidates for stopping; COUNT such places are counted.\n\
Thus, a positive value for DEPTH means go out levels.\n\
\n\
Comments are ignored if `parse-sexp-ignore-comments' is non-nil.\n\
\n\
If the beginning or end of (the accessible part of) the buffer is reached\n\
and the depth is wrong, an error is signaled.\n\
If the depth is right but the count is not used up, nil is returned.")
  (from, count, depth)
     Lisp_Object from, count, depth;
{
  CHECK_NUMBER (from, 0);
  CHECK_NUMBER (count, 1);
  CHECK_NUMBER (depth, 2);

  return scan_lists (XINT (from), XINT (count), XINT (depth), 0);
}

DEFUN ("scan-sexps", Fscan_sexps, Sscan_sexps, 2, 2, 0,
  "Scan from character number FROM by COUNT balanced expressions.\n\
If COUNT is negative, scan backwards.\n\
Returns the character number of the position thus found.\n\
\n\
Comments are ignored if `parse-sexp-ignore-comments' is non-nil.\n\
\n\
If the beginning or end of (the accessible part of) the buffer is reached\n\
in the middle of a parenthetical grouping, an error is signaled.\n\
If the beginning or end is reached between groupings\n\
but before count is used up, nil is returned.")
  (from, count)
     Lisp_Object from, count;
{
  CHECK_NUMBER (from, 0);
  CHECK_NUMBER (count, 1);

  return scan_lists (XINT (from), XINT (count), 0, 1);
}

DEFUN ("backward-prefix-chars", Fbackward_prefix_chars, Sbackward_prefix_chars,
  0, 0, 0,
  "Move point backward over any number of chars with prefix syntax.\n\
This includes chars with \"quote\" or \"prefix\" syntax (' or p).")
  ()
{
  int beg = BEGV;
  int opoint = PT;
  int opoint_byte = PT_BYTE;
  int pos = PT;
  int pos_byte = PT_BYTE;
  int c;

  if (pos <= beg) 
    {
      SET_PT_BOTH (opoint, opoint_byte);

      return Qnil;
    }

  SETUP_SYNTAX_TABLE (pos, -1);

  DEC_BOTH (pos, pos_byte);

  while (!char_quoted (pos, pos_byte)
	 /* Previous statement updates syntax table.  */
	 && ((c = FETCH_CHAR (pos_byte), SYNTAX (c) == Squote)
	     || SYNTAX_PREFIX (c)))
    {
      opoint = pos;
      opoint_byte = pos_byte;

      if (pos + 1 > beg)
	DEC_BOTH (pos, pos_byte);
    }

  SET_PT_BOTH (opoint, opoint_byte);

  return Qnil;
}

/* Parse forward from FROM / FROM_BYTE to END,
   assuming that FROM has state OLDSTATE (nil means FROM is start of function),
   and return a description of the state of the parse at END.
   If STOPBEFORE is nonzero, stop at the start of an atom.
   If COMMENTSTOP is 1, stop at the start of a comment.
   If COMMENTSTOP is -1, stop at the start or end of a comment,
   after the beginning of a string, or after the end of a string.  */

static void
scan_sexps_forward (stateptr, from, from_byte, end, targetdepth,
		    stopbefore, oldstate, commentstop)
     struct lisp_parse_state *stateptr;
     register int from;
     int end, targetdepth, stopbefore;
     Lisp_Object oldstate;
     int commentstop;
{
  struct lisp_parse_state state;

  register enum syntaxcode code;
  int c1;
  int comnested;
  struct level { int last, prev; };
  struct level levelstart[100];
  register struct level *curlevel = levelstart;
  struct level *endlevel = levelstart + 100;
  register int depth;	/* Paren depth of current scanning location.
			   level - levelstart equals this except
			   when the depth becomes negative.  */
  int mindepth;		/* Lowest DEPTH value seen.  */
  int start_quoted = 0;		/* Nonzero means starting after a char quote */
  Lisp_Object tem;
  int prev_from;		/* Keep one character before FROM.  */
  int prev_from_byte;
  int prev_from_syntax;
  int boundary_stop = commentstop == -1;
  int nofence;
  int found;
  int out_bytepos, out_charpos;
  int temp;

  prev_from = from;
  prev_from_byte = from_byte;
  if (from != BEGV)
    DEC_BOTH (prev_from, prev_from_byte);

  /* Use this macro instead of `from++'.  */
#define INC_FROM				\
do { prev_from = from;				\
     prev_from_byte = from_byte; 		\
     prev_from_syntax				\
       = SYNTAX_WITH_FLAGS (FETCH_CHAR (prev_from_byte)); \
     INC_BOTH (from, from_byte);		\
     UPDATE_SYNTAX_TABLE_FORWARD (from);	\
  } while (0)

  immediate_quit = 1;
  QUIT;

  if (NILP (oldstate))
    {
      depth = 0;
      state.instring = -1;
      state.incomment = 0;
      state.comstyle = 0;	/* comment style a by default.  */
      state.comstr_start = -1;	/* no comment/string seen.  */
    }
  else
    {
      tem = Fcar (oldstate);
      if (!NILP (tem))
	depth = XINT (tem);
      else
	depth = 0;

      oldstate = Fcdr (oldstate);
      oldstate = Fcdr (oldstate);
      oldstate = Fcdr (oldstate);
      tem = Fcar (oldstate);
      /* Check whether we are inside string_fence-style string: */
      state.instring = (!NILP (tem) 
			? (INTEGERP (tem) ? XINT (tem) : ST_STRING_STYLE) 
			: -1);

      oldstate = Fcdr (oldstate);
      tem = Fcar (oldstate);
      state.incomment = (!NILP (tem)
			 ? (INTEGERP (tem) ? XINT (tem) : -1)
			 : 0);

      oldstate = Fcdr (oldstate);
      tem = Fcar (oldstate);
      start_quoted = !NILP (tem);

      /* if the eighth element of the list is nil, we are in comment
	 style a.  If it is non-nil, we are in comment style b */
      oldstate = Fcdr (oldstate);
      oldstate = Fcdr (oldstate);
      tem = Fcar (oldstate);
      state.comstyle = NILP (tem) ? 0 : (EQ (tem, Qsyntax_table) 
					 ? ST_COMMENT_STYLE : 1);

      oldstate = Fcdr (oldstate);
      tem = Fcar (oldstate);
      state.comstr_start = NILP (tem) ? -1 : XINT (tem) ;
      oldstate = Fcdr (oldstate);
      tem = Fcar (oldstate);
      while (!NILP (tem))		/* >= second enclosing sexps.  */
	{
	  /* curlevel++->last ran into compiler bug on Apollo */
	  curlevel->last = XINT (Fcar (tem));
	  if (++curlevel == endlevel)
	    curlevel--; /* error ("Nesting too deep for parser"); */
	  curlevel->prev = -1;
	  curlevel->last = -1;
	  tem = Fcdr (tem);
	}
    }
  state.quoted = 0;
  mindepth = depth;

  curlevel->prev = -1;
  curlevel->last = -1;

  SETUP_SYNTAX_TABLE (prev_from, 1);
  prev_from_syntax = SYNTAX_WITH_FLAGS (FETCH_CHAR (prev_from_byte));
  UPDATE_SYNTAX_TABLE_FORWARD (from);

  /* Enter the loop at a place appropriate for initial state.  */

  if (state.incomment)
    goto startincomment;
  if (state.instring >= 0)
    {
      nofence = state.instring != ST_STRING_STYLE;
      if (start_quoted)
	goto startquotedinstring;
      goto startinstring;
    }
  else if (start_quoted)
    goto startquoted;

#if 0 /* This seems to be redundant with the identical code above.  */
  SETUP_SYNTAX_TABLE (prev_from, 1);
  prev_from_syntax = SYNTAX_WITH_FLAGS (FETCH_CHAR (prev_from_byte));
  UPDATE_SYNTAX_TABLE_FORWARD (from);
#endif

  while (from < end)
    {
      INC_FROM;
      code = prev_from_syntax & 0xff;

      if (code == Scomment)
	{
	  state.comstyle = SYNTAX_FLAGS_COMMENT_STYLE (prev_from_syntax);
	  state.incomment = (SYNTAX_FLAGS_COMMENT_NESTED (prev_from_syntax) ?
			     1 : -1);
	  state.comstr_start = prev_from;
	}
      else if (code == Scomment_fence)
	{
	  /* Record the comment style we have entered so that only
	     the comment-end sequence of the same style actually
	     terminates the comment section.  */
	  state.comstyle = ST_COMMENT_STYLE;
	  state.incomment = -1;
	  state.comstr_start = prev_from;
	  code = Scomment;
	}
     else if (from < end)
	if (SYNTAX_FLAGS_COMSTART_FIRST (prev_from_syntax))
	  if (c1 = FETCH_CHAR (from_byte),
	      SYNTAX_COMSTART_SECOND (c1))
	    /* Duplicate code to avoid a complex if-expression
	       which causes trouble for the SGI compiler.  */
	    {
	      /* Record the comment style we have entered so that only
		 the comment-end sequence of the same style actually
		 terminates the comment section.  */
	      state.comstyle = SYNTAX_COMMENT_STYLE (FETCH_CHAR (from_byte));
	      comnested = SYNTAX_FLAGS_COMMENT_NESTED (prev_from_syntax);
	      comnested = comnested || SYNTAX_COMMENT_NESTED (c1);
	      state.incomment = comnested ? 1 : -1;
	      state.comstr_start = prev_from;
	      INC_FROM;
	      code = Scomment;
	    }

      if (SYNTAX_FLAGS_PREFIX (prev_from_syntax))
	continue;
      switch (SWITCH_ENUM_CAST (code))
	{
	case Sescape:
	case Scharquote:
	  if (stopbefore) goto stop;  /* this arg means stop at sexp start */
	  curlevel->last = prev_from;
	startquoted:
	  if (from == end) goto endquoted;
	  INC_FROM;
	  goto symstarted;
	  /* treat following character as a word constituent */
	case Sword:
	case Ssymbol:
	  if (stopbefore) goto stop;  /* this arg means stop at sexp start */
	  curlevel->last = prev_from;
	symstarted:
	  while (from < end)
	    {
	      /* Some compilers can't handle this inside the switch.  */
	      temp = SYNTAX (FETCH_CHAR (from_byte));
	      switch (temp)
		{
		case Scharquote:
		case Sescape:
		  INC_FROM;
		  if (from == end) goto endquoted;
		  break;
		case Sword:
		case Ssymbol:
		case Squote:
		  break;
		default:
		  goto symdone;
		}
	      INC_FROM;
	    }
	symdone:
	  curlevel->prev = curlevel->last;
	  break;

	case Scomment:
	  if (commentstop || boundary_stop) goto done;
	startincomment:
	  /* The (from == BEGV) test was to enter the loop in the middle so
	     that we find a 2-char comment ender even if we start in the
	     middle of it.  We don't want to do that if we're just at the
	     beginning of the comment (think of (*) ... (*)).  */
	  found = forw_comment (from, from_byte, end,
				state.incomment, state.comstyle,
				(from == BEGV || from < state.comstr_start + 3)
				? 0 : prev_from_syntax,
				&out_charpos, &out_bytepos, &state.incomment);
	  from = out_charpos; from_byte = out_bytepos;
	  /* Beware!  prev_from and friends are invalid now.
	     Luckily, the `done' doesn't use them and the INC_FROM
	     sets them to a sane value without looking at them. */
	  if (!found) goto done;
	  INC_FROM;
	  state.incomment = 0;
	  state.comstyle = 0;	/* reset the comment style */
	  if (boundary_stop) goto done;
	  break;

	case Sopen:
	  if (stopbefore) goto stop;  /* this arg means stop at sexp start */
	  depth++;
	  /* curlevel++->last ran into compiler bug on Apollo */
	  curlevel->last = prev_from;
	  if (++curlevel == endlevel)
	    curlevel--; /* error ("Nesting too deep for parser"); */
	  curlevel->prev = -1;
	  curlevel->last = -1;
	  if (targetdepth == depth) goto done;
	  break;

	case Sclose:
	  depth--;
	  if (depth < mindepth)
	    mindepth = depth;
	  if (curlevel != levelstart)
	    curlevel--;
	  curlevel->prev = curlevel->last;
	  if (targetdepth == depth) goto done;
	  break;

	case Sstring:
	case Sstring_fence:
	  state.comstr_start = from - 1;
	  if (stopbefore) goto stop;  /* this arg means stop at sexp start */
	  curlevel->last = prev_from;
	  state.instring = (code == Sstring 
			    ? (FETCH_CHAR (prev_from_byte))
			    : ST_STRING_STYLE);
	  if (boundary_stop) goto done;
	startinstring:
	  {
	    nofence = state.instring != ST_STRING_STYLE;
	    
	    while (1)
	      {
		int c;

		if (from >= end) goto done;
		c = FETCH_CHAR (from_byte);
		/* Some compilers can't handle this inside the switch.  */
		temp = SYNTAX (c);

		/* Check TEMP here so that if the char has
		   a syntax-table property which says it is NOT
		   a string character, it does not end the string.  */
		if (nofence && c == state.instring && temp == Sstring)
		  break;

		switch (temp)
		  {
		  case Sstring_fence:
		    if (!nofence) goto string_end;
		    break;
		  case Scharquote:
		  case Sescape:
		    INC_FROM;
		  startquotedinstring:
		    if (from >= end) goto endquoted;
		  }
		INC_FROM;
	      }
	  }
	string_end:
	  state.instring = -1;
	  curlevel->prev = curlevel->last;
	  INC_FROM;
	  if (boundary_stop) goto done;
	  break;

	case Smath:
	  break;
	}
    }
  goto done;

 stop:   /* Here if stopping before start of sexp. */
  from = prev_from;    /* We have just fetched the char that starts it; */
  goto done; /* but return the position before it. */

 endquoted:
  state.quoted = 1;
 done:
  state.depth = depth;
  state.mindepth = mindepth;
  state.thislevelstart = curlevel->prev;
  state.prevlevelstart
    = (curlevel == levelstart) ? -1 : (curlevel - 1)->last;
  state.location = from;
  state.levelstarts = Qnil;
  while (--curlevel >= levelstart)
      state.levelstarts = Fcons (make_number (curlevel->last),
				 state.levelstarts);
  immediate_quit = 0;

  *stateptr = state;
}

/* This comment supplies the doc string for parse-partial-sexp,
   for make-docfile to see.  We cannot put this in the real DEFUN
   due to limits in the Unix cpp.

DEFUN ("parse-partial-sexp", Ffoo, Sfoo, 2, 6, 0,
  "Parse Lisp syntax starting at FROM until TO; return status of parse at TO.\n\
Parsing stops at TO or when certain criteria are met;\n\
 point is set to where parsing stops.\n\
If fifth arg STATE is omitted or nil,\n\
 parsing assumes that FROM is the beginning of a function.\n\
Value is a list of ten elements describing final state of parsing:\n\
 0. depth in parens.\n\
 1. character address of start of innermost containing list; nil if none.\n\
 2. character address of start of last complete sexp terminated.\n\
 3. non-nil if inside a string.\n\
    (it is the character that will terminate the string,\n\
     or t if the string should be terminated by a generic string delimiter.)\n\
 4. nil if outside a comment, t if inside a non-nestable comment, \n\
    else an integer (the current comment nesting).\n\
 5. t if following a quote character.\n\
 6. the minimum paren-depth encountered during this scan.\n\
 7. t if in a comment of style b; symbol `syntax-table' if the comment\n\
    should be terminated by a generic comment delimiter.\n\
 8. character address of start of comment or string; nil if not in one.\n\
 9. Intermediate data for continuation of parsing (subject to change).\n\
If third arg TARGETDEPTH is non-nil, parsing stops if the depth\n\
in parentheses becomes equal to TARGETDEPTH.\n\
Fourth arg STOPBEFORE non-nil means stop when come to\n\
 any character that starts a sexp.\n\
Fifth arg STATE is a nine-element list like what this function returns.\n\
 It is used to initialize the state of the parse.  Elements number 1, 2, 6\n\
 and 8 are ignored; you can leave off element 8 (the last) entirely.\n\
Sixth arg COMMENTSTOP non-nil means stop at the start of a comment.\n\
 If it is symbol `syntax-table', stop after the start of a comment or a\n\
 string, or after end of a comment or a string.")
  (from, to, targetdepth, stopbefore, state, commentstop)
*/

DEFUN ("parse-partial-sexp", Fparse_partial_sexp, Sparse_partial_sexp, 2, 6, 0,
  0 /* See immediately above */)
  (from, to, targetdepth, stopbefore, oldstate, commentstop)
     Lisp_Object from, to, targetdepth, stopbefore, oldstate, commentstop;
{
  struct lisp_parse_state state;
  int target;

  if (!NILP (targetdepth))
    {
      CHECK_NUMBER (targetdepth, 3);
      target = XINT (targetdepth);
    }
  else
    target = -100000;		/* We won't reach this depth */

  validate_region (&from, &to);
  scan_sexps_forward (&state, XINT (from), CHAR_TO_BYTE (XINT (from)),
		      XINT (to),
		      target, !NILP (stopbefore), oldstate,
		      (NILP (commentstop) 
		       ? 0 : (EQ (commentstop, Qsyntax_table) ? -1 : 1)));

  SET_PT (state.location);
  
  return Fcons (make_number (state.depth),
	   Fcons (state.prevlevelstart < 0 ? Qnil : make_number (state.prevlevelstart),
	     Fcons (state.thislevelstart < 0 ? Qnil : make_number (state.thislevelstart),
	       Fcons (state.instring >= 0 
		      ? (state.instring == ST_STRING_STYLE 
			 ? Qt : make_number (state.instring)) : Qnil,
		 Fcons (state.incomment < 0 ? Qt :
			(state.incomment == 0 ? Qnil :
			 make_number (state.incomment)),
		   Fcons (state.quoted ? Qt : Qnil,
		     Fcons (make_number (state.mindepth),
		       Fcons ((state.comstyle 
			       ? (state.comstyle == ST_COMMENT_STYLE
				  ? Qsyntax_table : Qt) :
			       Qnil),
			      Fcons (((state.incomment
				       || (state.instring >= 0))
				      ? make_number (state.comstr_start)
				      : Qnil),
				     Fcons (state.levelstarts, Qnil))))))))));
}

void
init_syntax_once ()
{
  register int i, c;
  Lisp_Object temp;

  /* This has to be done here, before we call Fmake_char_table.  */
  Qsyntax_table = intern ("syntax-table");
  staticpro (&Qsyntax_table);

  /* Intern this now in case it isn't already done.
     Setting this variable twice is harmless.
     But don't staticpro it here--that is done in alloc.c.  */
  Qchar_table_extra_slots = intern ("char-table-extra-slots");

  /* Create objects which can be shared among syntax tables.  */
  Vsyntax_code_object = Fmake_vector (make_number (Smax), Qnil);
  for (i = 0; i < XVECTOR (Vsyntax_code_object)->size; i++)
    XVECTOR (Vsyntax_code_object)->contents[i]
      = Fcons (make_number (i), Qnil);

  /* Now we are ready to set up this property, so we can
     create syntax tables.  */
  Fput (Qsyntax_table, Qchar_table_extra_slots, make_number (0));

  temp = XVECTOR (Vsyntax_code_object)->contents[(int) Swhitespace];

  Vstandard_syntax_table = Fmake_char_table (Qsyntax_table, temp);

  temp = XVECTOR (Vsyntax_code_object)->contents[(int) Sword];
  for (i = 'a'; i <= 'z'; i++)
    SET_RAW_SYNTAX_ENTRY (Vstandard_syntax_table, i, temp);
  for (i = 'A'; i <= 'Z'; i++)
    SET_RAW_SYNTAX_ENTRY (Vstandard_syntax_table, i, temp);
  for (i = '0'; i <= '9'; i++)
    SET_RAW_SYNTAX_ENTRY (Vstandard_syntax_table, i, temp);

  SET_RAW_SYNTAX_ENTRY (Vstandard_syntax_table, '$', temp);
  SET_RAW_SYNTAX_ENTRY (Vstandard_syntax_table, '%', temp);

  SET_RAW_SYNTAX_ENTRY (Vstandard_syntax_table, '(',
			Fcons (make_number (Sopen), make_number (')')));
  SET_RAW_SYNTAX_ENTRY (Vstandard_syntax_table, ')',
			Fcons (make_number (Sclose), make_number ('(')));
  SET_RAW_SYNTAX_ENTRY (Vstandard_syntax_table, '[',
			Fcons (make_number (Sopen), make_number (']')));
  SET_RAW_SYNTAX_ENTRY (Vstandard_syntax_table, ']',
			Fcons (make_number (Sclose), make_number ('[')));
  SET_RAW_SYNTAX_ENTRY (Vstandard_syntax_table, '{',
			Fcons (make_number (Sopen), make_number ('}')));
  SET_RAW_SYNTAX_ENTRY (Vstandard_syntax_table, '}',
			Fcons (make_number (Sclose), make_number ('{')));
  SET_RAW_SYNTAX_ENTRY (Vstandard_syntax_table, '"',
			Fcons (make_number ((int) Sstring), Qnil));
  SET_RAW_SYNTAX_ENTRY (Vstandard_syntax_table, '\\',
			Fcons (make_number ((int) Sescape), Qnil));

  temp = XVECTOR (Vsyntax_code_object)->contents[(int) Ssymbol];
  for (i = 0; i < 10; i++)
    {
      c = "_-+*/&|<>="[i];
      SET_RAW_SYNTAX_ENTRY (Vstandard_syntax_table, c, temp);
    }

  temp = XVECTOR (Vsyntax_code_object)->contents[(int) Spunct];
  for (i = 0; i < 12; i++)
    {
      c = ".,;:?!#@~^'`"[i];
      SET_RAW_SYNTAX_ENTRY (Vstandard_syntax_table, c, temp);
    }

  /* All multibyte characters have syntax `word' by default.  */
  temp = XVECTOR (Vsyntax_code_object)->contents[(int) Sword];
  for (i = CHAR_TABLE_SINGLE_BYTE_SLOTS; i < CHAR_TABLE_ORDINARY_SLOTS; i++)
    XCHAR_TABLE (Vstandard_syntax_table)->contents[i] = temp;
}

void
syms_of_syntax ()
{
  Qsyntax_table_p = intern ("syntax-table-p");
  staticpro (&Qsyntax_table_p);

  staticpro (&Vsyntax_code_object);

  Qscan_error = intern ("scan-error");
  staticpro (&Qscan_error);
  Fput (Qscan_error, Qerror_conditions,
	Fcons (Qscan_error, Fcons (Qerror, Qnil)));
  Fput (Qscan_error, Qerror_message,
	build_string ("Scan error"));

  DEFVAR_BOOL ("parse-sexp-ignore-comments", &parse_sexp_ignore_comments,
    "Non-nil means `forward-sexp', etc., should treat comments as whitespace.");

  DEFVAR_BOOL ("parse-sexp-lookup-properties", &parse_sexp_lookup_properties,
    "Non-nil means `forward-sexp', etc., grant `syntax-table' property.\n\
The value of this property should be either a syntax table, or a cons\n\
of the form (SYNTAXCODE . MATCHCHAR), SYNTAXCODE being the numeric\n\
syntax code, MATCHCHAR being nil or the character to match (which is\n\
relevant only for open/close type.");

  words_include_escapes = 0;
  DEFVAR_BOOL ("words-include-escapes", &words_include_escapes,
    "Non-nil means `forward-word', etc., should treat escape chars part of words.");

  DEFVAR_BOOL ("multibyte-syntax-as-symbol", &multibyte_syntax_as_symbol,
    "Non-nil means `scan-sexps' treats all multibyte characters as symbol.");
  multibyte_syntax_as_symbol = 0;

  DEFVAR_BOOL ("open-paren-in-column-0-is-defun-start",
	       &open_paren_in_column_0_is_defun_start,
    "Non-nil means an open paren in column 0 denotes the start of a defun.");
  open_paren_in_column_0_is_defun_start = 1;

  defsubr (&Ssyntax_table_p);
  defsubr (&Ssyntax_table);
  defsubr (&Sstandard_syntax_table);
  defsubr (&Scopy_syntax_table);
  defsubr (&Sset_syntax_table);
  defsubr (&Schar_syntax);
  defsubr (&Smatching_paren);
  defsubr (&Sstring_to_syntax);
  defsubr (&Smodify_syntax_entry);
  defsubr (&Sdescribe_syntax);

  defsubr (&Sforward_word);

  defsubr (&Sskip_chars_forward);
  defsubr (&Sskip_chars_backward);
  defsubr (&Sskip_syntax_forward);
  defsubr (&Sskip_syntax_backward);

  defsubr (&Sforward_comment);
  defsubr (&Sscan_lists);
  defsubr (&Sscan_sexps);
  defsubr (&Sbackward_prefix_chars);
  defsubr (&Sparse_partial_sexp);
}
