;; Auto-generated. Do not edit!


(when (boundp 'darias_intelcamera::maplist)
  (if (not (find-package "DARIAS_INTELCAMERA"))
    (make-package "DARIAS_INTELCAMERA"))
  (shadow 'maplist (find-package "DARIAS_INTELCAMERA")))
(unless (find-package "DARIAS_INTELCAMERA::MAPLIST")
  (make-package "DARIAS_INTELCAMERA::MAPLIST"))

(in-package "ROS")
;;//! \htmlinclude maplist.msg.html


(defclass darias_intelcamera::maplist
  :super ros::object
  :slots (_center_x _center_y _center_z _sphere_radius _cube_number ))

(defmethod darias_intelcamera::maplist
  (:init
   (&key
    ((:center_x __center_x) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:center_y __center_y) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:center_z __center_z) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:sphere_radius __sphere_radius) 0.0)
    ((:cube_number __cube_number) 0)
    )
   (send-super :init)
   (setq _center_x __center_x)
   (setq _center_y __center_y)
   (setq _center_z __center_z)
   (setq _sphere_radius (float __sphere_radius))
   (setq _cube_number (round __cube_number))
   self)
  (:center_x
   (&optional __center_x)
   (if __center_x (setq _center_x __center_x)) _center_x)
  (:center_y
   (&optional __center_y)
   (if __center_y (setq _center_y __center_y)) _center_y)
  (:center_z
   (&optional __center_z)
   (if __center_z (setq _center_z __center_z)) _center_z)
  (:sphere_radius
   (&optional __sphere_radius)
   (if __sphere_radius (setq _sphere_radius __sphere_radius)) _sphere_radius)
  (:cube_number
   (&optional __cube_number)
   (if __cube_number (setq _cube_number __cube_number)) _cube_number)
  (:serialization-length
   ()
   (+
    ;; float64[] _center_x
    (* 8    (length _center_x)) 4
    ;; float64[] _center_y
    (* 8    (length _center_y)) 4
    ;; float64[] _center_z
    (* 8    (length _center_z)) 4
    ;; float64 _sphere_radius
    8
    ;; int64 _cube_number
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64[] _center_x
     (write-long (length _center_x) s)
     (dotimes (i (length _center_x))
       (sys::poke (elt _center_x i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _center_y
     (write-long (length _center_y) s)
     (dotimes (i (length _center_y))
       (sys::poke (elt _center_y i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _center_z
     (write-long (length _center_z) s)
     (dotimes (i (length _center_z))
       (sys::poke (elt _center_z i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64 _sphere_radius
       (sys::poke _sphere_radius (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; int64 _cube_number
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _cube_number (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _cube_number) (= (length (_cube_number . bv)) 2)) ;; bignum
              (write-long (ash (elt (_cube_number . bv) 0) 0) s)
              (write-long (ash (elt (_cube_number . bv) 1) -1) s))
             ((and (class _cube_number) (= (length (_cube_number . bv)) 1)) ;; big1
              (write-long (elt (_cube_number . bv) 0) s)
              (write-long (if (>= _cube_number 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _cube_number s)(write-long (if (>= _cube_number 0) 0 #xffffffff) s)))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64[] _center_x
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _center_x (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _center_x i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _center_y
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _center_y (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _center_y i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _center_z
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _center_z (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _center_z i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64 _sphere_radius
     (setq _sphere_radius (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; int64 _cube_number
#+(or :alpha :irix6 :x86_64)
      (setf _cube_number (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _cube_number (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;;
   self)
  )

(setf (get darias_intelcamera::maplist :md5sum-) "a13af0fc5407b2a8448e9cb9d1e85a83")
(setf (get darias_intelcamera::maplist :datatype-) "darias_intelcamera/maplist")
(setf (get darias_intelcamera::maplist :definition-)
      "float64[] center_x
float64[] center_y
float64[] center_z

float64 sphere_radius

int64 cube_number



")



(provide :darias_intelcamera/maplist "a13af0fc5407b2a8448e9cb9d1e85a83")


