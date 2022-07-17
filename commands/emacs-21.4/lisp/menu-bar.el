;;; menu-bar.el --- define a default menu bar

;; Copyright (C) 1993, 1994, 1995, 2000, 2001, 2002 Free Software Foundation, Inc.

;; Author: RMS
;; Maintainer: FSF
;; Keywords: internal, mouse

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

;; Avishai Yacobi suggested some menu rearrangements.

;;; Commentary:

;;; Code:

;;; User options:

(defcustom buffers-menu-max-size 10
  "*Maximum number of entries which may appear on the Buffers menu.
If this is 10, then only the ten most-recently-selected buffers are shown.
If this is nil, then all buffers are shown.
A large number or nil slows down menu responsiveness."
  :type '(choice integer
		 (const :tag "All" nil))
  :group 'mouse)

;; Don't clobber an existing menu-bar keymap, to preserve any menu-bar key
;; definitions made in loaddefs.el.
(or (lookup-key global-map [menu-bar])
    (define-key global-map [menu-bar] (make-sparse-keymap "menu-bar")))
(defvar menu-bar-help-menu (make-sparse-keymap "Help"))

;; Force Help item to come last, after the major mode's own items.
;; The symbol used to be called `help', but that gets confused with the
;; help key.
(setq menu-bar-final-items '(help-menu))

(define-key global-map [menu-bar help-menu] (cons "Help" menu-bar-help-menu))
(defvar menu-bar-tools-menu (make-sparse-keymap "Tools"))
(define-key global-map [menu-bar tools] (cons "Tools" menu-bar-tools-menu))
;; This definition is just to show what this looks like.
;; It gets overridden below when menu-bar-update-buffers is called.
(define-key global-map [menu-bar buffer]
  (cons "Buffers" (make-sparse-keymap "Buffers")))
(defvar menu-bar-options-menu (make-sparse-keymap "Options"))
(define-key global-map [menu-bar options]
  (cons "Options" menu-bar-options-menu))
(defvar menu-bar-edit-menu (make-sparse-keymap "Edit"))
(define-key global-map [menu-bar edit] (cons "Edit" menu-bar-edit-menu))
(defvar menu-bar-files-menu (make-sparse-keymap "File"))
(define-key global-map [menu-bar files] (cons "File" menu-bar-files-menu))

;; This alias is for compatibility with 19.28 and before.
(defvar menu-bar-file-menu menu-bar-files-menu)

;; The "File" menu items
(define-key menu-bar-files-menu [exit-emacs]
  '(menu-item "Exit Emacs" save-buffers-kill-emacs
	      :help "Save unsaved buffers, then exit"))

(define-key menu-bar-files-menu [separator-exit]
  '("--"))

;; Don't use delete-frame as event name because that is a special
;; event.
(define-key menu-bar-files-menu [delete-this-frame]
  '(menu-item "Delete Frame" delete-frame
	      :visible (fboundp 'delete-frame)
	      :enable (delete-frame-enabled-p)
	      :help "Delete currently selected frame"))
(define-key menu-bar-files-menu [make-frame-on-display]
  '(menu-item "New Frame on Display..." make-frame-on-display
	      :visible (fboundp 'make-frame-on-display)
	      :help "Open a new frame on another display"))
(define-key menu-bar-files-menu [make-frame]
  '(menu-item "New Frame" make-frame-command
	      :visible (fboundp 'make-frame-command)
	      :help "Open a new frame"))

(define-key menu-bar-files-menu [one-window]
  '(menu-item "Unsplit Windows" delete-other-windows
	      :enable (not (one-window-p t nil))
	      :help "Make selected window fill its frame"))

(define-key menu-bar-files-menu [split-window]
  '(menu-item "Split Window" split-window-vertically
	      :help "Split selected window in two"))

(define-key menu-bar-files-menu [separator-window]
  '(menu-item "--"))

(define-key menu-bar-files-menu [ps-print-region]
  '(menu-item "Postscript Print Region (B+W)" ps-print-region
	      :enable mark-active
	      :help "Pretty-print marked region in black and white to PostScript printer"))
(define-key menu-bar-files-menu [ps-print-buffer]
  '(menu-item "Postscript Print Buffer (B+W)" ps-print-buffer
	      :help "Pretty-print current buffer in black and white to PostScript printer"))
(define-key menu-bar-files-menu [ps-print-region-faces]
  '(menu-item "Postscript Print Region" ps-print-region-with-faces
	      :enable mark-active
	      :help "Pretty-print marked region to PostScript printer"))
(define-key menu-bar-files-menu [ps-print-buffer-faces]
  '(menu-item "Postscript Print Buffer" ps-print-buffer-with-faces
	      :help "Pretty-print current buffer to PostScript printer"))
(define-key menu-bar-files-menu [print-region]
  '(menu-item "Print Region" print-region
	      :enable mark-active
	      :help "Print region between mark and current position"))
(define-key menu-bar-files-menu [print-buffer]
  '(menu-item "Print Buffer" print-buffer
	      :help "Print current buffer with page headings"))

(define-key menu-bar-files-menu [separator-print]
  '(menu-item "--"))

(define-key menu-bar-files-menu [recover-session]
  '(menu-item "Recover Crashed Session..." recover-session
	      :enable (and auto-save-list-file-prefix
			   (file-directory-p
                            (file-name-directory auto-save-list-file-prefix))
                           (directory-files
			    (file-name-directory auto-save-list-file-prefix)
			    nil
			    (concat "\\`"
				    (regexp-quote
				     (file-name-nondirectory
				      auto-save-list-file-prefix)))
			    t))
	      :help "Recover edits from a crashed session"))
(define-key menu-bar-files-menu [revert-buffer]
  '(menu-item "Revert Buffer" revert-buffer
	      :enable (or revert-buffer-function
			  revert-buffer-insert-file-contents-function
			  (and (buffer-file-name)
			       (or (buffer-modified-p)
				   (not (verify-visited-file-modtime
					 (current-buffer))))))
	      :help "Re-read current buffer from its file"))
(define-key menu-bar-files-menu [write-file]
  '(menu-item "Save Buffer As..." write-file
	      :enable (not (window-minibuffer-p
			    (frame-selected-window menu-updating-frame)))
	      :help "Write current buffer to another file"))
(define-key menu-bar-files-menu [save-buffer]
  '(menu-item "Save (current buffer)" save-buffer
	      :enable (and (buffer-modified-p)
			   (buffer-file-name)
			   (not (window-minibuffer-p
				 (frame-selected-window menu-updating-frame))))
	      :help "Save current buffer to its file"))

