;;; hi-lock.el --- minor mode for interactive automatic highlighting

;; Copyright (C) 2000, 2001 Free Software Foundation, Inc.

;; Author: David M. Koppelman, koppel@ee.lsu.edu
;; Keywords: faces, minor-mode, matching, display

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
;; 
;;  With the hi-lock commands text matching interactively entered
;;  regexp's can be highlighted.  For example, `M-x highlight-regexp
;;  RET clearly RET RET' will highlight all occurrences of `clearly'
;;  using a yellow background face.  New occurrences of `clearly' will
;;  be highlighted as they are typed.  `M-x unhighlight-regexp RET'
;;  will remove the highlighting.  Any existing face can be used for
;;  highlighting and a set of appropriate faces is provided.  The
;;  regexps can be written into the current buffer in a form that will
;;  be recognized the next time the corresponding file is read.
;;
;;  Applications:
;;
;;    In program source code highlight a variable to quickly see all
;;    places it is modified or referenced:
;;    M-x highlight-regexp ground_contact_switches_closed RET RET
;;
;;    In a shell or other buffer that is showing lots of program
;;    output, highlight the parts of the output you're interested in:
;;    M-x highlight-regexp Total execution time [0-9]+ RET hi-blue-b RET
;;
;;    In buffers displaying tables, highlight the lines you're interested in:
;;    M-x highlight-lines-matching-regexp January 2000 RET hi-black-b RET
;;
;;    When writing text, highlight personal cliches.  This can be
;;    amusing.
;;    M-x highlight-phrase as can be seen RET RET
;;
;;  Setup:
;;
;;    Put the following code in your .emacs file.  This turns on
;;    hi-lock mode and adds a "Regexp Highlighting" entry
;;    to the edit menu.
;;
;;    (hi-lock-mode 1)
;;  
;;    You might also want to bind the hi-lock commands to more
;;    finger-friendly sequences:

