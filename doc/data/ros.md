TF

```
roslaunch realsense2_description view_d435i_model.launch
```


```
 rosrun tf tf_echo camera_link camera_color_optical_frame

```

```
At time 0.000
- Translation: [0.000, 0.000, 0.000]
- Rotation: in Quaternion [-0.500, 0.500, -0.500, 0.500]
            in RPY (radian) [-1.571, -0.000, -1.571]
            in RPY (degree) [-90.000, -0.000, -90.000]

```

rosrun tf static_transform_publisher x y z qx qy qz qw frame_id child_frame_id  period_in_ms

```
<node pkg="tf" type="static_transform_publisher" name="link1_broadcaster" args="1 0 0 0 0 0 1 link1_parent link1 100" />
rosrun tf static_transform_publisher x y z qx qy qz qw frame_id child_frame_id  period_in_ms

```

```

rosrun tf static_transform_publisher 0 0 0 -0.5 0.5 -0.5 0.5 camera_link camera_color_optical_frame 100

<node pkg="tf" type="static_transform_publisher" name="camera_tf" args="0 0 0 -0.5 0.5 -0.5 0.5 camera_link camera_color_optical_frame 100" />
```