(define-key menu-bar-files-menu [separator-save]
  '(menu-item "--"))

(define-key menu-bar-files-menu [kill-buffer]
  '(menu-item "Close (current buffer)" kill-this-buffer
	      :enable (kill-this-buffer-enabled-p)
	      :help "Discard current buffer"))
(define-key menu-bar-files-menu [insert-file]
  '(menu-item "Insert File..." insert-file
	      :enable (not (window-minibuffer-p
			    (frame-selected-window menu-updating-frame)))
	      :help "Insert another file into current buffer"))
(define-key menu-bar-files-menu [dired]
  '(menu-item "Open Directory..." dired
	      :help "Read a directory, operate on its files"))
(define-key menu-bar-files-menu [open-file]
  '(menu-item "Open File..." find-file
	      :enable (not (window-minibuffer-p
			    (frame-selected-window menu-updating-frame)))
	      :help "Read a file into an Emacs buffer"))


;; The "Edit" menu items
(defun nonincremental-search-forward (string)
  "Read a string and search for it nonincrementally."
  (interactive "sSearch for string: ")
  (if (equal string "")
      (search-forward (car search-ring))
    (isearch-update-ring string nil)
    (search-forward string)))

(defun nonincremental-search-backward (string)
  "Read a string and search backward for it nonincrementally."
  (interactive "sSearch for string: ")
  (if (equal string "")
      (search-backward (car search-ring))
    (isearch-update-ring string nil)
    (search-backward string)))

(defun nonincremental-re-search-forward (string)
  "Read a regular expression and search for it nonincrementally."
  (interactive "sSearch for regexp: ")
  (if (equal string "")
      (re-search-forward (car regexp-search-ring))
    (isearch-update-ring string t)
    (re-search-forward string)))

(defun nonincremental-re-search-backward (string)
  "Read a regular expression and search backward for it nonincrementally."
  (interactive "sSearch for regexp: ")
  (if (equal string "")
      (re-search-backward (car regexp-search-ring))
    (isearch-update-ring string t)
    (re-search-backward string)))

(defun nonincremental-repeat-search-forward ()
  "Search forward for the previous search string."
  (interactive)
  (if (null search-ring)
      (error "No previous search"))
  (search-forward (car search-ring)))

(defun nonincremental-repeat-search-backward ()
  "Search backward for the previous search string."
  (interactive)
  (if (null search-ring)
      (error "No previous search"))
  (search-backward (car search-ring)))

(defun nonincremental-repeat-re-search-forward ()
  "Search forward for the previous regular expression."
  (interactive)
  (if (null regexp-search-ring)
      (error "No previous search"))
  (re-search-forward (car regexp-search-ring)))

(defun nonincremental-repeat-re-search-backward ()
  "Search backward for the previous regular expression."
  (interactive)
  (if (null regexp-search-ring)
      (error "No previous search"))
  (re-search-backward (car regexp-search-ring)))

(defvar menu-bar-search-menu (make-sparse-keymap "Search"))
(defvar menu-bar-adv-search-menu
  (make-sparse-keymap "Advanced Search/Replace"))

(define-key menu-bar-adv-search-menu [tags-continue]
  '(menu-item "Continue Tags Search/Replace" tags-loop-continue
	      :help "Continue last tags search/replace operation"))
(define-key menu-bar-adv-search-menu [tags-repl]
  '(menu-item "Replace in all tagged files" tags-query-replace
	      :help "Interactively replace a regexp in all tagged files"))
(define-key menu-bar-adv-search-menu [tags-srch]
  '(menu-item "Search in all tagged files" tags-search
	      :help "Search for a regexp in all tagged files"))

(define-key menu-bar-adv-search-menu [separator-tag-search]
  '(menu-item "--"))

(define-key menu-bar-adv-search-menu [query-replace-regexp]
  '(menu-item "Replace Regexp..." query-replace-regexp
	      :enable (not buffer-read-only)
	      :help "Replace regular expression, ask about each occurrence"))
(define-key menu-bar-adv-search-menu [repeat-regexp-back]
  '(menu-item "Repeat Regexp Backwards"
	      nonincremental-repeat-re-search-backward
	      :enable regexp-search-ring
	      :help "Repeat last regular expression search backwards"))
(define-key menu-bar-adv-search-menu [repeat-regexp-fwd]
  '(menu-item "Repeat Regexp" nonincremental-repeat-re-search-forward
	      :enable regexp-search-ring
	      :help "Repeat last regular expression search forward"))
(define-key menu-bar-adv-search-menu [re-search-backward]
  '(menu-item "Search Regexp Backwards..." nonincremental-re-search-backward
	      :help "Search backwards for a regular expression"))
(define-key menu-bar-adv-search-menu [re-search-forward]
  '(menu-item "Search Regexp..." nonincremental-re-search-forward
	      :help "Search forward for a regular expression"))
(define-key menu-bar-search-menu [re-search]
  (list 'menu-item "Advanced Search/Replace" menu-bar-adv-search-menu
	      :help "Regexp and Tags search and replace"))

(define-key menu-bar-search-menu [query-replace]
  '(menu-item "Replace..." query-replace
	      :enable (not buffer-read-only)
	      :help "Replace string interactively, ask about each occurrence"))
(define-key menu-bar-search-menu [repeat-search-back]
  '(menu-item "Repeat Backwards" nonincremental-repeat-search-backward
	      :enable search-ring
	      :help "Repeat last search backwards"))
(define-key menu-bar-search-menu [repeat-search-fwd]
  '(menu-item "Repeat Search" nonincremental-repeat-search-forward
	      :enable search-ring
	      :help "Repeat last search forward"))
(define-key menu-bar-search-menu [search-backward]
  '(menu-item "Search Backwards..." nonincremental-search-backward
	      :help "Search backwards for a string"))
(define-key menu-bar-search-menu [search-forward]
  '(menu-item "Search..." nonincremental-search-forward
	      :help "Search forward for a string"))

;;; Assemble the top-level Edit menu items.
(define-key menu-bar-edit-menu [props]
  '(menu-item "Text Properties" facemenu-menu
	      :help "Change properties of text in region"))

(define-key menu-bar-edit-menu [fill]
  '(menu-item "Fill" fill-region
	      :enable (and mark-active (not buffer-read-only))
	      :help
	      "Fill text in region to fit between left and right margin"))

(define-key menu-bar-edit-menu [separator-bookmark]
  '(menu-item "--"))

(define-key menu-bar-edit-menu [bookmark]
  '(menu-item "Bookmarks" menu-bar-bookmark-map
	      :help "Record positions and jump between them"))

(defvar menu-bar-goto-menu (make-sparse-keymap "Go To"))

(define-key menu-bar-goto-menu [set-tags-name]
  '(menu-item "Set Tags File Name" visit-tags-table
	      :help "Tell Tags commands which tag table file to use"))