;;    (define-key hi-lock-map "\C-z\C-h" 'highlight-lines-matching-regexp)
;;    (define-key hi-lock-map "\C-zi" 'hi-lock-find-patterns)
;;    (define-key hi-lock-map "\C-zh" 'highlight-regexp)
;;    (define-key hi-lock-map "\C-zp" 'highlight-phrase)
;;    (define-key hi-lock-map "\C-zr" 'unhighlight-regexp)
;;    (define-key hi-lock-map "\C-zb" 'hi-lock-write-interactive-patterns))

;;    See the documentation for hi-lock-mode `C-h f hi-lock-mode' for
;;    additional instructions.

;; Sample file patterns:

; Hi-lock: (("^;;; .*" (0 (quote hi-black-hb) t)))
; Hi-lock: ( ("make-variable-buffer-\\(local\\)" (0 font-lock-keyword-face)(1 'italic append)))))
; Hi-lock: end

;;; Code:

(eval-and-compile
  (require 'font-lock))

;;;###autoload
(defgroup hi-lock-interactive-text-highlighting nil
  "Interactively add and remove font-lock patterns for highlighting text."
  :group 'faces)

;;;###autoload
(defcustom hi-lock-mode nil
  "Toggle hi-lock, for interactively adding font-lock text-highlighting patterns."
  :set (lambda (symbol value)
         (hi-lock-mode (or value 0)))
  :initialize 'custom-initialize-default
  :type 'boolean
  :group 'hi-lock-interactive-text-highlighting
  :require 'hi-lock)

(defcustom hi-lock-file-patterns-range 10000
  "Limit of search in a buffer for hi-lock patterns.
When a file is visited and hi-lock mode is on patterns starting
up to this limit are added to font-lock's patterns.  See documentation
of functions `hi-lock-mode' and `hi-lock-find-patterns'."
  :type 'integer
  :group 'hi-lock-interactive-text-highlighting)

(defcustom hi-lock-exclude-modes
  '(rmail-mode mime/viewer-mode gnus-article-mode)
  "List of major modes in which hi-lock will not run.
For security reasons since font lock patterns can specify function
calls."
  :type '(repeat symbol)
  :group 'hi-lock-interactive-text-highlighting)


(defgroup hi-lock-faces nil
  "Faces for hi-lock."
  :group 'hi-lock-interactive-text-highlighting)

(defface hi-yellow
  '((((background dark)) (:background "yellow" :foreground "black"))
    (t (:background "yellow")))
  "Default face for hi-lock mode."
  :group 'hi-lock-faces)

(defface hi-pink
  '((((background dark)) (:background "pink" :foreground "black"))
    (t (:background "pink")))
  "Face for hi-lock mode."
  :group 'hi-lock-faces)

(defface hi-green
  '((((background dark)) (:background "green" :foreground "black"))
    (t (:background "green")))
  "Face for hi-lock mode."
  :group 'hi-lock-faces)

(defface hi-blue
  '((((background dark)) (:background "light blue" :foreground "black"))
    (t (:background "light blue")))
  "Face for hi-lock mode."
  :group 'hi-lock-faces)

(defface hi-black-b
  '((t (:weight bold)))
  "Face for hi-lock mode."
  :group 'hi-lock-faces)

(defface hi-blue-b
  '((t (:weight bold :foreground "blue")))
  "Face for hi-lock mode."
  :group 'hi-lock-faces)

(defface hi-green-b
  '((t (:weight bold :foreground "green")))
  "Face for hi-lock mode."
  :group 'hi-lock-faces)

(defface hi-red-b
  '((t (:weight bold :foreground "red")))
  "Face for hi-lock mode."
  :group 'hi-lock-faces)

(defface hi-black-hb
  '((t (:weight bold :height 1.67 :inherit variable-pitch)))
  "Face for hi-lock mode."
  :group 'hi-lock-faces)

(defvar hi-lock-file-patterns nil
  "Patterns found in file for hi-lock.  Should not be changed.")

(defvar hi-lock-interactive-patterns nil
  "Patterns provided to hi-lock by user.  Should not be changed.")

(defvar hi-lock-face-history
  (list "hi-yellow" "hi-pink" "hi-green" "hi-blue" "hi-black-b"
        "hi-blue-b" "hi-red-b" "hi-green-b" "hi-black-hb")
      "History list of faces for hi-lock interactive functions.")

;(dolist (f hi-lock-face-history) (unless (facep f) (error "%s not a face" f)))

(defvar hi-lock-regexp-history nil
  "History of regexps used for interactive fontification.")

(defvar hi-lock-file-patterns-prefix "Hi-lock"
  "Regexp for finding hi-lock patterns at top of file.")

(make-variable-buffer-local 'hi-lock-interactive-patterns)
(put 'hi-lock-interactive-patterns 'permanent-local t)
(make-variable-buffer-local 'hi-lock-regexp-history)
(put 'hi-lock-regexp-history 'permanent-local t)
(make-variable-buffer-local 'hi-lock-file-patterns)
(put 'hi-lock-file-patterns 'permanent-local t)

(defvar hi-lock-menu (make-sparse-keymap "Hi Lock")
  "Menu for hi-lock mode.")

(define-key-after hi-lock-menu [highlight-regexp]
  '(menu-item "Highlight Regexp..." highlight-regexp
              :help "Highlight text matching PATTERN (a regexp)."))

(define-key-after hi-lock-menu [highlight-phrase]
  '(menu-item "Highlight Phrase..." highlight-phrase
              :help "Highlight text matching PATTERN (a regexp processed to match phrases)."))

(define-key-after hi-lock-menu [highlight-lines-matching-regexp]
  '(menu-item "Highlight Lines..." highlight-lines-matching-regexp
              :help "Highlight lines containing match of PATTERN (a regexp).."))

(define-key-after hi-lock-menu [unhighlight-regexp]
  '(menu-item "Remove Highlighting..." unhighlight-regexp
              :help "Remove previously entered highlighting pattern."
              :enable hi-lock-interactive-patterns))

(define-key-after hi-lock-menu [hi-lock-write-interactive-patterns]
  '(menu-item "Patterns to Buffer" hi-lock-write-interactive-patterns
              :help "Insert interactively added REGEXPs into buffer at point."
              :enable hi-lock-interactive-patterns))

(define-key-after hi-lock-menu [hi-lock-find-patterns]
  '(menu-item "Patterns from Buffer" hi-lock-find-patterns
              :help "Use patterns (if any) near top of buffer."))

(defvar hi-lock-map (make-sparse-keymap "Hi Lock")
  "Key map for hi-lock.")

(define-key hi-lock-map "\C-xwi" 'hi-lock-find-patterns)
(define-key hi-lock-map "\C-xwl" 'highlight-lines-matching-regexp)
(define-key hi-lock-map "\C-xwp" 'highlight-phrase)
(define-key hi-lock-map "\C-xwh" 'highlight-regexp)
(define-key hi-lock-map "\C-xwr" 'unhighlight-regexp)
(define-key hi-lock-map "\C-xwb" 'hi-lock-write-interactive-patterns)

(unless (assq 'hi-lock-mode minor-mode-map-alist)
  (setq minor-mode-map-alist (cons (cons 'hi-lock-mode hi-lock-map)
                                   minor-mode-map-alist)))

(unless (assq 'hi-lock-mode minor-mode-alist)
  (setq minor-mode-alist (cons '(hi-lock-mode " H") minor-mode-alist)))


;; Visible Functions


;;;###autoload
(defun hi-lock-mode (&optional arg)
  "Toggle minor mode for interactively adding font-lock highlighting patterns.

If ARG positive turn hi-lock on.  Issuing a hi-lock command will also
turn hi-lock on.  When hi-lock is turned on, a \"Regexp Highlighting\"
submenu is added to the \"Edit\" menu.  The commands in the submenu,
which can be called interactively, are:

\\[highlight-regexp] REGEXP FACE
  Highlight matches of pattern REGEXP in current buffer with FACE.

\\[highlight-phrase] PHRASE FACE
  Highlight matches of phrase PHRASE in current buffer with FACE.
  (PHRASE can be any REGEXP, but spaces will be replaced by matches
  to whitespace and initial lower-case letters will become case insensitive.)
 
\\[highlight-lines-matching-regexp] REGEXP FACE
  Highlight lines containing matches of REGEXP in current buffer with FACE.

\\[unhighlight-regexp] REGEXP
  Remove highlighting on matches of REGEXP in current buffer.

\\[hi-lock-write-interactive-patterns]
  Write active REGEXPs into buffer as comments (if possible). They will
  be read the next time file is loaded or when the \\[hi-lock-find-patterns] command
  is issued.  The inserted regexps are in the form of font lock keywords.
  (See `font-lock-keywords') They may be edited and re-loaded with \\[hi-lock-find-patterns],
  any valid `font-lock-keywords' form is acceptable.

\\[hi-lock-find-patterns]
  Re-read patterns stored in buffer (in the format produced by \\[hi-lock-write-interactive-patterns]).

When hi-lock is started and if the mode is not excluded, the
beginning of the buffer is searched for lines of the form:
  Hi-lock: FOO
where FOO is a list of patterns. These are added to the font lock keywords
already present.  The patterns must start before position (number
of characters into buffer) `hi-lock-file-patterns-range'.  Patterns
will be read until
 Hi-lock: end
is found. A mode is excluded if it's in the list `hi-lock-exclude-modes'."
  (interactive)
  (let ((hi-lock-mode-prev hi-lock-mode))
    (setq hi-lock-mode
          (if (null arg) (not hi-lock-mode)
            (> (prefix-numeric-value arg) 0)))
    ;; Turned on.
    (when (and (not hi-lock-mode-prev) hi-lock-mode)
      (add-hook 'find-file-hooks 'hi-lock-find-file-hook)
      (add-hook 'font-lock-mode-hook 'hi-lock-font-lock-hook)
      (define-key-after menu-bar-edit-menu [hi-lock]
        (cons "Regexp Highlighting" hi-lock-menu))
      (dolist (buffer (buffer-list))
        (with-current-buffer buffer (hi-lock-find-patterns))))
    ;; Turned off.
    (when (and hi-lock-mode-prev (not hi-lock-mode))
      (dolist (buffer (buffer-list))
        (with-current-buffer buffer
          (when (or hi-lock-interactive-patterns hi-lock-file-patterns)
            (font-lock-remove-keywords nil hi-lock-interactive-patterns)
            (font-lock-remove-keywords nil hi-lock-file-patterns)
            (setq hi-lock-interactive-patterns nil
                  hi-lock-file-patterns nil)
            (when font-lock-mode (hi-lock-refontify)))))
      (define-key-after menu-bar-edit-menu [hi-lock] nil)
      (remove-hook 'find-file-hooks 'hi-lock-find-file-hook)
      (remove-hook 'font-lock-mode-hook 'hi-lock-font-lock-hook))))


;;;###autoload
(defalias 'highlight-lines-matching-regexp 'hi-lock-line-face-buffer)
;;;###autoload
(defun hi-lock-line-face-buffer (regexp &optional face)
  "Set face of all lines containing a match of REGEXP to FACE.

Interactively, prompt for REGEXP then FACE.  Buffer-local history
list maintained for regexps, global history maintained for faces.
\\<minibuffer-local-map>Use \\[next-history-element] and \\[previous-history-element] to retrieve next or previous history item.
\(See info node `Minibuffer History')"
  (interactive
   (list
    (hi-lock-regexp-okay
     (read-from-minibuffer "Regexp to highlight line: "
                           (cons (or (car hi-lock-regexp-history) "") 1 )
                           nil nil 'hi-lock-regexp-history))
    (hi-lock-read-face-name)))
  (unless hi-lock-mode (hi-lock-mode))
  (or (facep face) (setq face 'rwl-yellow))
  (hi-lock-set-pattern
   ;; The \\(?:...\\) grouping construct ensures that a leading ^, +, * or ?
   ;; or a trailing $ in REGEXP will be interpreted correctly.
   (list (concat "^.*\\(?:" regexp "\\).*$") (list 0 (list 'quote face) t))))


;;;###autoload
(defalias 'highlight-regexp 'hi-lock-face-buffer)
;;;###autoload
(defun hi-lock-face-buffer (regexp &optional face)
  "Set face of each match of REGEXP to FACE.

Interactively, prompt for REGEXP then FACE.  Buffer-local history
list maintained for regexps, global history maintained for faces.
\\<minibuffer-local-map>Use \\[next-history-element] and \\[previous-history-element] to retrieve next or previous history item.
\(See info node `Minibuffer History')"
  (interactive
   (list
    (hi-lock-regexp-okay
     (read-from-minibuffer "Regexp to highlight: "
                           (cons (or (car hi-lock-regexp-history) "") 1 )
                           nil nil 'hi-lock-regexp-history))
    (hi-lock-read-face-name)))
  (or (facep face) (setq face 'rwl-yellow))
  (unless hi-lock-mode (hi-lock-mode))
  (hi-lock-set-pattern (list regexp (list 0 (list 'quote face) t))))

;;;###autoload
(defalias 'highlight-phrase 'hi-lock-face-phrase-buffer)
;;;###autoload
(defun hi-lock-face-phrase-buffer (regexp &optional face)
  "Set face of each match of phrase REGEXP to FACE.

Whitespace in REGEXP converted to arbitrary whitespace and initial
lower-case letters made case insensitive."
  (interactive
   (list
    (hi-lock-regexp-okay
     (hi-lock-process-phrase
      (read-from-minibuffer "Phrase to highlight: "
                            (cons (or (car hi-lock-regexp-history) "") 1 )
                            nil nil 'hi-lock-regexp-history)))
    (hi-lock-read-face-name)))
  (or (facep face) (setq face 'rwl-yellow))
  (unless hi-lock-mode (hi-lock-mode))
  (hi-lock-set-pattern (list regexp (list 0 (list 'quote face) t))))

;;;###autoload
(defalias 'unhighlight-regexp 'hi-lock-unface-buffer)
;;;###autoload
(defun hi-lock-unface-buffer (regexp)
  "Remove highlighting of each match to REGEXP set by hi-lock.

Interactively, prompt for REGEXP.  Buffer-local history of inserted
regexp's maintained.  Will accept only regexps inserted by hi-lock
interactive functions.  \(See `hi-lock-interactive-patterns'.\)
\\<minibuffer-local-must-match-map>Use \\[minibuffer-complete] to complete a partially typed regexp.
\(See info node `Minibuffer History'.\)"
  (interactive
   (if (and (display-popup-menus-p) (vectorp (this-command-keys)))
       (catch 'snafu
	 (or
	  (x-popup-menu
	   t
	   (cons
	    `keymap
	    (cons "Select Pattern to Unhighlight"
		  (mapcar (lambda (pattern)
			    (list (car pattern)
				  (format
				   "%s (%s)" (car pattern)
				   (symbol-name
				    (car
				     (cdr (car (cdr (car (cdr pattern))))))))
				  (cons nil nil)
				  (car pattern)))
			  hi-lock-interactive-patterns))))
	  ;; If the user clicks outside the menu, meaning that they
	  ;; change their mind, x-popup-menu returns nil, and
	  ;; interactive signals a wrong number of arguments error.
	  ;; To prevent that, we return an empty string, which will
	  ;; effectively disable the rest of the function.
	  (throw 'snafu '(""))))
     (let ((history-list (mapcar (lambda (p) (car p))
                                 hi-lock-interactive-patterns)))
       (unless hi-lock-interactive-patterns
         (error "No highlighting to remove"))
       (list
        (completing-read "Regexp to unhighlight: "
                         hi-lock-interactive-patterns nil t
                         (car (car hi-lock-interactive-patterns))
                         (cons 'history-list 1))))))
  (let ((keyword (assoc regexp hi-lock-interactive-patterns)))
    (when keyword
      (font-lock-remove-keywords nil (list keyword))
      (setq hi-lock-interactive-patterns
            (delq keyword hi-lock-interactive-patterns))
      (hi-lock-refontify))))

;;;###autoload
(defun hi-lock-write-interactive-patterns ()
  "Write interactively added patterns, if any, into buffer at point.

Interactively added patterns are those normally specified using
`highlight-regexp' and `highlight-lines-matching-regexp'; they can
be found in variable `hi-lock-interactive-patterns'."
  (interactive)
  (let ((prefix (format "%s %s:" (or comment-start "") "Hi-lock")))
    (when (> (+ (point) (length prefix)) hi-lock-file-patterns-range)
      (beep)
      (message
       "Warning, inserted keywords not close enough to top of file."))
    (mapcar
     (lambda (pattern)
       (insert (format "%s (%s) %s\n"
                       prefix (prin1-to-string pattern) (or comment-end ""))))
     hi-lock-interactive-patterns)))


;; Implementation Functions

(defun hi-lock-process-phrase (phrase)
  "Convert regexp PHRASE to a regexp that matches phrases.

Blanks in PHRASE replaced by regexp that matches arbitrary whitespace
and initial lower-case letters made case insensitive."
  (let ((mod-phrase nil))
    (setq mod-phrase
          (replace-regexp-in-string
           "\\<[a-z]" (lambda (m) (format "[%s%s]" (upcase m) m)) phrase))
    (setq mod-phrase
          (replace-regexp-in-string
           "\\s-+" "[ \t\n]+" mod-phrase nil t))))

(defun hi-lock-regexp-okay (regexp)
  "Return REGEXP if it appears suitable for a font-lock pattern.

Otherwise signal an error.  A pattern that matches the null string is
not suitable."
  (if (string-match regexp "")
      (error "Regexp cannot match an empty string")
    regexp))

(defun hi-lock-read-face-name ()
  "Read face name from minibuffer with completion and history."
  (intern (completing-read
           "Highlight using face: "
           obarray 'facep t
           (cons (car hi-lock-face-history)
                 (let ((prefix
                        (try-completion
                         (substring (car hi-lock-face-history) 0 1)
                         (mapcar (lambda (f) (cons f f))
                                 hi-lock-face-history))))
                   (if (and (stringp prefix)
                            (not (equal prefix (car hi-lock-face-history))))
                       (length prefix) 0)))
           '(hi-lock-face-history . 0))))

(defun hi-lock-find-file-hook ()
  "Add hi-lock patterns, if present."
  (hi-lock-find-patterns))

(defun hi-lock-current-line (&optional end)
  "Return line number of line at point.
Optional argument END is maximum excursion."
  (interactive)
  (save-excursion
    (beginning-of-line)
    (1+ (count-lines 1 (or end (point))))))

(defun hi-lock-set-pattern (pattern)
  "Add PATTERN to list of interactively highlighted patterns and refontify."
  (hi-lock-set-patterns (list pattern)))

(defun hi-lock-set-patterns (patterns)
  "Add PATTERNS to list of interactively highlighted patterns and refontify.."
  (dolist (pattern patterns)
    (unless (member pattern hi-lock-interactive-patterns)
      (font-lock-add-keywords nil (list pattern))
      (add-to-list 'hi-lock-interactive-patterns pattern)))
  (hi-lock-refontify))

(defun hi-lock-set-file-patterns (patterns)
  "Replace file patterns list with PATTERNS and refontify."
  (when (or hi-lock-file-patterns patterns)
    (font-lock-remove-keywords nil hi-lock-file-patterns)
    (setq hi-lock-file-patterns patterns)
    (font-lock-add-keywords nil hi-lock-file-patterns)
    (hi-lock-refontify)))

(defun hi-lock-refontify ()
  "Unfontify then refontify buffer.  Used when hi-lock patterns change."
  (interactive)
  (unless font-lock-mode (font-lock-mode 1))
  (font-lock-fontify-buffer))

(defun hi-lock-find-patterns ()
  "Find patterns in current buffer for hi-lock."
  (interactive)
  (unless (memq major-mode hi-lock-exclude-modes)
    (let ((all-patterns nil)
          (target-regexp (concat "\\<" hi-lock-file-patterns-prefix ":")))
      (save-excursion
	(save-restriction
	  (widen)
	  (goto-char (point-min))
	  (re-search-forward target-regexp
			     (+ (point) hi-lock-file-patterns-range) t)
	  (beginning-of-line)
	  (while (and (re-search-forward target-regexp (+ (point) 100) t)
		      (not (looking-at "\\s-*end")))
	    (let ((patterns
		   (condition-case nil
		       (read (current-buffer))
		     (error  (message
			      (format "Could not read expression at %d"
				      (hi-lock-current-line))) nil))))
	      (if patterns
		  (setq all-patterns (append patterns all-patterns)))))))
      (when hi-lock-mode (hi-lock-set-file-patterns all-patterns))
      (if (interactive-p)
        (message (format "Hi-lock added %d patterns." (length all-patterns)))))))

(defun hi-lock-font-lock-hook ()
  "Add hi lock patterns to font-lock's."
  (when hi-lock-mode
    (font-lock-add-keywords nil hi-lock-file-patterns)
    (font-lock-add-keywords nil hi-lock-interactive-patterns)))

(provide 'hi-lock)

;;; hi-lock.el ends here
