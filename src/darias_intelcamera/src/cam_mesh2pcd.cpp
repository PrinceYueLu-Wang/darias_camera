/*************************************************************************
	> File Name: src/cam_mesh2pcd.cpp
	> Author: yifei wang
	> Mail: 329585095@qq.com
	> Created Time: 2021/11/15 20:53
 ************************************************************************/

#include <iostream>
#include <assert.h>
#include <vector>
#include <math.h>
#include <string>

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
// #include "eigen.h"

using namespace std;

class PCDPublisher
{

public:

    PCDPublisher()
    {

        pub_ = n_.advertise<sensor_msgs::PointCloud2>("/cam/robotarm", 1);

        // load PLY into PCD

        string addressfile = "/home/ias/Desktop/thesis/code/ros_camera/src/darias_intelcamera/mesh/arm/pointcloud/arm_segment_last_convex.ply";

        if (pcl::io::loadPLYFile<pcl::PointXYZ>(addressfile, *pcd_arm_) == -1)
        {
            PCL_ERROR("Couldn't read file1 \n");
        }

        // tf_listener lookup files

        tfListener_ = new tf2_ros::TransformListener(tfBuffer_);
    }

    // void pointcloudPub()
    // {
    //     try
    //     {
    //         geometry_msgs::TransformStamped tf_r6link;

    //         tf_r6link = tfBuffer_.lookupTransform("world", "R_6_link", ros::Time(0), ros::Duration(3.0));

    //         // tf to eigen
    //         Eigen::Matrix4f link2world;

    //         pcl_ros::transformAsMatrix(tf_r6link.transform, link2world);

    //         // pcd to world frame

    //         pcl::transformPointCloud(*pcd_arm_, *pcd_arm_world_, link2world);

    //         // pcd to pcdMsgs

    //         sensor_msgs::PointCloud2 pcdMsg;

    //         pcl::toROSMsg(*pcd_arm_world_, pcdMsg);

    //         pcdMsg.header.frame_id = "world";

    //         // publish pcd

    //         pub_.publish(pcdMsg);
    //     }
    //     catch (tf2::TransformException &ex)
    //     {
    //         ROS_WARN("%s", ex.what());
    //     }
    // }

private:
    ros::NodeHandle n_;

    ros::Publisher pub_;

    ros::Subscriber sub_;

    tf2_ros::Buffer tfBuffer_;

    tf2_ros::TransformListener *tfListener_;

    pcl::PointCloud<pcl::PointXYZ> *pcd_arm_;
    pcl::PointCloud<pcl::PointXYZ> *pcd_arm_world_;
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "pcl_example");

    PCDPublisher pcd_pub;

    ros::Rate loop_rate(1);

    while (ros::ok())
    {
        // pcd_pub.pointcloudPub();
        loop_rate.sleep();
    }
    return 0;
}