(define-key menu-bar-goto-menu [separator-tag-file]
  '(menu-item "--"))

(define-key menu-bar-goto-menu [apropos-tags]
  '(menu-item "Tags Apropos" tags-apropos
	      :help "Find function/variables whose names match regexp"))
(define-key menu-bar-goto-menu [next-tag-otherw]
  '(menu-item "Next Tag in Other Window"
	      (lambda () (interactive) (find-tag-other-window nil t))
	      :enable (and (boundp 'tags-location-ring)
			   (not (ring-empty-p tags-location-ring)))
	      :help "Find next function/variable matching last tag name in another window"))
(define-key menu-bar-goto-menu [next-tag]
  '(menu-item "Find Next Tag"
	      (lambda () (interactive) (find-tag nil t))
	      :enable (and (boundp 'tags-location-ring)
			   (not (ring-empty-p tags-location-ring)))
	      :help "Find next function/variable matching last tag name"))
(define-key menu-bar-goto-menu [find-tag-otherw]
  '(menu-item "Find Tag in Other Window..." find-tag-other-window
	      :help "Find function/variable definition in another window"))
(define-key menu-bar-goto-menu [find-tag]
  '(menu-item "Find Tag..." find-tag
	      :help "Find definition of function or variable"))

(define-key menu-bar-goto-menu [separator-tags]
  '(menu-item "--"))

(define-key menu-bar-goto-menu [end-of-buf]
  '(menu-item "Goto End of Buffer" end-of-buffer))
(define-key menu-bar-goto-menu [beg-of-buf]
  '(menu-item "Goto Beginning of Buffer" beginning-of-buffer))
(define-key menu-bar-goto-menu [go-to-pos]
  '(menu-item "Goto Buffer Position..." goto-char
	      :help "Read a number N and go to buffer position N"))
(define-key menu-bar-goto-menu [go-to-line]
  '(menu-item "Goto Line..." goto-line
	      :help "Read a line number and go to that line"))

(define-key menu-bar-edit-menu [goto]
  (list 'menu-item "Go To" menu-bar-goto-menu))

(define-key menu-bar-edit-menu [search]
  (list 'menu-item "Search" menu-bar-search-menu))

(define-key menu-bar-edit-menu [separator-search]
  '(menu-item "--"))

(define-key menu-bar-edit-menu [mark-whole-buffer]
  '(menu-item "Select All" mark-whole-buffer
	      :help "Mark the whole buffer for a subsequent cut/copy."))
(define-key menu-bar-edit-menu [clear]
  '(menu-item "Clear" delete-region
	      :enable (and mark-active
			   (not buffer-read-only)
			   (not (mouse-region-match)))
	      :help
	      "Delete the text in region between mark and current position"))
(defvar yank-menu (cons "Select Yank" nil))
(fset 'yank-menu (cons 'keymap yank-menu))
(define-key menu-bar-edit-menu [select-paste]
  '(menu-item "Select and Paste" yank-menu
	      :enable (and (cdr yank-menu) (not buffer-read-only))
	      :help "Paste (yank) text cut or copied earlier"))
(define-key menu-bar-edit-menu [paste]
  '(menu-item "Paste" yank
	      :enable (and
		       ;; Emacs compiled --without-x doesn't have
		       ;; x-selection-exists-p.
		       (fboundp 'x-selection-exists-p)
		       (x-selection-exists-p) (not buffer-read-only))
	      :help "Paste (yank) text most recently cut/copied"))
(define-key menu-bar-edit-menu [copy]
  '(menu-item "Copy" menu-bar-kill-ring-save
	      :enable mark-active
	      :help "Copy text in region between mark and current position"
	      :keys "\\[kill-ring-save]"))
(define-key menu-bar-edit-menu [cut]
  '(menu-item "Cut" kill-region
	      :enable (and mark-active (not buffer-read-only))
	      :help
	      "Cut (kill) text in region between mark and current position"))
(define-key menu-bar-edit-menu [undo]
  '(menu-item "Undo" undo
	      :enable (and (not buffer-read-only)
			   (not (eq t buffer-undo-list))
			   (if (eq last-command 'undo)
			       pending-undo-list
			     (consp buffer-undo-list)))
	      :help "Undo last operation"))


(defun menu-bar-kill-ring-save (beg end)
  (interactive "r")
  (if (mouse-region-match)
      (message "Selecting a region with the mouse does `copy' automatically")
    (kill-ring-save beg end)))

(autoload 'ispell-menu-map "ispell" nil t 'keymap)

;; These are alternative definitions for the cut, paste and copy
;; menu items.  Use them if your system expects these to use the clipboard.

