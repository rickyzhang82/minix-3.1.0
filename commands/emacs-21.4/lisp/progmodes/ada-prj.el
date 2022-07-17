;;; ada-prj.el --- easy editing of project files for the ada-mode

;; Copyright (C) 1998, 1999 Free Software Foundation, Inc.

;; Author: Emmanuel Briot <briot@gnat.com>
;; Ada Core Technologies's version:   $Revision: 1.3 $
;; Keywords: languages, ada, project file

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

;;; This package provides a set of functions to easily edit the project
;;; files used by the ada-mode.
;;; The only function publicly available here is `ada-customize'.
;;; See the documentation of the Ada mode for more information on the project
;;; files.
;;; Internally, a project file is represented as a property list, with each
;;; field of the project file matching one property of the list.

;;; Code:


;; ----- Requirements -----------------------------------------------------

(require 'cus-edit)

;; ----- Buffer local variables -------------------------------------------

(defvar ada-prj-current-values nil
  "Hold the current value of the fields, This is a property list.")
(make-variable-buffer-local 'ada-prj-current-values)

(defvar ada-prj-default-values nil
  "Hold the default value for the fields, This is a property list.")
(make-variable-buffer-local 'ada-prj-default-values)

(defvar ada-prj-ada-buffer nil
  "Indicates what Ada source file was being edited.")


;; ----- Functions --------------------------------------------------------

(defun ada-prj-new ()
  "Open a new project file"
  (interactive)
  (let* ((prj
	  (if (my-local-variable-if-set-p 'ada-prj-prj-file (current-buffer))
	      ada-prj-prj-file
	    "default.adp"))
	 (filename (read-file-name "Project file: "
				   (if prj "" nil)
				   nil
				   nil
				   prj)))
    (if (not (string= (file-name-extension filename t) ".adp"))
	(error "File name extension for project files must be .adp"))
    
    (ada-customize nil filename)))

(defun ada-prj-edit ()
  "Editing the project file associated with the current Ada buffer.
If there is none, opens a new project file"
  (interactive)
  (let ((file (ada-prj-find-prj-file)))
    (if file
	(progn
	  (ada-reread-prj-file file)
	  (ada-customize))
      (ada-prj-new))))

(defun ada-prj-add-ada-menu ()
  "Add a new submenu to the Ada menu.
The items are added to the menu NAME in map MAP. NAME should be the same
name as was passed to `ada-create-menu'."
  (if ada-xemacs
      (progn
	(funcall (symbol-function 'add-menu-button)
		 '("Ada" "Project")
		 ["Edit" ada-prj-edit t] "Associate")
	(funcall (symbol-function 'add-menu-button)
		 '("Ada" "Project")
		 ["New..." ada-prj-new t] "Associate"))
    (define-key (lookup-key ada-mode-map [menu-bar Ada Project])
      [Edit] '("Edit current" . ada-prj-edit))
    (define-key (lookup-key ada-mode-map [menu-bar Ada Project])
      [New]  '("New" . ada-prj-new))))

(defun ada-prj-add-keymap ()
  "Add new keybindings for ada-prj."
  (define-key ada-mode-map "\C-cu"  'ada-prj-edit))

(defun ada-prj-initialize-values (symbol ada-buffer &optional filename)
  "Set SYMBOL to the property list of the project file FILENAME.
If FILENAME is null, read the file associated with ADA-BUFFER. If no
project file is found, returns the default values."

  (let ((prj filename))

    (if filename
      ;; If filename is given, reread if first if needed
      (if (file-exists-p filename)
	  (ada-reread-prj-file))

      ;; Else use the one from the current buffer
      (save-excursion
	(set-buffer ada-buffer)
	(set 'prj ada-prj-prj-file)))

       
    (if (and prj
	     (not (string= prj ""))
	     (assoc prj ada-xref-project-files))
	(set symbol (copy-sequence (cdr (assoc prj ada-xref-project-files))))
      
      ;;  Set default values (except for the file name if this was given
      ;;  in the buffer
      (ada-xref-set-default-prj-values symbol ada-buffer)
      (if (and prj (not (string= prj "")))
	  (set symbol (plist-put (eval symbol) 'filename prj)))
      )))
    

(defun ada-prj-save-specific-option (field)
  "Returns the string to print in the project file to save FIELD.
If the current value of FIELD is the default value, returns an empty string."
  (if (string= (plist-get ada-prj-current-values field)
	       (plist-get ada-prj-default-values field))
      ""
    (concat (symbol-name field)
	    "=" (plist-get ada-prj-current-values field) "\n")))

(defun ada-prj-save ()
  "Save the edited project file."
  (interactive)
  (let ((file-name (plist-get ada-prj-current-values 'filename))
	output)
    (set 'output
	 (concat

	  ;;  Save the fields that do not depend on the current buffer
	  ;;  only if they are different from the default value
	  
	  (ada-prj-save-specific-option 'comp_opt)
	  (ada-prj-save-specific-option 'bind_opt)
	  (ada-prj-save-specific-option 'link_opt)
	  (ada-prj-save-specific-option 'gnatmake_opt)
	  (ada-prj-save-specific-option 'cross_prefix)
	  (ada-prj-save-specific-option 'remote_machine)
	  (ada-prj-save-specific-option 'comp_cmd)
	  (ada-prj-save-specific-option 'check_cmd)
	  (ada-prj-save-specific-option 'make_cmd)
	  (ada-prj-save-specific-option 'run_cmd)
	  (ada-prj-save-specific-option 'debug_cmd)

	  ;;  Always save the fields that depend on the current buffer
	  (concat "main="      (plist-get ada-prj-current-values 'main) "\n")
	  (concat "main_unit=" (plist-get ada-prj-current-values 'main_unit) "\n")
	  (concat "build_dir=" (plist-get ada-prj-current-values 'build_dir) "\n")
	  
	  (ada-prj-set-list "casing"
			    (plist-get ada-prj-current-values 'casing)) "\n"
	  (ada-prj-set-list "src_dir"
			    (plist-get ada-prj-current-values 'src_dir)) "\n"
	  (ada-prj-set-list "obj_dir"
			    (plist-get ada-prj-current-values 'obj_dir)) "\n"
	  ))
    
    (find-file file-name)
    (erase-buffer)
    (insert output)
    (save-buffer)
    ;; kill the project buffer
    (kill-buffer nil)

    ;; kill the editor buffer
    (kill-buffer "*Customize Ada Mode*")

    ;; automatically associates the current buffer with the
    ;; new project file
    (set (make-local-variable 'ada-prj-prj-file) file-name)

    ;; force Emacs to reread the project files
    (ada-reread-prj-file file-name)
    )
  )

(defun ada-prj-load-from-file (symbol)
  "Load SYMBOL value from file. One item per line should be found in the file."
  (save-excursion
    (let ((file (read-file-name "File name: " nil nil t))
	  (buffer (current-buffer))
	  line
	  list)
      (find-file file)
      (widen)
      (goto-char (point-min))
      (while (not (eobp))
	(set 'line (buffer-substring-no-properties
		    (point) (save-excursion (end-of-line) (point))))
	(add-to-list 'list line)
	(forward-line 1)
	)
      (kill-buffer nil)
      (set-buffer buffer)
      (set 'ada-prj-current-values
	   (plist-put ada-prj-current-values
		      symbol
		      (append (plist-get ada-prj-current-values symbol)
			      (reverse list))))
      )
    (ada-prj-display-page 2)
  ))

(defun ada-prj-subdirs-of (dir)
  "Returns a list of all the subdirectories of dir, recursively."
  (let ((subdirs (directory-files dir t "^[^.].*"))
	(dirlist (list dir)))
    (while subdirs
      (if (file-directory-p (car subdirs))
	  (let ((sub (ada-prj-subdirs-of (car subdirs))))
	    (if sub
		(set 'dirlist (append sub dirlist)))))
      (set 'subdirs (cdr subdirs)))
    dirlist))

(defun ada-prj-load-directory (field &optional file-name)
  "Append the content of FILE-NAME to FIELD in the current project file.
If FILE-NAME is nil, ask the user for the name."
  (unless file-name
    (set 'file-name (read-file-name "Root directory: " nil nil t)))

  (set 'ada-prj-current-values
       (plist-put ada-prj-current-values
		  field
		  (append (plist-get ada-prj-current-values field)
			  (reverse (ada-prj-subdirs-of
				    (expand-file-name file-name))))))
  (ada-prj-display-page 2))

(defun ada-prj-display-page (tab-num)
  "Display one of the pages available in the notebook. TAB-NUM should have
a value between 1 and the maximum number of pages.
The current buffer must be the project editing buffer."

  (let ((inhibit-read-only t))
    (erase-buffer))

  ;;  Display the tabs
  
  (widget-insert "\n               Project and Editor configuration.\n
   ___________    ____________    ____________    ____________\n  / ")
  (widget-create 'push-button :notify
		 (lambda (&rest dummy) (ada-prj-display-page 1)) "General")
  (widget-insert " \\  /   ")
  (widget-create 'push-button :notify
		 (lambda (&rest dummy) (ada-prj-display-page 2)) "Paths")
  (widget-insert "  \\  / ")
  (widget-create 'push-button :notify
		 (lambda (&rest dummy) (ada-prj-display-page 3)) "Switches")
  (widget-insert " \\  / ")
  (widget-create 'push-button :notify
		 (lambda (&rest dummy) (ada-prj-display-page 4)) "Ada Menu")
  (widget-insert " \\\n")

  ;;  Display the currently selected page
  
  (cond
   
   ;;
   ;;  First page (General)
   ;;
   ((= tab-num 1)
    (widget-insert "_/             \\/______________\\/______________\\/______________\\_____\n\n")

    (widget-insert "Project file name:\n")
    (widget-insert (plist-get ada-prj-current-values 'filename))
    (widget-insert "\n\n")
;     (ada-prj-field 'filename "Project file name"
; "Enter the name and directory of the project
; file. The name of the file should be the
; name of the project itself. The extension
; must be .adp")
;     (ada-prj-field 'casing "Casing Exceptions Dictionnaries"
; "List of files that contain casing exception
; dictionnaries. All these files contain one
; identifier per line, with a special casing.
; The first file has the highest priority."
;      t)
    (ada-prj-field 'main "Executable file name"
"Name of the executable generated when you
compile your application. This should include
the full directory name, using ${build_dir} if
you wish.")
    (ada-prj-field 'main_unit "File name of the main unit"
"Name of the file to pass to the gnatmake command,
and that will create the executable.
This should not include any directory specification.")
    (ada-prj-field 'build_dir  "Build directory"
		   "Reference directory for relative paths in
src_dir and obj_dir below. This is also the directory
where the compilation is done.")
    (ada-prj-field 'remote_machine "Name of the remote machine (if any)"
"If you want to remotely compile, debug and
run your application, specify the name of a
remote machine here. This capability requires
the 'rsh' protocol on the remote machine.")
    (ada-prj-field 'cross_prefix "Prefix used in for the cross tool chain"
"When working on multiple cross targets, it is
most convenient to specify the prefix of the
tool chain here. For instance, on PowerPc
vxworks, you would enter 'powerpc-wrs-vxworks-'.
To use JGNAT, enter 'j'.")
    )

   
   ;;
   ;;  Second page (Paths)
   ;;
   ((= tab-num 2)
    (widget-insert "_/_____________\\/              \\/______________\\/______________\\_____\n\n")
    (ada-prj-field 'src_dir  "Source directories"
"Enter the list of directories where your Ada
sources can be found. These directories will be
used for the cross-references and for the default
compilation commands.
Note that src_dir includes both the build directory
and the standard runtime."
      t t
      (mapconcat (lambda(x)
		   (concat "           " x))
		 ada-xref-runtime-library-specs-path
		 "\n")
      )
    (widget-insert "\n\n")
    
    (ada-prj-field 'obj_dir  "Object directories"
"Enter the list of directories where the GNAT
library files (ALI files) can be found. These
files are used for cross-references and by the
gnatmake command.
Note that obj_dir includes both the build directory
and the standard runtime."
      t t
      (mapconcat (lambda(x)
 		   (concat "           " x))
 		 ada-xref-runtime-library-ali-path
 		 "\n")
      )
    (widget-insert "\n\n")
    )

   ;;
   ;;  Third page (Switches)
   ;;
   ((= tab-num 3)
    (widget-insert "_/_____________\\/______________\\/              \\/______________\\_____\n\n")
    (ada-prj-field 'comp_opt "Switches for the compiler"
"These switches are used in the default
compilation commands, both for compiling a
single file and rebuilding the whole project")
    (ada-prj-field 'bind_opt "Switches for the binder"
"These switches are used in the default build
command and are passed to the binder")
    (ada-prj-field 'link_opt "Switches for the linker"
"These switches are used in the default build
command and are passed to the linker")
    (ada-prj-field 'gnatmake_opt "Switches for gnatmake"
"These switches are used in the default gnatmake
command.")		   
    )

   ;;
   ;;  Fourth page
   ;;
   ((= tab-num 4)
    (widget-insert "_/_____________\\/______________\\/______________\\/              \\_____\n\n")
    (widget-insert "All the fields below can use variable substitution\n")
    (widget-insert "The syntax is ${name}, where name is the name that\n")
    (widget-insert "appears after the Help buttons in this buffer.\n")
    (widget-insert "As a special case, ${current} is replaced with the name\n")
    (widget-insert "of the file currently edited, with directory name but\n")
    (widget-insert "no extension.\n\n")
    (widget-insert
     "The environment variables ADA_INCLUDE_PATH and ADA_OBJECTS_PATH\n")
    (widget-insert
     "are set to ${src_dir} and ${obj_dir} before running the compilation\n")
    (widget-insert
     "commands, so that you don't need to specify the -aI and -aO\n")
    (widget-insert
     "switches on the command line\n\n")
    
    (ada-prj-field 'check_cmd
      "Check syntax of a single file (menu Ada->Check File)"
"This command is run to check the syntax and semantics of a file.
The file name is added at the end of this command.")
    (ada-prj-field 'comp_cmd
      "Compiling a single file (menu Ada->Compile File)"
"This command is run when the recompilation
of a single file is needed. The file name is
added at the end of this command.")
    (ada-prj-field 'make_cmd "Rebuilding the whole project (menu Ada->Build)"
"This command is run when you want to rebuild
your whole application. It is never issues
automatically and you will need to ask for it.
If remote_machine has been set, this command
will be executed on the remote machine.")
    (ada-prj-field 'run_cmd "Running the application (menu Ada->Run)"
"This command specifies how to run the
application, including any switch you need to
specify. If remote_machine has been set, this
command will be executed on the remote host.")
    (ada-prj-field 'debug_cmd "Debugging the application"
"Specifies how to debug the application, possibly
remotely if remote_machine has been set. We
recommend the following debuggers:
  > gdb
  > gdbtk
  > ddd --tty -fullname -toolbar")
    )
   )


  (widget-insert "______________________________________________________________________\n\n       ")
  (widget-create 'push-button
		 :notify (lambda (&rest ignore)
			   (ada-xref-set-default-prj-values
			    'ada-prj-current-values ada-prj-ada-buffer)
			   (ada-prj-display-page 1))
		 "Reset to Default Values")
  (widget-insert "         ")
  (widget-create 'push-button :notify (lambda (&rest ignore) (kill-buffer nil))
		 "Cancel")
  (widget-insert "         ")
  (widget-create 'push-button :notify (lambda (&rest ignore) (ada-prj-save))
		 "Save")
  (widget-insert "\n\n")

  (widget-setup)
  (beginning-of-buffer)
  )


(defun ada-customize (&optional new-file filename)
  "Edit the project file associated with the current buffer.
If there is none or NEW-FILE is non-nil, make a new one.
If FILENAME is given, edit that file."
  (interactive)

  (let ((ada-buffer (current-buffer))
	(inhibit-read-only t))

    (ada-require-project-file)
    
    (switch-to-buffer "*Customize Ada Mode*")
    (kill-all-local-variables)
    
    (ada-xref-set-default-prj-values 'ada-prj-default-values ada-buffer)
    (ada-prj-initialize-values  'ada-prj-current-values ada-buffer filename)

    (set (make-local-variable 'ada-prj-ada-buffer) ada-buffer)

    (use-local-map (copy-keymap custom-mode-map))
    (local-set-key "\C-x\C-s" 'ada-prj-save)

    (make-local-variable 'widget-keymap)
    (define-key widget-keymap "\C-x\C-s" 'ada-prj-save)

    (ada-prj-display-page 1)
  ))

;; ---------------- Utilities --------------------------------

(defun ada-prj-set-list (string ada-dir-list)
  "Join the strings in ADA-DIR-LIST into a single string. Each name is put
on a separate line that begins with STRING."
  (mapconcat (lambda (x) (concat string "=" (file-name-as-directory x)))
             ada-dir-list "\n"))


(defun ada-prj-get-prj-dir (&optional ada-file)
  "Returns the directory/name of the project file for ADA-FILE.
If ADA-FILE is nil, returns the project file for the current buffer."
  (unless ada-file
    (setq ada-file (buffer-file-name)))

  (save-excursion
    (set-buffer (get-file-buffer ada-file))
    
    (let ((prj-file (ada-prj-find-prj-file t)))
      (if (or (not prj-file)
	      (not (file-exists-p prj-file))
	      )
	  (setq prj-file
		(concat (file-name-sans-extension ada-file)
			ada-project-file-extension)))
      prj-file)
    ))

(defun ada-prj-field-modified (widget &rest dummy)
  "Callback called each time the value of WIDGET is modified. Save the
change in ada-prj-current-values so that selecting another page and coming
back keeps the new value."
  (set 'ada-prj-current-values
       (plist-put ada-prj-current-values
		  (widget-get widget 'prj-field)
		  (widget-value widget))))

(defun ada-prj-display-help (widget widget-modified event)
  "An help button in WIDGET was clicked on. The parameters are so that
this function can be used as :notify for the widget."
  (let ((text (widget-get widget 'prj-help)))
    (if event
	;;  If we have a mouse-event, popup a menu
	(widget-choose "Help"
		       (mapcar (lambda (a) (cons a t))
			       (split-string text "\n"))
		       event)
      ;;  Else display the help string just before the next group of
      ;;  variables
      (momentary-string-display
       (concat "*****Help*****\n" text "\n**************\n")
       (save-excursion (forward-line) (beginning-of-line) (point)))
      )))

(defun ada-prj-show-value (widget widget-modified event)
  (let ((value (plist-get ada-prj-current-values
			  (widget-get widget 'prj-field)))
	(inhibit-read-only t))

    ;;  If the other widget is already visible, delete it
    (if (widget-get widget 'prj-other-widget)
	(progn
	  (widget-delete (widget-get widget 'prj-other-widget))
	  (widget-put widget 'prj-other-widget nil)
	  (widget-default-value-set widget "Show Value")
	  )

      ;;  Else create it
      (save-excursion
	(mouse-set-point event)
	(forward-line 1)
	(beginning-of-line)
	(widget-put widget 'prj-other-widget
		    (widget-create 'editable-list
				   :entry-format "%i%d %v"
				   :notify 'ada-prj-field-modified
				   :help-echo (widget-get widget 'prj-help)
				   :value value
				   (list 'editable-field
					 :keymap widget-keymap)))
	(widget-default-value-set widget "Hide Value")
	)
      )
    (widget-setup)
    ))

(defun ada-prj-field (field text help-text &optional is-list is-paths after-text)
  "Create a widget to edit FIELD in the current buffer.
TEXT is a short explanation of what the field means, whereas HELP-TEXT
is the text displayed when the user pressed the help button.
If IS-LIST is non-nil, the field contains a list. Otherwise, it contains
a single string.
if IS-PATHS is true, some special buttons are added to load paths,...
AFTER-TEXT is inserted just after the widget."
  (let ((value (plist-get ada-prj-current-values field))
	(inhibit-read-only t)
	widget)
    (unless value
      (set 'value
	   (if is-list  '() "")))
    (widget-insert text)
    (widget-insert ":")
    (move-to-column 54 t)
    (widget-put (widget-create 'push-button
			       :notify 'ada-prj-display-help
			       "Help")
		'prj-help
		help-text)
    (widget-insert (concat "  (" (symbol-name field) ")\n"))
    (if is-paths
	(progn
	  (widget-create 'push-button
			 :notify
			 (list 'lambda '(&rest dummy) '(interactive)
			       (list 'ada-prj-load-from-file
				     (list 'quote field)))
			 "Load From File")
	  (widget-insert "      ")
	  (widget-create 'push-button
			 :notify
			 (list 'lambda '(&rest dummy) '(interactive)
			       (list 'ada-prj-load-directory
				     (list 'quote field)))
			 "Load Recursive Directory")
	  (widget-insert "\n           ${build_dir}\n")))
    (set 'widget
	 (if is-list
	     (if (< (length value) 15)
		 (widget-create 'editable-list
				:entry-format "%i%d %v"
				:notify 'ada-prj-field-modified
				:help-echo help-text
				:value value
				(list 'editable-field :keymap widget-keymap))
	       (let ((w (widget-create 'push-button
				       :notify 'ada-prj-show-value
				       "Show value")))
		 (widget-insert "\n")
		 (widget-put w 'prj-field field)
		 (widget-put w 'prj-help  help-text)
		 (widget-put w 'prj-other-widget nil)
		 w)
	       )
	   (widget-create 'editable-field
			  :format "%v"
			  :notify 'ada-prj-field-modified
			  :help-echo help-text
			  :keymap widget-keymap
			  value)))
    (widget-put widget 'prj-field field)
    (if after-text
	(widget-insert after-text))
    (widget-insert "\n")
    ))


;;  Set the keymap once and for all, so that the keys set by the user in his
;;  config file are not overwritten every time we open a new file.
(ada-prj-add-keymap)
(ada-prj-add-ada-menu)

(provide 'ada-prj)

;;; ada-prj.el ends here
