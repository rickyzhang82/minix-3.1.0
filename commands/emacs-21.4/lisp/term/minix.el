;; Enable meta key
(let ((value (current-input-mode)))
  ;; The third arg only matters in that it is not t or nil.
  (set-input-mode (nth 0 value) (nth 1 value) t (nth 3 value)))