(put 'clipboard-kill-region 'menu-enable 'mark-active)
(put 'clipboard-kill-ring-save 'menu-enable 'mark-active)
(put 'clipboard-yank 'menu-enable
     '(or (and (fboundp 'x-selection-exists-p) (x-selection-exists-p))
	  (x-selection-exists-p 'CLIPBOARD)))

(defun clipboard-yank ()
  "Insert the clipboard contents, or the last stretch of killed text."
  (interactive)
  (let ((x-select-enable-clipboard t))
    (yank)))

(defun clipboard-kill-ring-save (beg end)
  "Copy region to kill ring, and save in the X clipboard."
  (interactive "r")
  (let ((x-select-enable-clipboard t))
    (kill-ring-save beg end)))

(defun clipboard-kill-region (beg end)
  "Kill the region, and save it in the X clipboard."
  (interactive "r")
  (let ((x-select-enable-clipboard t))
    (kill-region beg end)))

(defun menu-bar-enable-clipboard ()
  "Make CUT, PASTE and COPY (keys and menu bar items) use the clipboard.
Do the same for the keys of the same name."
  (interactive)
  ;; We can't use constant list structure here because it becomes pure,
  ;; and because it gets modified with cache data.
  (define-key menu-bar-edit-menu [paste]
    (cons "Paste" (cons "Paste text from clipboard" 'clipboard-yank)))
  (define-key menu-bar-edit-menu [copy]
    (cons "Copy" (cons "Copy text in region to the clipboard"
		       'clipboard-kill-ring-save)))
  (define-key menu-bar-edit-menu [cut]
    (cons "Cut" (cons "Delete text in region and copy it to the clipboard"
		      'clipboard-kill-region)))

  (define-key global-map [f20] 'clipboard-kill-region)
  (define-key global-map [f16] 'clipboard-kill-ring-save)
  (define-key global-map [f18] 'clipboard-yank)
  ;; X11R6 versions
  (define-key global-map [cut] 'clipboard-kill-region)
  (define-key global-map [copy] 'clipboard-kill-ring-save)
  (define-key global-map [paste] 'clipboard-yank))

;; The "Options" menu items

(defvar menu-bar-custom-menu (make-sparse-keymap "Customize"))

(define-key menu-bar-custom-menu [customize-apropos-groups]
  '(menu-item "Groups Matching Regexp..." customize-apropos-groups
	      :help "Browse groups whose names match regexp"))
(define-key menu-bar-custom-menu [customize-apropos-faces]
  '(menu-item "Faces Matching Regexp..." customize-apropos-faces
	      :help "Browse faces whose names match regexp"))
(define-key menu-bar-custom-menu [customize-apropos-options]
  '(menu-item "Options Matching Regexp..." customize-apropos-options
	      :help "Browse options whose names match regexp"))
(define-key menu-bar-custom-menu [customize-apropos]
  '(menu-item "Settings Matching Regexp..." customize-apropos
	      :help "Browse customizable settings whose names match regexp"))
(define-key menu-bar-custom-menu [separator-2]
  '("--"))
(define-key menu-bar-custom-menu [customize-group]
  '(menu-item "Specific Group..." customize-group
	      :help "Customize settings of specific group"))
(define-key menu-bar-custom-menu [customize-face]
  '(menu-item "Specific Face..." customize-face
	      :help "Customize attributes of specific face"))
(define-key menu-bar-custom-menu [customize-option]
  '(menu-item "Specific Option..." customize-option
	      :help "Change value of specific option"))
(define-key menu-bar-custom-menu [customize-changed-options]
  '(menu-item "Recently Changed Options..." customize-changed-options
	      :help "Customize options changed in recent versions"))
(define-key menu-bar-custom-menu [separator-3]
  '("--"))
(define-key menu-bar-custom-menu [customize-browse]
  '(menu-item "Browse Customization Groups" customize-browse
	      :help "Browse all customization groups"))
(define-key menu-bar-custom-menu [customize]
  '(menu-item "Top-level Customization Group" customize
	      :help "The master group called `Emacs'"))

;(defvar menu-bar-preferences-menu (make-sparse-keymap "Preferences"))

(defmacro menu-bar-make-toggle (name variable doc message help &rest body)
  `(progn
     (defun ,name ()
       ,(concat "Toggle whether to " (downcase (substring help 0 1))
		(substring help 1) ".")
       (interactive)
       (if ,(if body `(progn . ,body)
	      `(setq ,variable (not ,variable)))
  	   (message ,message "enabled")
  	 (message ,message "disabled")))
     '(menu-item ,doc ,name
		 :help ,help
                 :button (:toggle . (and (boundp ',variable) ,variable)))))

;;; Assemble all the top-level items of the "Options" menu
(define-key menu-bar-options-menu [customize]
  (list 'menu-item "Customize Emacs" menu-bar-custom-menu
	:help "Full customization of every Emacs feature"))

(defun menu-bar-options-save ()
  "Save current values of Options menu items using Custom."
  (interactive)
  (dolist (elt '(debug-on-quit debug-on-error auto-compression-mode
		 case-fold-search truncate-lines show-paren-mode
		 transient-mark-mode global-font-lock-mode
		 current-language-environment default-input-method))
    (if (default-value elt)
	(customize-save-variable elt (default-value elt))))
  (if (memq 'turn-on-auto-fill text-mode-hook)
      (customize-save-variable 'text-mode-hook
			       (default-value 'text-mode-hook)))
  (if (featurep 'saveplace)
      (customize-save-variable 'save-place (default-value 'save-place)))
  (if (featurep 'uniquify)
      (customize-save-variable 'uniquify-buffer-name-style
			       (default-value 'uniquify-buffer-name-style))))

(define-key menu-bar-options-menu [save]
  '(menu-item "Save Options" menu-bar-options-save
	      :help "Save options set from the menu above"))

(define-key menu-bar-options-menu [custom-separator]
  '("--"))

(define-key menu-bar-options-menu [mule]
  ;; It is better not to use backquote here,
  ;; because that makes a bootstrapping problem
  ;; if you need to recompile all the Lisp files using interpreted code.
  (list 'menu-item "Mule (Multilingual Environment)" mule-menu-keymap
;; Most of the MULE menu actually does make sense in unibyte mode,
;; e.g. language selection.
;;;	':visible 'default-enable-multibyte-characters
	':help "Default language, encodings, input method"))
;(setq menu-bar-final-items (cons 'mule menu-bar-final-items))
;(define-key menu-bar-options-menu [preferences]
;  (list 'menu-item "Preferences" menu-bar-preferences-menu
;	:help "Toggle important global options"))

(define-key menu-bar-options-menu [mule-separator]
  '("--"))

(define-key menu-bar-options-menu [debug-on-quit]
  (menu-bar-make-toggle toggle-debug-on-quit debug-on-quit
			"Enter Debugger on Quit/C-g" "Debug on Quit %s"
			"Enter Lisp debugger when C-g is pressed"))
(define-key menu-bar-options-menu [debug-on-error]
  (menu-bar-make-toggle toggle-debug-on-error debug-on-error
			"Enter Debugger on Error" "Debug on Error %s"
			"Enter Lisp debugger when an error is signaled"))
(define-key menu-bar-options-menu [debugger-separator]
  '("--"))
(define-key menu-bar-options-menu [toggle-auto-compression]
  '(menu-item "Automatic File De/compression"
             auto-compression-mode
	     :help "Transparently decompress compressed files"
             :button (:toggle . (rassq 'jka-compr-handler
				       file-name-handler-alist))))
(define-key menu-bar-options-menu [save-place]
  (menu-bar-make-toggle toggle-save-place-globally save-place
			"Save Place in Files between Sessions"
			"Saving place in files %s"
			"Save Emacs state for next session"
                        (require 'saveplace)
			(setq-default save-place
				      (not (default-value save-place)))))
(define-key menu-bar-options-menu [uniquify]
  (menu-bar-make-toggle toggle-uniquify-buffer-names uniquify-buffer-name-style
			"Use Directory Names in Buffer Names"
			"Directory name in buffer names (uniquify) %s"
			"Uniquify buffer names by adding parent directory names"
			(require 'uniquify)
			(setq uniquify-buffer-name-style
			      (if (not uniquify-buffer-name-style)
				  'forward))))
(define-key menu-bar-options-menu [edit-options-separator]
  '("--"))
(define-key menu-bar-options-menu [case-fold-search]
  (menu-bar-make-toggle toggle-case-fold-search case-fold-search
			"Case-Insensitive Search"
			"Case-Insensitive Search %s"
			"Ignore letter-case in search"))
(define-key menu-bar-options-menu [auto-fill-mode]
  '(menu-item "Word Wrap in Text Modes (Auto Fill)"
              toggle-text-mode-auto-fill
	      :help "Automatically fill text between left and right margins"
              :button (:toggle . (member 'turn-on-auto-fill text-mode-hook))))
(define-key menu-bar-options-menu [truncate-lines]
  (menu-bar-make-toggle
   toggle-truncate-lines truncate-lines
   "Truncate Long Lines in this Buffer" "Long Line Truncation %s"
   "Truncate long lines on the screen"
   (prog1 (setq truncate-lines (not truncate-lines))
     (set-buffer-modified-p (buffer-modified-p)))))
(define-key menu-bar-options-menu [highlight-separator]
  '("--"))
(define-key menu-bar-options-menu [highlight-paren-mode]
  (menu-bar-make-toggle toggle-highlight-paren-mode show-paren-mode
			"Paren Match Highlighting (Show Paren mode)"
			"Show Paren mode %s"
			"Highlight matching/mismatched parentheses at cursor"
			(show-paren-mode)))
(define-key menu-bar-options-menu [transient-mark-mode]
  (menu-bar-make-toggle toggle-transient-mark-mode transient-mark-mode
			"Active Region Highlighting (Transient Mark mode)"
			"Transient Mark mode %s"
			"Make text in active region stand out in color"))
(define-key menu-bar-options-menu [toggle-global-lazy-font-lock-mode]
  (menu-bar-make-toggle toggle-global-lazy-font-lock-mode global-font-lock-mode
			"Syntax Highlighting (Global Font Lock mode)"
			"Global Font Lock mode %s"
			"Colorize text based on language syntax"
			(global-font-lock-mode)))


;; The "Tools" menu items

(defun send-mail-item-name ()
  (let* ((known-send-mail-commands '((sendmail-user-agent . "sendmail")
				     (mh-e-user-agent . "MH")
				     (message-user-agent . "Gnus Message")
				     (gnus-user-agent . "Gnus")))
	 (name (assq mail-user-agent known-send-mail-commands)))
    (if name
	(setq name (cdr name))
      (setq name (symbol-name mail-user-agent))
      (if (string-match "\\(.+\\)-user-agent" name)
	  (setq name (match-string 1 name))))
    name))

(defun read-mail-item-name ()
  (let* ((known-rmail-commands '((rmail . "RMAIL")
				 (mh-rmail . "MH")
				 (gnus . "Gnus")))
	 (known (assq read-mail-command known-rmail-commands)))
    (if known (cdr known) (symbol-name read-mail-command))))

(defvar menu-bar-games-menu (make-sparse-keymap "Games"))

(define-key menu-bar-tools-menu [games]
  (list 'menu-item "Games" menu-bar-games-menu))

(define-key menu-bar-tools-menu [separator-games]
  '("--"))

(define-key menu-bar-games-menu [zone]
  '(menu-item "Zone Out"  zone
	      :help "Play tricks with Emacs display when Emacs is idle"))
(define-key menu-bar-games-menu [yow]
  '(menu-item "Random Quotation"  yow
	      :help "Display a random Zippy quotation"))
(define-key menu-bar-games-menu [tetris]
  '(menu-item "Tetris"  tetris))
(define-key menu-bar-games-menu [solitaire]
  '(menu-item "Solitaire"  solitaire))
(define-key menu-bar-games-menu [snake]
  '(menu-item "Snake"  snake
	      :help "Move snake around avoiding collisions"))
(define-key menu-bar-games-menu [mult]
  '(menu-item "Multiplication Puzzle"  mpuz
	      :help "Excercise brain with multiplication"))
(define-key menu-bar-games-menu [life]
  '(menu-item "Life"  life
	      :help "Watch how John Conway's cellular automaton evolves"))
(define-key menu-bar-games-menu [hanoi]
  '(menu-item "Towers of Hanoi" hanoi
	      :help "Watch Towers-of-Hanoi puzzle solved by Emacs"))
(define-key menu-bar-games-menu [gomoku]
  '(menu-item "Gomoku"  gomoku
	      :help "Mark 5 contiguous squares (like tic-tac-toe)"))
(define-key menu-bar-games-menu [black-box]
  '(menu-item "Blackbox"  blackbox
	      :help "Find balls in a black box by shooting rays"))
(define-key menu-bar-games-menu [adventure]
  '(menu-item "Adventure"  dunnet
	      :help "Dunnet, a text Adventure game for Emacs"))
(define-key menu-bar-games-menu [5x5]
  '(menu-item "5x5" 5x5
	      :help "Fill in all the squares on a 5x5 board"))

(define-key menu-bar-tools-menu [calendar]
  '(menu-item "Display Calendar" calendar))
(define-key menu-bar-tools-menu [speedbar]
  '(menu-item "Display Speedbar" speedbar-frame-mode))
(define-key menu-bar-tools-menu [directory-search]
  '(menu-item "Directory Search" eudc-tools-menu
	      :help "Query directory servers via LDAP, CCSO PH/QI or BBDB"))
(define-key menu-bar-tools-menu [compose-mail]
  (list
   'menu-item `(format "Send Mail (with %s)" (send-mail-item-name))
   'compose-mail
   :visible `(and mail-user-agent (not (eq mail-user-agent 'ignore)))
   :help "Send a mail message"))
(define-key menu-bar-tools-menu [rmail]
  (list
   'menu-item `(format "Read Mail (with %s)" (read-mail-item-name))
   (lambda ()
     (interactive)
     (call-interactively read-mail-command))
   :visible `(and read-mail-command (not (eq read-mail-command 'ignore)))
   :help "Read your mail and reply to it"))
(define-key menu-bar-tools-menu [gnus]
  '(menu-item "Read Net News (Gnus)" gnus
	      :help "Read network news groups"))

(define-key menu-bar-tools-menu [separator-vc]
  '("--"))

(defvar vc-menu-map (make-sparse-keymap "Version Control"))
(define-key menu-bar-tools-menu [pcl-cvs]
  `(menu-item "PCL-CVS" ,cvs-global-menu
	      :help "Module-level interface to CVS"))
(define-key menu-bar-tools-menu [vc]
  (list 'menu-item "Version Control" vc-menu-map
	:help "Interface to RCS, CVS, SCCS"))

(define-key menu-bar-tools-menu [separator-compare]
  '("--"))

(define-key menu-bar-tools-menu [ediff-misc]
  '(menu-item "Ediff Miscellanea" menu-bar-ediff-misc-menu
	      :help "Ediff manual, customization, sessions, etc."))
(define-key menu-bar-tools-menu [epatch]
  '(menu-item "Apply Patch" menu-bar-epatch-menu))
(define-key menu-bar-tools-menu [ediff-merge]
  '(menu-item "Merge" menu-bar-ediff-merge-menu
	      :help "Merge different revisions of files/directories"))
(define-key menu-bar-tools-menu [compare]
  '(menu-item "Compare (Ediff)" menu-bar-ediff-menu
	      :help "Display differences between files/directories"))


(define-key menu-bar-tools-menu [separator-spell]
  '("--"))

(define-key menu-bar-tools-menu [spell]
  '(menu-item "Spell Checking" ispell-menu-map))

(define-key menu-bar-tools-menu [separator-prog]
  '("--"))

(define-key menu-bar-tools-menu [gdb]
  '(menu-item "Debugger (GUD)..." gdb
	      :help "Debug a program from within Emacs"))
(define-key menu-bar-tools-menu [shell-on-region]
  '(menu-item "Shell Command on Region..." shell-command-on-region
	      :enable mark-active
	      :help "Pass marked region to a shell command"))
(define-key menu-bar-tools-menu [shell]
  '(menu-item "Shell Command..." shell-command
	      :help "Invoke a shell command and catch its output"))
(define-key menu-bar-tools-menu [compile]
  '(menu-item "Compile..." compile
	      :help "Invoke compiler or Make, view compilation errors"))
(define-key menu-bar-tools-menu [grep]
  '(menu-item "Search Files (Grep)..." grep
	      :help "Search files for strings or regexps (with Grep)"))


;; The "Help" menu items

(defvar menu-bar-describe-menu (make-sparse-keymap "Describe"))

(define-key menu-bar-describe-menu [mule-diag]
  '(menu-item "Show All of Mule Status" mule-diag
	      :visible default-enable-multibyte-characters
	      :help "Display multilingual environment settings"))
(define-key menu-bar-describe-menu [describe-coding-system]
  '(menu-item "Describe Coding System..." describe-coding-system
	      :visible default-enable-multibyte-characters))
(define-key menu-bar-describe-menu [describe-input-method]
  '(menu-item "Describe Input Method..." describe-input-method
	      :visible default-enable-multibyte-characters
	      :help "Keyboard layout for specific input method"))
(define-key menu-bar-describe-menu [describe-language-environment]
  (list 'menu-item "Describe Language Environment"
	describe-language-environment-map
	:help "Show multilingual settings for a specific language"))

(define-key menu-bar-describe-menu [separator-desc-mule]
  '("--"))

(define-key menu-bar-describe-menu [list-keybindings]
  '(menu-item "List Key Bindings" describe-bindings
	      :help "Display a list of all current keybindings"))
(define-key menu-bar-describe-menu [list-keybindings]
  '(menu-item "List Key Bindings" describe-bindings
	      :help "Display a list of all current keybindings"))
(define-key menu-bar-describe-menu [describe-variable]
  '(menu-item "Describe Variable..." describe-variable
	      :help "Display documentation of variable/option"))
(define-key menu-bar-describe-menu [describe-function]
  '(menu-item "Describe Function..." describe-function
	      :help "Display documentation of function/command"))
(define-key menu-bar-describe-menu [describe-key]
  '(menu-item "Describe Key..." describe-key
	      ;; Users typically don't identify keys and menu items...
	      :help "Display documentation of command bound to a \
key (or menu-item)"))
(define-key menu-bar-describe-menu [apropos-variables]
  '(menu-item "Apropos Variables..." apropos-variable
	      :help "List variables whose names match a regexp"))
