;;; refill.el --- `auto-fill' by refilling paragraphs on changes

;; Copyright (C) 2000 Free Software Foundation, Inc.

;; Author: Dave Love <fx@gnu.org>
;; Keywords: wp

;; This file is part of GNU Emacs.

;; GNU Emacs is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 2, or (at your option)
;; any later version.

;; GNU Emacs is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with GNU Emacs; see the file COPYING.  If not, write to the
;; Free Software Foundation, Inc., 59 Temple Place - Suite 330,
;; Boston, MA 02111-1307, USA.

;;; Commentary:

;; Provides a mode where paragraphs are refilled after changes in them
;; (using `after-change-functions').  This gives something akin to typical
;; word processor-style filling.  We restrict refilling due to
;; self-insertion to the characters which trigger auto-fill.

;; It partly satisfies a todo item in enriched.el for some value of
;; `without slowing down editing too much'.  It doesn't attempt to do
;; anything (using `window-size-change-functions'?) about resizing
;; windows -- who cares?

;; This implementation is probably fragile and missing some special
;; cases -- not extensively tested.  Yanking paragraph breaks, for
;; instance, won't DTRT by refilling all the relevant paragraphs.

;; You could do it a bit more efficiently (and robustly?) with just an
;; auto-fill function, but that doesn't cope with changes other than
;; through self-insertion.  (Using auto-fill and after-change
;; functions together didn't seem winning.)  This could probably
;; benefit from a less-general and faster `fill-paragraph-function',
;; ideally as a primitive.

;; The work is done in a local post-command hook but only if
;; `refill-doit' has been set by the after-change function.  Using
;; `post-command-hook' ensures simply that refilling only happens
;; once per command.

;; [Per Abrahamsen's maniac.el does a similar thing, but operates from
;; post-command-hook.  I don't understand the statement in it that
;; after-change-functions don't work for this purpose; perhaps there was
;; some Emacs bug at the time.  ISTR maniac has problems with
;; whitespace at the end of paragraphs.]

;;; Code:

(defvar refill-ignorable-overlay nil
  "Portion of the most recently filled paragraph not needing filling.
This is used to optimize refilling.")
(make-variable-buffer-local 'refill-ignorable-overlay)

(defun refill-adjust-ignorable-overlay (overlay afterp beg end &optional len)
  "Adjust OVERLAY to not include the about-to-be-modified region."
  (when (not afterp)
    (save-excursion
      (goto-char beg)
      (forward-line -1)
      (if (<= (point) (overlay-start overlay))
	  ;; Just get OVERLAY out of the way
	  (move-overlay overlay 1 1)
	;; Make overlay contain only the region 
	(move-overlay overlay (overlay-start overlay) (point))))))

(defun refill-fill-paragraph-at (pos &optional arg)
  "Like `fill-paragraph' at POS, but don't delete whitespace at paragraph end."
  (let (fill-pfx)
    (save-excursion
      (goto-char pos)
      (forward-paragraph)
      (skip-syntax-backward "-")
      (let ((end (point))
	    (beg (progn (backward-paragraph) (point)))
	    (obeg (overlay-start refill-ignorable-overlay))
	    (oend (overlay-end refill-ignorable-overlay)))
	(goto-char pos)
	(if (and (>= beg obeg) (< beg oend))
	    ;; Limit filling to the modified tail of the paragraph.
	    (let (;; When adaptive-fill-mode is enabled, the filling
		  ;; functions will attempt to set the fill prefix from
		  ;; the fake paragraph bounds we pass in, so set it
		  ;; ourselves first, using the real paragraph bounds.
		  (fill-prefix
		   (if (and adaptive-fill-mode
			    (or (null fill-prefix) (string= fill-prefix "")))
		       (fill-context-prefix beg end)
		     fill-prefix))
		  ;; Turn off adaptive-fill-mode temporarily
		  (adaptive-fill-mode nil))
	      (save-restriction
		(if use-hard-newlines
		    (fill-region oend end arg)
		  (fill-region-as-paragraph oend end arg)))
	      (setq fill-pfx fill-prefix)
	      (move-overlay refill-ignorable-overlay obeg (point)))
	  ;; Fill the whole paragraph
	  (setq fill-pfx
		(save-restriction
		  (if use-hard-newlines
		      (fill-region beg end arg)
		    (fill-region-as-paragraph beg end arg))))
	  (move-overlay refill-ignorable-overlay beg (point)))))
    (skip-line-prefix fill-pfx)))

