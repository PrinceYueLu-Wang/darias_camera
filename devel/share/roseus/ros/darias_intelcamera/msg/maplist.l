;; Auto-generated. Do not edit!


(when (boundp 'darias_intelcamera::maplist)
  (if (not (find-package "DARIAS_INTELCAMERA"))
    (make-package "DARIAS_INTELCAMERA"))
  (shadow 'maplist (find-package "DARIAS_INTELCAMERA")))
(unless (find-package "DARIAS_INTELCAMERA::MAPLIST")
  (make-package "DARIAS_INTELCAMERA::MAPLIST"))

(in-package "ROS")
;;//! \htmlinclude maplist.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass darias_intelcamera::maplist
  :super ros::object
  :slots (_header _center_x _center_y _center_z _sphere_radius ))

(defmethod darias_intelcamera::maplist
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:center_x __center_x) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:center_y __center_y) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:center_z __center_z) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:sphere_radius __sphere_radius) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _center_x __center_x)
   (setq _center_y __center_y)
   (setq _center_z __center_z)
   (setq _sphere_radius (float __sphere_radius))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
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
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64[] _center_x
    (* 8    (length _center_x)) 4
    ;; float64[] _center_y
    (* 8    (length _center_y)) 4
    ;; float64[] _center_z
    (* 8    (length _center_z)) 4
    ;; float64 _sphere_radius
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
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
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
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
   ;;
   self)
  )

(setf (get darias_intelcamera::maplist :md5sum-) "226df555f0c0d330fad82df3aec4cf97")
(setf (get darias_intelcamera::maplist :datatype-) "darias_intelcamera/maplist")
(setf (get darias_intelcamera::maplist :definition-)
      "Header header

float64[] center_x
float64[] center_y
float64[] center_z

float64 sphere_radius



================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

")



(provide :darias_intelcamera/maplist "226df555f0c0d330fad82df3aec4cf97")