(define-key menu-bar-describe-menu [apropos-commands]
  '(menu-item "Apropos Commands..." apropos-command
	      :help "List commands whose names match a regexp"))
(define-key menu-bar-describe-menu [describe-mode]
  '(menu-item "Describe Buffer Modes" describe-mode
	      :help "Describe this buffer's major and minor mode"))

(defvar menu-bar-manuals-menu (make-sparse-keymap "Manuals"))

(define-key menu-bar-manuals-menu [man]
  '(menu-item "Read Man Page..." manual-entry
	      :help "Man-page docs for external commands and libraries"))
(define-key menu-bar-manuals-menu [sep2]
  '("--"))
(define-key menu-bar-manuals-menu [info]
  '(menu-item "Browse Manuals with Info" Info-directory
	      :help "Read any of the installed manuals"))
(define-key menu-bar-manuals-menu [command]
  '(menu-item "Find Command in Manual" Info-goto-emacs-command-node
	      :help "Display manual section that describes a command"))
(define-key menu-bar-manuals-menu [key]
  '(menu-item "Find Key in Manual" Info-goto-emacs-key-command-node
	      :help "Display manual section that describes a key"))

(define-key menu-bar-help-menu [eliza]
  '(menu-item "Emacs Psychiatrist" doctor
	      :help "Our doctor will help you feel better"))
