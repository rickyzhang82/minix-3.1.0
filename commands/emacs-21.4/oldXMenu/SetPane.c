#include "copyright.h"

/* $Header: /cvsup/minix/src/commands/emacs-21.4/oldXMenu/SetPane.c,v 1.3 2005/09/21 14:35:40 beng Exp $ */
/* Copyright    Massachusetts Institute of Technology    1985	*/

/*
 * XMenu:	MIT Project Athena, X Window system menu package
 *
 *	XMenuSetPane - Set a menu pane to be active or inactive.
 *
 *	Author:		Tony Della Fera, DEC
 *			August, 1985
 *
 */

#include "XMenuInt.h"

int
XMenuSetPane(menu, p_num, active)
    register XMenu *menu;	/* Menu object to be modified. */
    register int p_num;		/* Pane number to be modified. */
    register int active;	/* Make selection active? */
{
    register XMPane *p_ptr;	/* XMPane pointer. */

    /*
     * Find the right pane.
     */
    p_ptr = _XMGetPanePtr(menu, p_num);
    if (p_ptr == NULL) return(XM_FAILURE);

    /*
     * Set its active switch.
     */
    p_ptr->active = active;
    if (p_ptr->active == False) p_ptr->activated = False;

    /*
     * Return the pane number just set.
     */
    _XMErrorCode = XME_NO_ERROR;
    return(p_num);
}
