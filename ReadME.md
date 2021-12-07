# Camera Parts for Darias Robot Arm

## Introduction
---

This package transfer intel realcamera's depth info into simplfied octomap and publish pointclouds and octree messages. Meanwhile it would automatically eliminate points ,which belon to robots' arms, that would benefit the afterprocessing in obstacle avoidence.

## Package dependencies
---

This package requires some ros package, which could be easily installed by Ubuntu `apt-get` with prefix `ros-noetic-xx`. For exmaple for pkg `octomap_msgs`, tpye in terminal 
```
sudo apt-get install ros-noetic-octomap
```
### OctoMap
---
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
----
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
---
tf2_ros offer functions to lookup or transformation between different frames. In this package tf2 would used to lookup transfer between world and armlink, world and camera optical frame 

- tf2_ros pkg name in apt-get 
    - ros-noetic-tf2-ros


## Description for RosNodes
---
### ROSNode : ``cam_img2pcdtree``

input: RGB images and depth pointcloud from realsenses camera

output： simplfied pointcloud and octree

process : via voxel grid reduced number of the pointcloud

***

### ROSNode : ``cam_meshes2pcd``

input:  mesh geometry file of the arm ; tf transform lisenter

output： simplfied pointcloud of the arm

process: 
  - mesh files already turned into ply pointcloud files via CloudCompare
  - load arm links pointclouds
  - get frame transform between frame `world` and frame `camera_depth_optical_frame`
  - apply tf transform on the arm links pointclouds
  - sum arm links pointclouds into one arm pointcloud and publish it     
***

### ROSNode : ``cam_pcd2map``

input:  
  - pointcloud `arm`
  - pointcloud `camera`
  
output： simplfied pointcloud of the arm

process:

  - apply KD tree to get intersection parts of two clouds
  - eliminate points(intersection) from the camera pointclous
  - apply an octree to it
  - publish an 3D-array of the octree(obstacles)

## Description for ROStopics
---
| topic name                          | msg tpye                    | rosnode         | description                                 |
| ----------------------------------- | --------------------------- | --------------- | ------------------------------------------- |
| /camera_visual/raw/octomap          | octomap_msgs::Octomap       | cam_img2pcdtree | raw octomap of the camera depth pointcloud  |
| /camera_visual/raw/point_list       | darias_intelcamera::maplist | cam_img2pcdtree | raw 3dArray of cube in raw octomap          |
| /camera_visual/raw/pointcloud"      | sensor_msgs::PointCloud2    | cam_img2pcdtree | pointcloud from raw octomap                 |
| /camera_visual/raw/pointcloud_voxel | sensor_msgs::PointCloud2    | cam_img2pcdtree | simplfied pointcloud via voxel grid         |
| ***                                 | ***                         | ***             | ***                                         |
| /camera_visual/mesh/rightArm        | sensor_msgs::PointCloud2    | cam_meshes2pcd  | sum of arm link pointcloud in frame `world` |
| ***                                 | ***                         | ***             | ***                                         |
| /camera_visual/filtered/octomap     | octomap_msgs::Octomap       | cam_pcd2map     | final octomap in frame `world`              |
| /camera_visual/filtered/pointcloud  | sensor_msgs::PointCloud2    | cam_pcd2map     | final pointcloud in frame `world`           |
| /camera_visual/filtered/point3d     | darias_intelcamera::maplist | cam_pcd2map     | final 3dArray of cube in final octomap in frame `world`     |


## Description for self-defined ROSMSG
---
location :  ``src/darias_intelcamera/msg/maplist.msg``

content :

`float64[] center_x` : in `world` frame x coordinates array of the obstacle cube

`float64[] center_y` : in `world` frame y coordinates array of the obstacle cube

`float64[] center_z` : in `world` frame z coordinates array of the obstacle cube

`float64 sphere_radius` : radius of the obstacle cube

`int64 cube_number` : total number of obstacle cubes



## Usage
---
download:

- run ```git clone https://github.com/PrinceYueLu-Wang/darias_camera.git```

- create new branch with name like test and switch to remoter branch `msi_pc`
  
  run ```git checkout -b test origin/msi_pc```

---
modification:

due to relative path issue inside library `pcl-ros`, it requires full path name of ply file(mesh arm link) to load pointcloud.

in file : ```src/darias_intelcamera/src/cam_meshes2pcd.cpp```

please change the line 201 :
 ```string meshFolder = "../../../src/darias_intelcamera/mesh/arm/pointcloud/";```

into the real correct full path of the meshfolder,

for example ```/home/ias/Desktop/thesis/code/ros_camera/src/darias_intelcamera/mesh/arm/pointcloud/```

---
build
- if there were build cache errors, in catkin workingspace run :  ```rm rf ./build ./devel```
- in catkin workingspace run : ```catkin_build```

---
roslaunch
- put commands in terminal : ```ros_remote``` to apply configurations of ROS_HOST and ROS_IP  
- in catkin workingspace source rospkg file ```source ./devel/setup.bash```

- in terminal run : ```roslaunch darias_intelcamera real_with_tfadjust.launch```














rosbag record -O Nov29Pose1 /joint_states /camera/depth/color/points
