;;; scroll-all.el --- scroll all buffers together minor mode

;; Copyright (C) 1997 Free Software Foundation, Inc.

;; Author: Gary D. Foster <Gary.Foster@corp.sun.com>
;; Keywords: scroll crisp brief lock

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
;;    This mode allows multiple buffers to be 'locked' so that scrolling
;;    up or down lines in any buffer causes all the buffers to mirror
;;    the scrolling.  It hooks into the post-command-hook to check for
;;    potential scrolling commands and if we're locked, mirrors them in all
;;    windows.	This allows us to grab line-at-a-time scrolling as well as
;;    screen-at-a-time scrolling, and doesn't remap any of the keyboard
;;    commands to do it.

;; You can enable and disable this mode with the 'scroll-all-mode' command.

;; Suggestions/ideas from:
;;    Rick Macdonald <rickm@vsl.com>
;;    Anders Lindgren <andersl@csd.uu.se>

;;; Code:

(defvar running-xemacs (string-match "XEmacs\\|Lucid" emacs-version))

;;;###autoload
(defcustom scroll-all-mode nil
  "Control/track scroll locking.

Setting this variable directly does not take effect;
use either M-x customize or the function `scroll-all-mode'."
  :set (lambda (symbol value) (scroll-all-mode (if value 1 0)))
  :initialize 'custom-initialize-default
  :require 'scroll-all
  :type 'boolean
  :group 'windows)

(if running-xemacs
    (add-minor-mode 'scroll-all-mode " *SL*")
  (or (assq 'scroll-all-mode minor-mode-alist)
      (setq minor-mode-alist
	    (cons '(scroll-all-mode " *SL*") minor-mode-alist))))

(defun scroll-all-scroll-down-all (arg)
  "Scroll down all visible windows."
  (interactive "P")
  (let ((num-windows (count-windows))
	(count 1))
    (if (> num-windows 1)
	(progn (other-window 1)
               (while (< count num-windows)
                 (if (not (eq (point) (point-max)))
                     (progn (call-interactively 'next-line)))
                 (other-window 1)
                 (setq count (1+ count)))))))

(defun scroll-all-scroll-up-all (arg)
  "Scroll up all visible windows."
  (interactive "P")
  (let ((num-windows (count-windows))
	(count 1))
    (if (> num-windows 1)
	(progn (other-window 1)
               (while (< count num-windows)
                 (if (not (eq (point) (point-min)))
                     (progn (call-interactively 'previous-line)))
                 (other-window 1)
                 (setq count (1+ count)))))))

(defun scroll-all-page-down-all (arg)
  "Page down in all visible windows."
  (interactive "P")
  (let ((num-windows (count-windows))
	(count 1))
    (if (> num-windows 1)
	(progn (other-window 1)
	       (while (< count num-windows)
		 (call-interactively 'scroll-up)
		 (other-window 1)
		 (setq count (1+ count)))))))

(defun scroll-all-page-up-all (arg)
  "Page up in all visible windows."
  (interactive "P")
  (let ((num-windows (count-windows))
	(count 1))
    (if (> num-windows 1)
	(progn (other-window 1)
	       (while (< count num-windows)
		 (call-interactively 'scroll-down)
		 (other-window 1)
		 (setq count (1+ count)))))))


(defun scroll-all-check-to-scroll ()
  "Check `this-command' to see if a scroll is to be done."
  (cond
   ((eq this-command 'next-line)
    (call-interactively 'scroll-all-scroll-down-all))
   ((eq this-command 'previous-line)
    (call-interactively 'scroll-all-scroll-up-all))
   ((eq this-command 'scroll-up)
    (call-interactively 'scroll-all-page-down-all))
   ((eq this-command 'scroll-down)
    (call-interactively 'scroll-all-page-up-all))))


;;;###autoload
(defun scroll-all-mode (&optional arg)
  "Toggle Scroll-All minor mode.
With ARG, turn Scroll-All minor mode on if ARG is positive, off otherwise.
When Scroll-All mode is on, scrolling commands entered in one window
apply to all visible windows in the same frame."
  (interactive "P")
  (setq scroll-all-mode
 	(if (null arg) (not scroll-all-mode)
 	  (> (prefix-numeric-value arg) 0)))
  (if scroll-all-mode
      (add-hook 'post-command-hook 'scroll-all-check-to-scroll)
    (remove-hook 'post-command-hook 'scroll-all-check-to-scroll)))

(provide 'scroll-all)

;;; scroll-all.el ends here