(define-key menu-bar-help-menu [sep3]
  '("--"))
(define-key menu-bar-help-menu [describe-no-warranty]
  '(menu-item "(Non)Warranty" describe-no-warranty
	      :help "Explain that Emacs has NO WARRANTY"))
(define-key menu-bar-help-menu [describe-copying]
  '(menu-item "Copying Conditions" describe-copying
	      :help "Show the Emacs license (GPL)"))
(define-key menu-bar-help-menu [describe-distribution]
  '(menu-item "Getting New Versions" describe-distribution
	      :help "How to get latest versions of Emacs"))
(define-key menu-bar-help-menu [more]
  '(menu-item "Find Extra Packages"
	      (lambda ()
		(interactive)
		(let (enable-local-variables)
		  (view-file (expand-file-name "MORE.STUFF"
					       data-directory))
		  (goto-address)))
	      :help "Where to find some extra packages and possible updates"))
(define-key menu-bar-help-menu [emacs-version]
  '(menu-item "Show Emacs Version" emacs-version))
(define-key menu-bar-help-menu [sep2]
  '("--"))
(define-key menu-bar-help-menu [finder-by-keyword]
  '(menu-item "Find Emacs Packages..." finder-by-keyword
	      :help "Find packages and features by keyword"))
(define-key menu-bar-help-menu [describe]
  (list 'menu-item "Describe" menu-bar-describe-menu
	:help "Describe commands, variables, keys"))
(define-key menu-bar-help-menu [manuals]
  (list 'menu-item "Manuals" menu-bar-manuals-menu
	:help "Lookup commands and keys in docs, read manuals"))
(define-key menu-bar-help-menu [sep1]
  '("--"))
(define-key menu-bar-help-menu [report-emacs-bug]
  '(menu-item "Send Bug Report..." report-emacs-bug
	      :help "Send e-mail to Emacs maintainers"))
(define-key menu-bar-help-menu [order-emacs-manuals]
  '(menu-item "Ordering Manuals" view-order-manuals
	      :help "How to order manuals from the Free Software Foundation"))
