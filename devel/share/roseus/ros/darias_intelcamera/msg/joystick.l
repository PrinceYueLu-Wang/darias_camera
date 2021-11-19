;; Auto-generated. Do not edit!


(when (boundp 'darias_intelcamera::joystick)
  (if (not (find-package "DARIAS_INTELCAMERA"))
    (make-package "DARIAS_INTELCAMERA"))
  (shadow 'joystick (find-package "DARIAS_INTELCAMERA")))
(unless (find-package "DARIAS_INTELCAMERA::JOYSTICK")
  (make-package "DARIAS_INTELCAMERA::JOYSTICK"))

(in-package "ROS")
;;//! \htmlinclude joystick.msg.html


(defclass darias_intelcamera::joystick
  :super ros::object
  :slots (_rh_axisX _rh_axisY _lh_axisX _lh_axisY _button_up _button_down _button_left _button_right ))

(defmethod darias_intelcamera::joystick
  (:init
   (&key
    ((:rh_axisX __rh_axisX) 0.0)
    ((:rh_axisY __rh_axisY) 0.0)
    ((:lh_axisX __lh_axisX) 0.0)
    ((:lh_axisY __lh_axisY) 0.0)
    ((:button_up __button_up) 0.0)
    ((:button_down __button_down) 0.0)
    ((:button_left __button_left) 0.0)
    ((:button_right __button_right) 0.0)
    )
   (send-super :init)
   (setq _rh_axisX (float __rh_axisX))
   (setq _rh_axisY (float __rh_axisY))
   (setq _lh_axisX (float __lh_axisX))
   (setq _lh_axisY (float __lh_axisY))
   (setq _button_up (float __button_up))
   (setq _button_down (float __button_down))
   (setq _button_left (float __button_left))
   (setq _button_right (float __button_right))
   self)
  (:rh_axisX
   (&optional __rh_axisX)
   (if __rh_axisX (setq _rh_axisX __rh_axisX)) _rh_axisX)
  (:rh_axisY
   (&optional __rh_axisY)
   (if __rh_axisY (setq _rh_axisY __rh_axisY)) _rh_axisY)
  (:lh_axisX
   (&optional __lh_axisX)
   (if __lh_axisX (setq _lh_axisX __lh_axisX)) _lh_axisX)
  (:lh_axisY
   (&optional __lh_axisY)
   (if __lh_axisY (setq _lh_axisY __lh_axisY)) _lh_axisY)
  (:button_up
   (&optional __button_up)
   (if __button_up (setq _button_up __button_up)) _button_up)
  (:button_down
   (&optional __button_down)
   (if __button_down (setq _button_down __button_down)) _button_down)
  (:button_left
   (&optional __button_left)
   (if __button_left (setq _button_left __button_left)) _button_left)
  (:button_right
   (&optional __button_right)
   (if __button_right (setq _button_right __button_right)) _button_right)
  (:serialization-length
   ()
   (+
    ;; float64 _rh_axisX
    8
    ;; float64 _rh_axisY
    8
    ;; float64 _lh_axisX
    8
    ;; float64 _lh_axisY
    8
    ;; float64 _button_up
    8
    ;; float64 _button_down
    8
    ;; float64 _button_left
    8
    ;; float64 _button_right
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _rh_axisX
       (sys::poke _rh_axisX (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _rh_axisY
       (sys::poke _rh_axisY (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _lh_axisX
       (sys::poke _lh_axisX (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _lh_axisY
       (sys::poke _lh_axisY (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _button_up
       (sys::poke _button_up (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _button_down
       (sys::poke _button_down (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _button_left
       (sys::poke _button_left (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _button_right
       (sys::poke _button_right (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _rh_axisX
     (setq _rh_axisX (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _rh_axisY
     (setq _rh_axisY (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _lh_axisX
     (setq _lh_axisX (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _lh_axisY
     (setq _lh_axisY (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _button_up
     (setq _button_up (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _button_down
     (setq _button_down (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _button_left
     (setq _button_left (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _button_right
     (setq _button_right (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get darias_intelcamera::joystick :md5sum-) "71f51f585b7d21a17e5851f8e46a743b")
(setf (get darias_intelcamera::joystick :datatype-) "darias_intelcamera/joystick")
(setf (get darias_intelcamera::joystick :definition-)
      "float64 rh_axisX
float64 rh_axisY

float64 lh_axisX
float64 lh_axisY

float64 button_up
float64 button_down

float64 button_left
float64 button_right
")



(provide :darias_intelcamera/joystick "71f51f585b7d21a17e5851f8e46a743b")


