;;; vc-cvs.el --- non-resident support for CVS version-control

;; Copyright (C) 1995,98,99,2000,2001  Free Software Foundation, Inc.

;; Author:      FSF (see vc.el for full credits)
;; Maintainer:  Andre Spiegel <spiegel@gnu.org>

;; $Id: vc-cvs.el,v 1.3 2005/09/21 14:35:38 beng Exp $

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

;;; Code:

(eval-when-compile
  (require 'vc))

;;;
;;; Customization options
;;;

(defcustom vc-cvs-register-switches nil
  "*Extra switches for registering a file into CVS.
A string or list of strings passed to the checkin program by
\\[vc-register]."
  :type '(choice (const :tag "None" nil)
		 (string :tag "Argument String")
		 (repeat :tag "Argument List"
			 :value ("")
			 string))
  :version "21.1"
  :group 'vc)

(defcustom vc-cvs-diff-switches nil
  "*A string or list of strings specifying extra switches for cvs diff under VC."
    :type '(choice (const :tag "None" nil)
		 (string :tag "Argument String")
		 (repeat :tag "Argument List"
			 :value ("")
			 string))
  :version "21.1"
  :group 'vc)

(defcustom vc-cvs-header (or (cdr (assoc 'CVS vc-header-alist)) '("\$Id\$"))
  "*Header keywords to be inserted by `vc-insert-headers'."
  :version "21.1"
  :type '(repeat string)
  :group 'vc)

(defcustom vc-cvs-use-edit t
  "*Non-nil means to use `cvs edit' to \"check out\" a file.
This is only meaningful if you don't use the implicit checkout model
\(i.e. if you have $CVSREAD set)."
  :type 'boolean
  :version "21.1"
  :group 'vc)

(defcustom vc-cvs-stay-local t
  "*Non-nil means use local operations when possible for remote repositories.
This avoids slow queries over the network and instead uses heuristics
and past information to determine the current status of a file.
The value can also be a regular expression to match against the host name
of a repository; then VC only stays local for hosts that match it."
  :type '(choice (const :tag "Always stay local" t)
		 (string :tag "Host regexp")
		 (const :tag "Don't stay local" nil))
  :version "21.1"
  :group 'vc)


;;;
;;; Internal variables
;;;

(defvar vc-cvs-local-month-numbers
  '(("Jan" . 1) ("Feb" .  2) ("Mar" .  3) ("Apr" .  4)
    ("May" . 5) ("Jun" .  6) ("Jul" .  7) ("Aug" .  8)
    ("Sep" . 9) ("Oct" . 10) ("Nov" . 11) ("Dec" . 12))
  "Local association list of month numbers.")


;;;
;;; State-querying functions
;;;

;;;###autoload (defun vc-cvs-registered (f)
;;;###autoload   (when (file-readable-p (expand-file-name
;;;###autoload 			  "CVS/Entries" (file-name-directory f)))
;;;###autoload       (require 'vc-cvs)
;;;###autoload       (vc-cvs-registered f)))

(defun vc-cvs-registered (file)
  "Check if FILE is CVS registered."
  (let ((dirname (or (file-name-directory file) ""))
	(basename (file-name-nondirectory file))
        ;; make sure that the file name is searched case-sensitively
        (case-fold-search nil))
    (if (file-readable-p (expand-file-name "CVS/Entries" dirname))
	(with-temp-buffer
          (vc-insert-file (expand-file-name "CVS/Entries" dirname))
          (goto-char (point-min))
	  (cond
	   ((re-search-forward
	     (concat "^/" (regexp-quote basename) "/") nil t)
	    (beginning-of-line)
	    (vc-cvs-parse-entry file)
	    t)
	   (t nil)))
      nil)))

(defun vc-cvs-state (file)
  "CVS-specific version of `vc-state'."
  (if (vc-cvs-stay-local-p file)
      (let ((state (vc-file-getprop file 'vc-state)))
        ;; If we should stay local, use the heuristic but only if
        ;; we don't have a more precise state already available.
	(if (memq state '(up-to-date edited))
	    (vc-cvs-state-heuristic file)
	  state))
    (with-temp-buffer
      (cd (file-name-directory file))
      (vc-do-command t 0 "cvs" file "status")
      (vc-cvs-parse-status t))))

(defun vc-cvs-state-heuristic (file)
  "CVS-specific state heuristic."
  ;; If the file has not changed since checkout, consider it `up-to-date'.
  ;; Otherwise consider it `edited'.
  (let ((checkout-time (vc-file-getprop file 'vc-checkout-time))
        (lastmod (nth 5 (file-attributes file))))
    (if (equal checkout-time lastmod)
        'up-to-date
      'edited)))

(defun vc-cvs-dir-state (dir)
  "Find the CVS state of all files in DIR."
  (if (vc-cvs-stay-local-p dir)
      (vc-cvs-dir-state-heuristic dir)
    (let ((default-directory dir))
      ;; Don't specify DIR in this command, the default-directory is
      ;; enough.  Otherwise it might fail with remote repositories.
      (with-temp-buffer
	(vc-do-command t 0 "cvs" nil "status" "-l")
	(goto-char (point-min))
	(while (re-search-forward "^=+\n\\([^=\n].*\n\\|\n\\)+" nil t)
	  (narrow-to-region (match-beginning 0) (match-end 0))
	  (vc-cvs-parse-status)
	  (goto-char (point-max))
	  (widen))))))

(defun vc-cvs-workfile-version (file)
  "CVS-specific version of `vc-workfile-version'."
  ;; There is no need to consult RCS headers under CVS, because we
  ;; get the workfile version for free when we recognize that a file
  ;; is registered in CVS.
  (vc-cvs-registered file)
  (vc-file-getprop file 'vc-workfile-version))

(defun vc-cvs-checkout-model (file)
  "CVS-specific version of `vc-checkout-model'."
  (if (or (getenv "CVSREAD")
          ;; If the file is not writable (despite CVSREAD being
          ;; undefined), this is probably because the file is being
          ;; "watched" by other developers.
          ;; (If vc-mistrust-permissions was t, we actually shouldn't
          ;; trust this, but there is no other way to learn this from CVS
          ;; at the moment (version 1.9).)
          (string-match "r-..-..-." (nth 8 (file-attributes file))))
      'announce
    'implicit))

(defun vc-cvs-mode-line-string (file)
  "Return string for placement into the modeline for FILE.
Compared to the default implementation, this function handles the
special case of a CVS file that is added but not yet committed."
  (let ((state   (vc-state file))
	(rev     (vc-workfile-version file)))
    (cond ((string= rev "0")
	   ;; A file that is added but not yet committed.
	   "CVS @@")
	  ((or (eq state 'up-to-date)
	       (eq state 'needs-patch))
	   (concat "CVS-" rev))
          ((stringp state)
	   (concat "CVS:" state ":" rev))
          (t
           ;; Not just for the 'edited state, but also a fallback
           ;; for all other states.  Think about different symbols
           ;; for 'needs-patch and 'needs-merge.
           (concat "CVS:" rev)))))

(defun vc-cvs-dired-state-info (file)
  "CVS-specific version of `vc-dired-state-info'."
  (let* ((cvs-state (vc-state file))
	 (state (cond ((eq cvs-state 'edited)	"modified")
		      ((eq cvs-state 'needs-patch)	"patch")
		      ((eq cvs-state 'needs-merge)	"merge")
		      ;; FIXME: those two states cannot occur right now
		      ((eq cvs-state 'unlocked-changes)	"conflict")
		      ((eq cvs-state 'locally-added)	"added")
		      )))
    (if state (concat "(" state ")"))))


;;;
;;; State-changing functions
;;;

(defun vc-cvs-register (file &optional rev comment)
  "Register FILE into the CVS version-control system.
COMMENT can be used to provide an initial description of FILE.

`vc-register-switches' and `vc-cvs-register-switches' are passed to
the CVS command (in that order)."
    (let ((switches (list
		     (if (stringp vc-register-switches)
			 (list vc-register-switches)
		       vc-register-switches)
		     (if (stringp vc-cvs-register-switches)
			 (list vc-cvs-register-switches)
		       vc-cvs-register-switches))))

      (apply 'vc-do-command nil 0 "cvs" file
	     "add"
	     (and comment (string-match "[^\t\n ]" comment)
		  (concat "-m" comment))
	     switches)))

(defun vc-cvs-responsible-p (file)
  "Return non-nil if CVS thinks it is responsible for FILE."
  (file-directory-p (expand-file-name "CVS"
				      (if (file-directory-p file)
					  file
					(file-name-directory file)))))

(defun vc-cvs-could-register (file)
  "Return non-nil if FILE could be registered in CVS.
This is only possible if CVS is responsible for FILE's directory."
  (vc-cvs-responsible-p file))

(defun vc-cvs-checkin (file rev comment)
  "CVS-specific version of `vc-backend-checkin'."
  (let ((switches (if (stringp vc-checkin-switches)
		      (list vc-checkin-switches)
		    vc-checkin-switches))
	status)
    ;; explicit check-in to the trunk requires a double check-in (first
    ;; unexplicit) (CVS-1.3)
    (if (and rev (vc-trunk-p rev))
	(apply 'vc-do-command nil 1 "cvs" file
	       "ci" "-m" "intermediate"
	       switches))
    (setq status (apply 'vc-do-command nil 1 "cvs" file
			"ci" (if rev (concat "-r" rev))
			(concat "-m" comment)
			switches))
    (set-buffer "*vc*")
    (goto-char (point-min))
    (when (not (zerop status))
      ;; Check checkin problem.
      (cond
       ((re-search-forward "Up-to-date check failed" nil t)
        (vc-file-setprop file 'vc-state 'needs-merge)
        (error (substitute-command-keys
                (concat "Up-to-date check failed: "
                        "type \\[vc-next-action] to merge in changes"))))
       (t
        (pop-to-buffer (current-buffer))
        (goto-char (point-min))
        (shrink-window-if-larger-than-buffer)
        (error "Check-in failed"))))
    ;; Update file properties
    (vc-file-setprop
     file 'vc-workfile-version
     (vc-parse-buffer "^\\(new\\|initial\\) revision: \\([0-9.]+\\)" 2))
    ;; Forget the checkout model of the file, because we might have
    ;; guessed wrong when we found the file.  After commit, we can
    ;; tell it from the permissions of the file (see
    ;; vc-cvs-checkout-model).
    (vc-file-setprop file 'vc-checkout-model nil)
    ;; if this was an explicit check-in, remove the sticky tag
    (if rev (vc-do-command nil 0 "cvs" file "update" "-A"))))

(defun vc-cvs-checkout (file &optional editable rev workfile)
  "Retrieve a revision of FILE into a WORKFILE.
EDITABLE non-nil means that the file should be writable.
REV is the revision to check out into WORKFILE."
  (let ((filename (or workfile file))
	(file-buffer (get-file-buffer file))
	switches)
    (message "Checking out %s..." filename)
    (save-excursion
      ;; Change buffers to get local value of vc-checkout-switches.
      (if file-buffer (set-buffer file-buffer))
      (setq switches (if (stringp vc-checkout-switches)
			 (list vc-checkout-switches)
		       vc-checkout-switches))
      ;; Save this buffer's default-directory
      ;; and use save-excursion to make sure it is restored
      ;; in the same buffer it was saved in.
      (let ((default-directory default-directory))
	(save-excursion
	  ;; Adjust the default-directory so that the check-out creates
	  ;; the file in the right place.
	  (setq default-directory (file-name-directory filename))
	  (if workfile
	      (let ((failed t)
                    (backup-name (if (string= file workfile)
                                     (car (find-backup-file-name filename)))))
                (when backup-name
                  (copy-file filename backup-name
                             'ok-if-already-exists 'keep-date)
                  (unless (file-writable-p filename)
                    (set-file-modes filename
                                    (logior (file-modes filename) 128))))
		(unwind-protect
		    (progn
                      (let ((coding-system-for-read 'no-conversion)
                            (coding-system-for-write 'no-conversion))
                        (with-temp-file filename
                          (apply 'vc-do-command
                                 (current-buffer) 0 "cvs" file
                                 "-Q"	; suppress diagnostic output
                                 "update"
                                 (and (stringp rev)
                                      (not (string= rev ""))
                                      (concat "-r" rev))
                                 "-p"
                                 switches)))
		      (setq failed nil))
		  (if failed
                      (if backup-name
                          (rename-file backup-name filename
                                       'ok-if-already-exists)
                        (if (file-exists-p filename)
                            (delete-file filename)))
                    (and backup-name
                         (not vc-make-backup-files)
                         (delete-file backup-name)))))
	    (if (and (file-exists-p file) (not rev))
		;; If no revision was specified, just make the file writable
		;; if necessary (using `cvs-edit' if requested).
                (and editable (not (eq (vc-cvs-checkout-model file) 'implicit))
                     (if vc-cvs-use-edit
                         (vc-do-command nil 0 "cvs" file "edit")
                       (set-file-modes file (logior (file-modes file) 128))
                       (if file-buffer (toggle-read-only -1))))
              ;; Check out a particular version (or recreate the file).
              (vc-file-setprop file 'vc-workfile-version nil)
              (apply 'vc-do-command nil 0 "cvs" file
                     (and editable
                          (or (not (file-exists-p file))
                              (not (eq (vc-cvs-checkout-model file)
                                       'implicit)))
                          "-w")
                     "update"
                     ;; default for verbose checkout: clear the sticky tag so
                     ;; that the actual update will get the head of the trunk
                     (if (or (not rev) (eq rev t) (string= rev ""))
                         "-A"
                       (concat "-r" rev))
                     switches))))
	(vc-mode-line file)
	(message "Checking out %s...done" filename)))))

(defun vc-cvs-revert (file &optional contents-done)
  "Revert FILE to the version it was based on."
  (unless contents-done
    ;; Check out via standard output (caused by the final argument
    ;; FILE below), so that no sticky tag is set.
    (vc-cvs-checkout file nil (vc-workfile-version file) file))
  (unless (eq (vc-checkout-model file) 'implicit)
    (if vc-cvs-use-edit
        (vc-do-command nil 0 "cvs" file "unedit")
      ;; Make the file read-only by switching off all w-bits
      (set-file-modes file (logand (file-modes file) 3950)))))

(defun vc-cvs-merge (file first-version &optional second-version)
  "Merge changes into current working copy of FILE.
The changes are between FIRST-VERSION and SECOND-VERSION."
  (vc-do-command nil 0 "cvs" file
                 "update" "-kk"
                 (concat "-j" first-version)
                 (concat "-j" second-version))
  (vc-file-setprop file 'vc-state 'edited)
  (save-excursion
    (set-buffer (get-buffer "*vc*"))
    (goto-char (point-min))
    (if (re-search-forward "conflicts during merge" nil t)
        1				; signal error
      0)))				; signal success

(defun vc-cvs-merge-news (file)
  "Merge in any new changes made to FILE."
  (message "Merging changes into %s..." file)
  (save-excursion
    ;; (vc-file-setprop file 'vc-workfile-version nil)
    (vc-file-setprop file 'vc-checkout-time 0)
    (vc-do-command nil 0 "cvs" file "update")
    ;; Analyze the merge result reported by CVS, and set
    ;; file properties accordingly.
    (set-buffer (get-buffer "*vc*"))
    (goto-char (point-min))
    ;; get new workfile version
    (if (re-search-forward (concat "^Merging differences between "
				   "[01234567890.]* and "
				   "\\([01234567890.]*\\) into")
			   nil t)
	(vc-file-setprop file 'vc-workfile-version (match-string 1))
      (vc-file-setprop file 'vc-workfile-version nil))
    ;; get file status
    (prog1
        (if (eq (buffer-size) 0)
            0 ;; there were no news; indicate success
          (if (re-search-forward
               (concat "^\\([CMUP] \\)?"
                       (regexp-quote (file-name-nondirectory file))
                       "\\( already contains the differences between \\)?")
               nil t)
              (cond
               ;; Merge successful, we are in sync with repository now
               ((or (match-string 2)
                    (string= (match-string 1) "U ")
                    (string= (match-string 1) "P "))
                (vc-file-setprop file 'vc-state 'up-to-date)
                (vc-file-setprop file 'vc-checkout-time
                                 (nth 5 (file-attributes file)))
                0);; indicate success to the caller
               ;; Merge successful, but our own changes are still in the file
               ((string= (match-string 1) "M ")
                (vc-file-setprop file 'vc-state 'edited)
                0);; indicate success to the caller
               ;; Conflicts detected!
               (t
                (vc-file-setprop file 'vc-state 'edited)
                1);; signal the error to the caller
               )
            (pop-to-buffer "*vc*")
            (error "Couldn't analyze cvs update result")))
      (message "Merging changes into %s...done" file))))


;;;
;;; History functions
;;;

(defun vc-cvs-print-log (file)
  "Get change log associated with FILE."
  (vc-do-command
   nil
   (if (and (vc-cvs-stay-local-p file) (fboundp 'start-process)) 'async 0)
   "cvs" file "log"))

(defun vc-cvs-show-log-entry (version)
  (when (re-search-forward
	 ;; also match some context, for safety
	 (concat "----\nrevision " version
		 "\\(\tlocked by:.*\n\\|\n\\)date: ") nil t)
    ;; set the display window so that
    ;; the whole log entry is displayed
    (let (start end lines)
      (beginning-of-line) (forward-line -1) (setq start (point))
      (if (not (re-search-forward "^----*\nrevision" nil t))
	  (setq end (point-max))
	(beginning-of-line) (forward-line -1) (setq end (point)))
      (setq lines (count-lines start end))
      (cond
       ;; if the global information and this log entry fit
       ;; into the window, display from the beginning
       ((< (count-lines (point-min) end) (window-height))
	(goto-char (point-min))
	(recenter 0)
	(goto-char start))
       ;; if the whole entry fits into the window,
       ;; display it centered
       ((< (1+ lines) (window-height))
	(goto-char start)
	(recenter (1- (- (/ (window-height) 2) (/ lines 2)))))
       ;; otherwise (the entry is too large for the window),
       ;; display from the start
       (t
	(goto-char start)
	(recenter 0))))))

(defun vc-cvs-diff (file &optional oldvers newvers)
  "Get a difference report using CVS between two versions of FILE."
  (let (options status (diff-switches-list (vc-diff-switches-list cvs)))
    (if (string= (vc-workfile-version file) "0")
	;; This file is added but not yet committed; there is no master file.
	(if (or oldvers newvers)
	    (error "No revisions of %s exist" file)
	  ;; we regard this as "changed".
	  ;; diff it against /dev/null.
          (apply 'vc-do-command "*vc-diff*"
                 1 "diff" file
                 (append diff-switches-list '("/dev/null"))))
      (setq status
            (apply 'vc-do-command "*vc-diff*"
                   (if (and (vc-cvs-stay-local-p file)
			    (fboundp 'start-process))
		       'async
		     1)
                   "cvs" file "diff"
                   (and oldvers (concat "-r" oldvers))
                   (and newvers (concat "-r" newvers))
                   diff-switches-list))
      (if (vc-cvs-stay-local-p file)
          1 ;; async diff, pessimistic assumption
        status))))

(defun vc-cvs-diff-tree (dir &optional rev1 rev2)
  "Diff all files at and below DIR."
  (with-current-buffer "*vc-diff*"
    (setq default-directory dir)
    (if (vc-cvs-stay-local-p dir)
        ;; local diff: do it filewise, and only for files that are modified
        (vc-file-tree-walk
         dir
         (lambda (f)
           (vc-exec-after
            `(let ((coding-system-for-read (vc-coding-system-for-diff ',f)))
               ;; possible optimization: fetch the state of all files
               ;; in the tree via vc-cvs-dir-state-heuristic
               (unless (vc-up-to-date-p ',f)
                 (message "Looking at %s" ',f)
                 (vc-diff-internal ',f ',rel1 ',rel2))))))
      ;; cvs diff: use a single call for the entire tree
      (let ((coding-system-for-read
             (or coding-system-for-read 'undecided)))
        (apply 'vc-do-command "*vc-diff*" 1 "cvs" nil "diff"
               (and rel1 (concat "-r" rel1))
               (and rel2 (concat "-r" rel2))
               (vc-diff-switches-list cvs))))))

(defun vc-cvs-annotate-command (file buffer &optional version)
  "Execute \"cvs annotate\" on FILE, inserting the contents in BUFFER.
Optional arg VERSION is a version to annotate from."
  (vc-do-command buffer 0 "cvs" file "annotate" (if version
                                                    (concat "-r" version))))

(defun vc-cvs-annotate-difference (point)
  "Return the difference between the time of the line and the current time.
Return values are as defined for `current-time'."
  ;; We need a list of months and their corresponding numbers.
  (if (looking-at "^\\S-+\\s-+\\S-+\\s-+\\([0-9]+\\)-\\(\\sw+\\)-\\([0-9]+\\)): ")
      (progn
	(let* ((day (string-to-number (match-string 1)))
	       (month (cdr (assoc (match-string 2) vc-cvs-local-month-numbers)))
	       (year-tmp (string-to-number (match-string 3)))
	       ;; Years 0..68 are 2000..2068.
	       ;; Years 69..99 are 1969..1999.
	       (year (+ (cond ((> 69 year-tmp) 2000)
			      ((> 100 year-tmp) 1900)
			      (t 0))
			year-tmp)))
	  (goto-char (match-end 0)) ; Position at end makes for nicer overlay result
	  (- (car (current-time))
	     (car (encode-time 0 0 0 day month year)))))
    ;; If we did not look directly at an annotation, there might be
    ;; some further down.  This is the case if we are positioned at
    ;; the very top of the buffer, for instance.
    (if (re-search-forward
	 "^\\S-+\\s-+\\S-+\\s-+\\([0-9]+\\)-\\(\\sw+\\)-\\([0-9]+\\)): " nil t)
	(progn
	  (beginning-of-line nil)
	  (vc-cvs-annotate-difference (point))))))


;;;
;;; Snapshot system
;;;

(defun vc-cvs-create-snapshot (dir name branchp)
  "Assign to DIR's current version a given NAME.
If BRANCHP is non-nil, the name is created as a branch (and the current
workspace is immediately moved to that new branch)."
  (vc-do-command nil 0 "cvs" dir "tag" "-c" (if branchp "-b") name)
  (when branchp (vc-do-command nil 0 "cvs" dir "update" "-r" name)))

(defun vc-cvs-retrieve-snapshot (dir name update)
  "Retrieve a snapshot at and below DIR.
NAME is the name of the snapshot; if it is empty, do a `cvs update'.
If UPDATE is non-nil, then update (resynch) any affected buffers."
  (with-current-buffer (get-buffer-create "*vc*")
    (let ((default-directory dir))
      (erase-buffer)
      (if (or (not name) (string= name ""))
	  (vc-do-command t 0 "cvs" nil "update")
	(vc-do-command t 0 "cvs" nil "update" "-r" name))
      (when update
	(goto-char (point-min))
	(while (not (eobp))
	  (if (looking-at "\\([CMUP]\\) \\(.*\\)")
	      (let* ((file (expand-file-name (match-string 2) dir))
		     (state (match-string 1))
		     (buffer (find-buffer-visiting file)))
		(when buffer
		  (cond
		   ((or (string= state "U")
			(string= state "P"))
		    (vc-file-setprop file 'vc-state 'up-to-date)
		    (vc-file-setprop file 'vc-workfile-version nil)
		    (vc-file-setprop file 'vc-checkout-time
				     (nth 5 (file-attributes file))))
		   ((or (string= state "M")
			(string= state "C"))
		    (vc-file-setprop file 'vc-state 'edited)
		    (vc-file-setprop file 'vc-workfile-version nil)
		    (vc-file-setprop file 'vc-checkout-time 0)))
		  (vc-resynch-buffer file t t))))
	  (forward-line 1))))))


;;;
;;; Miscellaneous
;;;

(defun vc-cvs-make-version-backups-p (file)
  "Return non-nil if version backups should be made for FILE."
  (vc-cvs-stay-local-p file))

(defun vc-cvs-check-headers ()
  "Check if the current file has any headers in it."
  (save-excursion
    (goto-char (point-min))
    (re-search-forward "\\$[A-Za-z\300-\326\330-\366\370-\377]+\
\\(: [\t -#%-\176\240-\377]*\\)?\\$" nil t)))


;;;
;;; Internal functions
;;;

(defun vc-cvs-stay-local-p (file)
  "Return non-nil if VC should stay local when handling FILE."
  (if vc-cvs-stay-local
      (let* ((dirname (if (file-directory-p file)
			  (directory-file-name file)
			(file-name-directory file)))
	     (prop
	      (or (vc-file-getprop dirname 'vc-cvs-stay-local-p)
		  (let ((rootname (expand-file-name "CVS/Root" dirname)))
		    (vc-file-setprop
		     dirname 'vc-cvs-stay-local-p
		     (when (file-readable-p rootname)
		       (with-temp-buffer
			 (vc-insert-file rootname)
			 (goto-char (point-min))
			 (if (looking-at "\\([^:]*\\):")
			     (if (not (stringp vc-cvs-stay-local))
				 'yes
			       (let ((hostname (match-string 1)))
				 (if (string-match vc-cvs-stay-local hostname)
				     'yes
				   'no)))
			   'no))))))))
	(if (eq prop 'yes) t nil))))

(defun vc-cvs-parse-status (&optional full)
  "Parse output of \"cvs status\" command in the current buffer.
Set file properties accordingly.  Unless FULL is t, parse only
essential information."
  (let (file status)
    (goto-char (point-min))
    (if (re-search-forward "^File: " nil t)
        (cond
         ((looking-at "no file") nil)
         ((re-search-forward "\\=\\([^ \t]+\\)" nil t)
	  (setq file (expand-file-name (match-string 1)))
          (vc-file-setprop file 'vc-backend 'CVS)
          (if (not (re-search-forward "\\=[ \t]+Status: \\(.*\\)" nil t))
              (setq status "Unknown")
            (setq status (match-string 1)))
          (if (and full
                   (re-search-forward
                    "\\(RCS Version\\|RCS Revision\\|Repository revision\\):\
\[\t ]+\\([0-9.]+\\)"
                    nil t))
              (vc-file-setprop file 'vc-latest-version (match-string 2)))
          (vc-file-setprop 
           file 'vc-state
           (cond
            ((string-match "Up-to-date" status)
             (vc-file-setprop file 'vc-checkout-time
                              (nth 5 (file-attributes file)))
             'up-to-date)
            ((string-match "Locally Modified" status)             'edited)
            ((string-match "Needs Merge" status)                  'needs-merge)
            ((string-match "Needs \\(Checkout\\|Patch\\)" status) 'needs-patch)
            (t 'edited))))))))

(defun vc-cvs-dir-state-heuristic (dir)
  "Find the CVS state of all files in DIR, using only local information."
  (with-temp-buffer
    (vc-insert-file (expand-file-name "CVS/Entries" dir))
    (goto-char (point-min))
    (while (not (eobp))
      (when (looking-at "/\\([^/]*\\)/")
	(let ((file (expand-file-name (match-string 1) dir)))
	  (unless (vc-file-getprop file 'vc-state)
	    (vc-cvs-parse-entry file t))))
      (forward-line 1))))

(defun vc-cvs-parse-entry (file &optional set-state)
  "Parse a line from CVS/Entries.
Compare modification time to that of the FILE, set file properties
accordingly.  However, `vc-state' is set only if optional arg SET-STATE
is non-nil."
  (cond
   ;; entry for a "locally added" file (not yet committed)
   ((looking-at "/[^/]+/0/")
    (vc-file-setprop file 'vc-checkout-time 0)
    (vc-file-setprop file 'vc-workfile-version "0")
    (if set-state (vc-file-setprop file 'vc-state 'edited)))
   ;; normal entry
   ((looking-at
     (concat "/[^/]+"
	     ;; revision
	     "/\\([^/]*\\)"
	     ;; timestamp
	     "/[A-Z][a-z][a-z]"       ;; week day (irrelevant)
	     " \\([A-Z][a-z][a-z]\\)" ;; month name
	     " *\\([0-9]*\\)"         ;; day of month
	     " \\([0-9]*\\):\\([0-9]*\\):\\([0-9]*\\)"  ;; hms
	     " \\([0-9]*\\)"          ;; year
	     ;; optional conflict field
	     "\\(+[^/]*\\)?/"))
    (vc-file-setprop file 'vc-workfile-version (match-string 1))
    ;; compare checkout time and modification time
    (let ((second (string-to-number (match-string 6)))
	  (minute (string-to-number (match-string 5)))
	  (hour (string-to-number (match-string 4)))
	  (day (string-to-number (match-string 3)))
	  (year (string-to-number (match-string 7)))
	  (month (/ (string-match
		     (match-string 2)
		     "xxxJanFebMarAprMayJunJulAugSepOctNovDec")
		    3))
	  (mtime (nth 5 (file-attributes file))))
      (cond ((equal mtime
		    (encode-time second minute hour day month year 0))
	     (vc-file-setprop file 'vc-checkout-time mtime)
	     (if set-state (vc-file-setprop file 'vc-state 'up-to-date)))
	    (t
	     (vc-file-setprop file 'vc-checkout-time 0)
	     (if set-state (vc-file-setprop file 'vc-state 'edited))))))
   ;; entry with arbitrary text as timestamp
   ;; (this means we should consider it modified)
   ((looking-at
     (concat "/[^/]+"
	     ;; revision
	     "/\\([^/]*\\)"
	     ;; timestamp (arbitrary text)
	     "/[^/]*"
	     ;; optional conflict field
	     "\\(+[^/]*\\)?/"))
    (vc-file-setprop file 'vc-workfile-version (match-string 1))
    (vc-file-setprop file 'vc-checkout-time 0)
    (if set-state (vc-file-setprop file 'vc-state 'edited)))))

(provide 'vc-cvs)

;;; vc-cvs.el ends here