(define-key menu-bar-help-menu [emacs-manual]
  '(menu-item "Read the Emacs Manual"
	      (lambda () (interactive) (info "emacs"))))
(define-key menu-bar-help-menu [emacs-problems]
  '(menu-item "Emacs Known Problems" view-emacs-problems))
(define-key menu-bar-help-menu [emacs-news]
  '(menu-item "Emacs News" view-emacs-news
	      :help "New features of this version"))
(define-key menu-bar-help-menu [emacs-faq]
  '(menu-item "Emacs FAQ" view-emacs-FAQ))
(define-key menu-bar-help-menu [emacs-tutorial-language-specific]
  '(menu-item "Emacs Tutorial (choose language)..."
	      (lambda () (interactive) (help-with-tutorial t))
	      :help "Learn how to use Emacs (choose a language)"))
(define-key menu-bar-help-menu [emacs-tutorial]
  '(menu-item "Emacs Tutorial" help-with-tutorial
	      :help "Learn how to use Emacs"))

(defun kill-this-buffer ()	; for the menubar
  "Kill the current buffer."
  (interactive)
  (kill-buffer (current-buffer)))

(defun kill-this-buffer-enabled-p ()
  (let ((count 0)
	(buffers (buffer-list)))
    (while buffers
      (or (string-match "^ " (buffer-name (car buffers)))
	  (setq count (1+ count)))
      (setq buffers (cdr buffers)))
    (and (not (window-minibuffer-p (frame-selected-window menu-updating-frame)))
	 (> count 1))))

