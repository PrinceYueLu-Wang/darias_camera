# Camera Parts for Darias Robot Arm

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

---

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

---

### ROSNode : ``cam_meshes2pcd``

input:  mesh geometry file of the arm ; tf transform lisenter

output： simplfied pointcloud of the arm

process:

- mesh files already turned into ply pointcloud files via CloudCompare
- load arm links pointclouds
- get frame transform between frame `world` and frame `camera_depth_optical_frame`
- apply tf transform on the arm links pointclouds
- sum arm links pointclouds into one arm pointcloud and publish it

---

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

---
## Description for ROStopics for allInOne node


| topic name                                   | msg type                    | description                             |
| -------------------------------------------- | --------------------------- | --------------------------------------- |
| /camera_visual/raw/pointcloud_voxel_filtered | sensor_msgs::PointCloud2    | simpflied pcd from camera via grid voxl |
| /camera_visual/mesh/pointcloud_rightArm      | sensor_msgs::PointCloud2    | simpflied pcd from robot arm links      |
| /camera_visual/filtered/pointcloud           | sensor_msgs::PointCloud2    | final pcd                               |
| /camera_visual/filtered/octomap              | octomap_msgs::Octomap       | final octomap                           |
| /camera_visual/filtered/point3d              | darias_intelcamera::maplist | final 3d points array                   |

---

## Description for ROStopics for three nodes


| topic name                          | msg tpye                    | rosnode         | description                                               |
| ----------------------------------- | --------------------------- | --------------- | --------------------------------------------------------- |
| /camera_visual/raw/octomap          | octomap_msgs::Octomap       | cam_img2pcdtree | raw octomap of the camera depth pointcloud                |
| /camera_visual/raw/point_list       | darias_intelcamera::maplist | cam_img2pcdtree | raw 3dArray of cube in raw octomap                        |
| /camera_visual/raw/pointcloud"      | sensor_msgs::PointCloud2    | cam_img2pcdtree | pointcloud from raw octomap                               |
| /camera_visual/raw/pointcloud_voxel | sensor_msgs::PointCloud2    | cam_img2pcdtree | simplfied pointcloud via voxel grid                       |
| ***                                 | ***                         | ***             | ***                                                       |
| /camera_visual/mesh/rightArm        | sensor_msgs::PointCloud2    | cam_meshes2pcd  | sum of arm link pointcloud in frame `world`             |
| ***                                 | ***                         | ***             | ***                                                       |
| /camera_visual/filtered/octomap     | octomap_msgs::Octomap       | cam_pcd2map     | final octomap in frame `world`                          |
| /camera_visual/filtered/pointcloud  | sensor_msgs::PointCloud2    | cam_pcd2map     | final pointcloud in frame `world`                       |
| /camera_visual/filtered/point3d     | darias_intelcamera::maplist | cam_pcd2map     | final 3dArray of cube in final octomap in frame `world` |

## Description for self-defined ROSMSG

---

location :  ``src/darias_intelcamera/msg/maplist.msg``

content :

`float64[] center_x` : in `world` frame x coordinates array of the obstacle cube

`float64[] center_y` : in `world` frame y coordinates array of the obstacle cube

`float64[] center_z` : in `world` frame z coordinates array of the obstacle cube

`float64 sphere_radius` : radius of the obstacle cube

`int64 cube_number` : total number of obstacle cubes
