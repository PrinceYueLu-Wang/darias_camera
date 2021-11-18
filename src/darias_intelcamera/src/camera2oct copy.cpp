/*************************************************************************
	> File Name: src/camera2oct.cpp
	> Author: yifei wang
	> Mail: 329585095@qq.com
	> Created Time: 2021/11/15 20:53
 ************************************************************************/

#include <iostream>
#include <assert.h>
#include <vector>
#include <math.h>

//ros
#include <ros/ros.h>

//pcl
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl_ros/transforms.h>

//ros msg
#include <sensor_msgs/PointCloud2.h>
#include <geometry_msgs/Transform.h>

//octomap
#include <octomap/octomap.h>
#include <octomap_msgs/Octomap.h>
#include <octomap_msgs/conversions.h>

//tf2
#include <tf2_ros/transform_listener.h>

//msgs
#include "darias_intelcamera/maplist.h"

using namespace std;

class StateProcess
{
public:
  tf2_ros::Buffer tfBuffer_;
  tf2_ros::TransformListener *tfListener_;

  StateProcess()
  {
    //tf listner
    tfListener_ = new tf2_ros::TransformListener(tfBuffer_);

    pub_octomap = n_.advertise<octomap_msgs::Octomap>("/camera/octomap", 1);

    pub_octomap_list = n_.advertise<darias_intelcamera::maplist>("/camera/octomap_list", 1);

    // pub_cloud =n_.advertise<>

    sub_ = n_.subscribe("/camera/depth/color/points", 1, &StateProcess::callback, this);
  }

  void callback(const sensor_msgs::PointCloud2::ConstPtr &msgs)
  {

    pcl::PCLPointCloud2 pointcloud_msg;

    // sensor::PointCloud2 msg -> pcl::PointCloud2 msg

    pcl_conversions::toPCL(*msgs, pointcloud_msg);

    pcl::PointCloud<pcl::PointXYZ>::Ptr pointcloud_raw(new pcl::PointCloud<pcl::PointXYZ>);

    // pcl::PointCloud2 msg -> pcl::pointcloud
    // void fromPCLPointCloud2 (const pcl::PCLPointCloud2& msg, cl::PointCloud
    pcl::fromPCLPointCloud2(pointcloud_msg, *pointcloud_raw);

    // pcl pointcloud transform

    geometry_msgs::Transform::Ptr tf_camera(new geometry_msgs::Transform);

    // rosrun tf tf_echo image darias
    // At time 1637091276.466
    // - Translation: [-0.390, 0.106, -0.417]
    // - Rotation: in Quaternion [0.489, -0.089, 0.867, 0.031]
    //         in RPY (radian) [-0.240, -1.023, -3.079]
    //         in RPY (degree) [-13.731, -58.611, -176.390]

    // rosrun tf tf_echo darias image
    // At time 1637091240.548
    // - Translation: [0.157, -0.002, 0.559]
    // - Rotation: in Quaternion [0.489, -0.089, 0.867, -0.031]
    //         in RPY (radian) [-0.350, -1.002, -2.877]
    //         in RPY (degree) [-20.054, -57.410, -164.817]

    //
    // import ! there the transform is camera to darias
    tf_camera->translation.x = 0.158;
    tf_camera->translation.y = 0.012;
    tf_camera->translation.z = 0.562;

    tf_camera->rotation.x = -0.649;
    tf_camera->rotation.y = 0.706;
    tf_camera->rotation.z = -0.130;
    tf_camera->rotation.w = 0.252;

    //   transformPointCloud 	(const pcl::PointCloud< PointT > &  	cloud_in,
    // 	                             pcl::PointCloud< PointT > &  	cloud_out,
    // 	                             const geometry_msgs::Transform &  	transform
    // )

    pcl::PointCloud<pcl::PointXYZ>::Ptr pointcloud(new pcl::PointCloud<pcl::PointXYZ>);

    pcl_ros::transformPointCloud(*pointcloud_raw, *pointcloud, *tf_camera);

    // ROS_INFO("the header is %s",msgs->header.frame_id.c_str());

    // range = 0.02 * 2^16 = 0.02 * 256 = 5.12 m

    double octree_res = 0.02;
    octomap::OcTree tree(octree_res);

    for (auto p : pointcloud->points)
    {
      // insert cloud points into octree
      tree.updateNode(octomap::point3d(p.x, p.y, p.z), true);
    }

    tree.updateInnerOccupancy();

    int tree_node_number = 0;

    for (auto iter = tree.begin(11), end = tree.end(); iter != end; ++iter)
    {
      ++tree_node_number;
    }

    octomap_msgs::Octomap octomapMsg;
    octomap_msgs::fullMapToMsg(tree, octomapMsg);
    octomapMsg.header.frame_id = "darias";

    pub_octomap.publish(octomapMsg);

    // section to publish points xyz array

    int tree_depth = 15;

    darias_intelcamera::maplist pointsMsg;
    
    pointsMsg.sphere_radius = octree_res*2^(16-tree_depth);
    
    for (auto iter = tree.begin(15), end = tree.end(); iter != end; ++iter)
    {
      pointsMsg.center_x.push_back(iter.getX());
      pointsMsg.center_y.push_back(iter.getY());
      pointsMsg.center_z.push_back(iter.getZ());
    }

    pub_octomap_list.publish(pointsMsg);
  }

private:
  ros::NodeHandle n_;
  ros::Publisher pub_octomap;
  ros::Publisher pub_octomap_list;
  ros::Publisher pub_cloud;
  ros::Subscriber sub_;
};

int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "subscribe_and_publish");

  //Create an object of class SubscribeAndPublish that will take care of everything
  StateProcess SAPObject;

  ros::Rate loop_rate = 10;

  while (ros::ok()){

    ros::spinOnce();

    loop_rate.sleep();

  }

  // ros::spin();

  return 0;
}