(put 'dired 'menu-enable
     '(not (window-minibuffer-p (frame-selected-window menu-updating-frame))))

;; Permit deleting frame if it would leave a visible or iconified frame.
(defun delete-frame-enabled-p ()
  "Return non-nil if `delete-frame' should be enabled in the menu bar."
  (let ((frames (frame-list))
	(count 0))
    (while frames
      (if (frame-visible-p (car frames))
	  (setq count (1+ count)))
      (setq frames (cdr frames)))
    (> count 1)))

(defcustom yank-menu-length 20
  "*Maximum length to display in the yank-menu."
  :type 'integer
  :group 'mouse)

(defun menu-bar-update-yank-menu (string old)
  (let ((front (car (cdr yank-menu)))
	(menu-string (if (<= (length string) yank-menu-length)
			 string
		       (concat
			(substring string 0 (/ yank-menu-length 2))
			"..."
			(substring string (- (/ yank-menu-length 2)))))))
    ;; Don't let the menu string be all dashes
    ;; because that has a special meaning in a menu.
    (if (string-match "\\`-+\\'" menu-string)
	(setq menu-string (concat menu-string " ")))
    ;; If we're supposed to be extending an existing string, and that
    ;; string really is at the front of the menu, then update it in place.
    (if (and old (or (eq old (car front))
		     (string= old (car front))))
	(progn
	  (setcar front string)
	  (setcar (cdr front) menu-string))
      (setcdr yank-menu
	      (cons
	       (cons string (cons menu-string 'menu-bar-select-yank))
	       (cdr yank-menu)))))
  (if (> (length (cdr yank-menu)) kill-ring-max)
      (setcdr (nthcdr kill-ring-max yank-menu) nil)))

(put 'menu-bar-select-yank 'apropos-inhibit t)
(defun menu-bar-select-yank ()
  (interactive "*")
  (push-mark (point))
  (insert last-command-event))

(defvar list-buffers-directory nil)

(defvar menu-bar-update-buffers-maxbuf)

(defun menu-bar-select-buffer ()
  (interactive)
  (switch-to-buffer last-command-event))

(defun menu-bar-select-frame ()
  (interactive)
  (let (frame)
    (dolist (f (frame-list))
      (when (equal last-command-event (frame-parameter f 'name))
	(setq frame f)))
  (make-frame-visible frame)
  (raise-frame frame)
  (select-frame frame)))

(defun menu-bar-update-buffers-1 (elt)
  (cons (format
	 (format "%%%ds  %%s%%s  %%s" menu-bar-update-buffers-maxbuf)
	 (cdr elt)
	 (if (buffer-modified-p (car elt))
	     "*" " ")
	 (save-excursion
	   (set-buffer (car elt))
	   (if buffer-read-only "%" " "))
	 (let ((file
		(or (buffer-file-name (car elt))
		    (save-excursion
		      (set-buffer (car elt))
		      list-buffers-directory)
		    "")))
	   (setq file (or (file-name-directory file)
			  ""))
	   (if (> (length file) 20)
	       (setq file (concat "..." (substring file -17))))
	   file))
	(car elt)))

(defvar menu-bar-buffers-menu-list-buffers-entry nil)

(defun menu-bar-update-buffers (&optional force)
  ;; If user discards the Buffers item, play along.
  (and (lookup-key (current-global-map) [menu-bar buffer])
       (or force (frame-or-buffer-changed-p))
       (let ((buffers (buffer-list))
	     (frames (frame-list))
	     (maxlen 0)
	     buffers-menu frames-menu)
	 ;; If requested, list only the N most recently selected buffers.
	 (if (and (integerp buffers-menu-max-size)
		  (> buffers-menu-max-size 1))
	     (if (> (length buffers) buffers-menu-max-size)
		 (setcdr (nthcdr buffers-menu-max-size buffers) nil)))

	 ;; Make the menu of buffers proper.
	 (setq buffers-menu
	       (cons "Select Buffer"
		     (let* ((buffer-list
			     (mapcar 'list buffers))
			    tail
			    (menu-bar-update-buffers-maxbuf 0)
			    alist
			    head)
		       ;; Put into each element of buffer-list
		       ;; the name for actual display,
		       ;; perhaps truncated in the middle.
		       (setq tail buffer-list)
		       (while tail
			 (let ((name (buffer-name (car (car tail)))))
			   (setcdr (car tail)
				   (if (> (length name) 27)
				       (concat (substring name 0 12)
					       "..."
					       (substring name -12))
				     name)))
			 (setq tail (cdr tail)))
		       ;; Compute the maximum length of any name.
		       (setq tail buffer-list)
		       (while tail
			 (or (eq ?\ (aref (cdr (car tail)) 0))
			     (setq menu-bar-update-buffers-maxbuf
				   (max menu-bar-update-buffers-maxbuf
					(length (cdr (car tail))))))
			 (setq tail (cdr tail)))
		       ;; Set ALIST to an alist of the form
		       ;; ITEM-STRING . BUFFER
		       (setq tail buffer-list)
		       (while tail
			 (let ((elt (car tail)))
			   (or (eq ?\ (aref (cdr elt) 0))
			       (setq alist (cons
					    (menu-bar-update-buffers-1 elt)
					    alist)))
			   (and alist (> (length (car (car alist))) maxlen)
				(setq maxlen (length (car (car alist))))))
			 (setq tail (cdr tail)))
		       (setq alist (nreverse alist))
		       ;; Make the menu item for list-buffers
		       ;; or reuse the one we already have.
		       ;; The advantage in reusing one
		       ;; is that it already has the keyboard equivalent
		       ;; cached, so we save the time to look that up again.
		       (or menu-bar-buffers-menu-list-buffers-entry
			   (setq menu-bar-buffers-menu-list-buffers-entry
				 (cons
				  'list-buffers
				  (cons
				   ""
				   'list-buffers))))
		       ;; Update the item string for menu's new width.
		       (setcar (cdr menu-bar-buffers-menu-list-buffers-entry)
			       (concat (make-string (max (- (/ maxlen 2) 8) 0)
						    ?\ )
				       "List All Buffers"))
		       ;; Now make the actual list of items,
		       ;; ending with the list-buffers item.
		       (nconc (mapcar (lambda (pair)
					;; This is somewhat risque, to use
					;; the buffer name itself as the event
					;; type to define, but it works.
					;; It would not work to use the buffer
					;; since a buffer as an event has its
					;; own meaning.
					(nconc (list (buffer-name (cdr pair))
						     (car pair)
						     (cons nil nil))
					       'menu-bar-select-buffer))
				      alist)
			      (list menu-bar-buffers-menu-list-buffers-entry)))))


	 ;; Make a Frames menu if we have more than one frame.
	 (if (cdr frames)
	     (let ((name (concat (make-string (max (- (/ maxlen 2) 3) 0)
					      ?\ )
				 "Frames"))
		   (frames-menu
		    (cons 'keymap
			  (cons "Select Frame"
				(mapcar
				 (lambda (frame)
				   (nconc
				    (list (frame-parameter frame 'name)
					  (frame-parameter frame 'name)
					  (cons nil nil))
					  'menu-bar-select-frame))
					frames)))))
	       ;; Put it underneath the Buffers menu.
	       (setq buffers-menu (cons (cons 'frames (cons name frames-menu))
					buffers-menu))))
	 (if buffers-menu
	     (setq buffers-menu (cons 'keymap buffers-menu)))
	 (define-key (current-global-map) [menu-bar buffer]
	   (cons "Buffers" buffers-menu)))))

(add-hook 'menu-bar-update-hook 'menu-bar-update-buffers)

(menu-bar-update-buffers)

;; this version is too slow
;;;(defun format-buffers-menu-line (buffer)
;;;  "Returns a string to represent the given buffer in the Buffer menu.
;;;nil means the buffer shouldn't be listed.  You can redefine this."
;;;  (if (string-match "\\` " (buffer-name buffer))
;;;      nil
;;;    (save-excursion
;;;     (set-buffer buffer)
;;;     (let ((size (buffer-size)))
;;;       (format "%s%s %-19s %6s %-15s %s"
;;;	       (if (buffer-modified-p) "*" " ")
;;;	       (if buffer-read-only "%" " ")
;;;	       (buffer-name)
;;;	       size
;;;	       mode-name
;;;	       (or (buffer-file-name) ""))))))

;;; Set up a menu bar menu for the minibuffer.

(dolist (map (list minibuffer-local-ns-map
		   minibuffer-local-must-match-map
		   minibuffer-local-isearch-map
		   minibuffer-local-map
		   minibuffer-local-completion-map))
  (define-key map [menu-bar minibuf]
    (cons "Minibuf" (make-sparse-keymap "Minibuf"))))

(dolist (map (list minibuffer-local-must-match-map
		   minibuffer-local-completion-map))
  (define-key map [menu-bar minibuf ?\?]
    (list 'menu-item "List Completions" 'minibuffer-completion-help
	  :help "Display all possible completions"))
  (define-key map [menu-bar minibuf space]
    (list 'menu-item "Complete Word" 'minibuffer-complete-word
	  :help "Complete at most one word"))
  (define-key map [menu-bar minibuf tab]
    (list 'menu-item "Complete" 'minibuffer-complete
	  :help "Complete as far as possible")))

(dolist (map (list minibuffer-local-ns-map
		   minibuffer-local-must-match-map
		   minibuffer-local-isearch-map
		   minibuffer-local-map
		   minibuffer-local-completion-map))
  (define-key map [menu-bar minibuf quit]
    (list 'menu-item "Quit" 'keyboard-escape-quit
	  :help "Abort input and exit minibuffer"))
  (define-key map [menu-bar minibuf return]
    (list 'menu-item "Enter" 'exit-minibuffer
	  :help "Terminate input and exit minibuffer")))

(defcustom menu-bar-mode nil
  "Toggle display of a menu bar on each frame.
Setting this variable directly does not take effect;
use either \\[customize] or the function `menu-bar-mode'."
  :set (lambda (symbol value)
	 (menu-bar-mode (or value 0)))
  :initialize 'custom-initialize-default
  :type 'boolean
  :group 'frames)

(defun menu-bar-mode (flag)
  "Toggle display of a menu bar on each frame.
This command applies to all frames that exist and frames to be
created in the future.
With a numeric argument, if the argument is positive,
turn on menu bars; otherwise, turn off menu bars."
 (interactive "P")

  ;; Make menu-bar-mode and default-frame-alist consistent.
  (let ((default (assq 'menu-bar-lines default-frame-alist)))
    (if default
	(setq menu-bar-mode (not (eq (cdr default) 0)))
      (setq default-frame-alist
	    (cons (cons 'menu-bar-lines (if menu-bar-mode 1 0))
		  default-frame-alist))))

  ;; Toggle or set the mode, according to FLAG.
 (setq menu-bar-mode (if (null flag) (not menu-bar-mode)
		       (> (prefix-numeric-value flag) 0)))

 ;; Apply it to default-frame-alist.
 (let ((parameter (assq 'menu-bar-lines default-frame-alist)))
   (if (consp parameter)
       (setcdr parameter (if menu-bar-mode 1 0))
     (setq default-frame-alist
	   (cons (cons 'menu-bar-lines (if menu-bar-mode 1 0))
		 default-frame-alist))))

 ;; Apply it to existing frames.
 (let ((frames (frame-list)))
   (while frames
     (let ((height (cdr (assq 'height (frame-parameters (car frames))))))
       (modify-frame-parameters (car frames)
				(list (cons 'menu-bar-lines
					  (if menu-bar-mode 1 0))))
       (modify-frame-parameters (car frames)
				(list (cons 'height height))))
     (setq frames (cdr frames)))))

(provide 'menu-bar)

;;; menu-bar.el ends here