(defun refill-fill-paragraph (arg)
  "Like `fill-paragraph' but don't delete whitespace at paragraph end."
  (refill-fill-paragraph-at (point) arg))

(defvar refill-doit nil
  "Non-nil means that `refill-post-command-function' does its processing.
Set by `refill-after-change-function' in `after-change-functions' and
unset by `refill-post-command-function' in `post-command-hook', and
sometimes `refill-pre-command-function' in `pre-command-hook'.  This
ensures refilling is only done once per command that causes a change,
regardless of the number of after-change calls from commands doing
complex processing.")
(make-variable-buffer-local 'refill-doit)

(defun refill-after-change-function (beg end len)
  "Function for `after-change-functions' which just sets `refill-doit'."
  (unless undo-in-progress
    (setq refill-doit end)))

(defun refill-post-command-function ()
  "Post-command function to do refilling (conditionally)."
  (when refill-doit ; there was a change
    ;; There's probably scope for more special cases here...
    (if (eq this-command 'self-insert-command)
	;; Treat self-insertion commands specially, since they don't
	;; always reset `refill-doit' -- for self-insertion commands that
	;; *don't* cause a refill, we want to leave it turned on so that
	;; any subsequent non-modification command will cause a refill.
	(when (aref auto-fill-chars (char-before))
	  ;; Respond to the same characters as auto-fill (other than
	  ;; newline, covered below).
	  (refill-fill-paragraph-at refill-doit)
	  (setq refill-doit nil))
      (cond
       ((or (eq this-command 'quoted-insert)
	    (eq this-command 'fill-paragraph)
	    (eq this-command 'fill-region))
	nil)
       ((or (eq this-command 'newline)
	    (eq this-command 'newline-and-indent)
	    (eq this-command 'open-line))
	;; Don't zap what was just inserted.
	(save-excursion
	  (beginning-of-line)		; for newline-and-indent
	  (skip-chars-backward "\n")
	  (save-restriction
	    (narrow-to-region (point-min) (point))
	    (refill-fill-paragraph-at refill-doit)))
	(widen)
	(save-excursion
	  (skip-chars-forward "\n")
	  (save-restriction
	    (narrow-to-region (line-beginning-position) (point-max))
	    (refill-fill-paragraph-at refill-doit))))
       (t
	(refill-fill-paragraph-at refill-doit)))
      (setq refill-doit nil))))

(defun refill-pre-command-function ()
  "Pre-command function to do refilling (conditionally)."
  (when (and refill-doit (not (eq this-command 'self-insert-command)))
    ;; A previous setting of `refill-doit' didn't result in a refill,
    ;; because it was a self-insert-command.  Since the next command is
    ;; something else, do the refill now.
    (refill-fill-paragraph-at refill-doit)
    (setq refill-doit nil)))

(defvar refill-late-fill-paragraph-function nil)

;;;###autoload
(define-minor-mode refill-mode
  "Toggle Refill minor mode.
With prefix arg, turn Refill mode on iff arg is positive.

When Refill mode is on, the current paragraph will be formatted when
changes are made within it.  Self-inserting characters only cause
refilling if they would cause auto-filling."
  nil " Refill" nil
  ;; This provides the test for recursive paragraph filling.
  (make-local-variable 'fill-paragraph-function)
  (if refill-mode
      (progn
	(add-hook 'after-change-functions 'refill-after-change-function nil t)
	(add-hook 'post-command-hook 'refill-post-command-function nil t)
	(add-hook 'pre-command-hook 'refill-pre-command-function nil t)
	(set (make-local-variable 'refill-late-fill-paragraph-function)
	     fill-paragraph-function)
	(set (make-local-variable 'fill-paragraph-function)
	     'refill-fill-paragraph)
	(setq refill-ignorable-overlay (make-overlay 1 1 nil nil t))
	(overlay-put refill-ignorable-overlay 'modification-hooks
		     '(refill-adjust-ignorable-overlay))
	(overlay-put refill-ignorable-overlay 'insert-behind-hooks
		     '(refill-adjust-ignorable-overlay))
	(auto-fill-mode 0))
    (remove-hook 'after-change-functions 'refill-after-change-function t)
    (remove-hook 'post-command-hook 'refill-post-command-function t)
    (delete-overlay refill-ignorable-overlay)
    (setq fill-paragraph-function refill-late-fill-paragraph-function)))

(provide 'refill)

;;; refill.el ends here
