# Camera Parts for Darias Robot Arm

## Introduction

This package transfer intel realcamera's depth info into simplfied octomap and publish pointclouds and octree messages. Meanwhile it would automatically eliminate points ,which belon to robots' arms, that would benefit the afterprocessing in obstacle avoidence.

## Package dependencies

This package requires some ros package, which could be easily installed by Ubuntu `apt-get` with prefix `ros-noetic-xx`. For exmaple for pkg `octomap_msgs`, tpye in terminal 
```
sudo apt-get install ros-noetic-octomap
```
### OctoMap
Octomap is used to transfer pointcloud into grid map, which also offer functions to change the depth and resolution of the tree.

- octomap components
  - octomap_msgs   
  - octomap_ros
  - octomap_mapping

- octomap pkg name in apt-get 
  - ros-noetic-octomap-msgs
  - ros-noetic-octomap-ros
  - ros-noetic-octomap-rviz-plugins
  - ros-noetic-octomap-mapping

### PCL 
PCL (pointcloud library) in this package serves for three goals:
1. turn geometry mesh/stl file of robot arm link into pointclouds with downsampling
2. filter the pointclouds with different built-in filters

- PCL components
    - pcl_conversions
    - pcl_ros
    - pcl_msgs
 - PCL pkg name in apt-get 
    - ros-noetic-pcl-ros
    - ros-noetic-pcl-conversions
    - ros-noetic-pcl-msgs

### TF2 
tf2_ros offer functions to lookup or transformation between different frames. In this package tf2 would used to lookup transfer between world and armlink, world and camera optical frame 

- tf2_ros pkg name in apt-get 
    - ros-noetic-tf2-ros


## Description for RosNodes

### RosNode : cam_img2pcdtree

### RosNode : cam_img2pcdtree

### RosNode : cam_img2pcdtree
## Description for RosLaunch

rosbag record -O Nov29Pose1 /joint_states /camera/depth/color/points
