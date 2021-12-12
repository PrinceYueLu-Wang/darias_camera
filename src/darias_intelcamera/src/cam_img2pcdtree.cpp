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

//pcl filter
#include <pcl/filters/voxel_grid.h>
#include<pcl/filters/passthrough.h> 
#include<pcl/filters/voxel_grid.h> 

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

        // pub_octomap = n_.advertise<octomap_msgs::Octomap>("/camera_visual/raw/octomap", 1);

        // pub_octomap_points = n_.advertise<darias_intelcamera::maplist>("/camera_visual/raw/point_list", 1);

        // pub_pcd = n_.advertise<sensor_msgs::PointCloud2>("/camera_visual/raw/pointcloud", 1);

        pub_pcd_voxel = n_.advertise<sensor_msgs::PointCloud2>("/camera_visual/raw/pointcloud_voxel", 1);

        sub_ = n_.subscribe("/camera/depth/color/points", 1, &StateProcess::callback, this);
    }

    void callback(const sensor_msgs::PointCloud2::ConstPtr &msgs)
    {   


        // ros::WallTime start_, end_;
        // double execution_time;

        // double execution_time = (end_ - start_).toNSec() * 1e-6;


        pcl::PCLPointCloud2 pointcloud_msg;

        // sensor::PointCloud2 msg -> pcl::PointCloud2 msg

        pcl_conversions::toPCL(*msgs, pointcloud_msg);

        pcl::PointCloud<pcl::PointXYZ>::Ptr pointcloud_raw(new pcl::PointCloud<pcl::PointXYZ>);

        // pcl::PointCloud2 msg -> pcl::pointcloud
        // pcl::fromPCLPointCloud2 (const pcl::PCLPointCloud2& msg, pcl::PointCloud

        pcl::fromPCLPointCloud2(pointcloud_msg, *pointcloud_raw);

        // pcl pointcloud transform

        // tf lookup reference frame : "world"  target frame : "camera_depth_optical_frame"

        geometry_msgs::TransformStamped tf_world2camera;

        pcl::VoxelGrid<pcl::PointXYZ> voxel_grid;

        voxel_grid.setInputCloud (pointcloud_raw);
        voxel_grid.setLeafSize (0.02f, 0.02f, 0.02f);

        pcl::PointCloud<pcl::PointXYZ>::Ptr pointcloud_raw_voxel(new pcl::PointCloud<pcl::PointXYZ>);
        voxel_grid.filter (*pointcloud_raw_voxel);

        try
        {   

            tf_world2camera = tfBuffer_.lookupTransform("world", "camera_depth_optical_frame", ros::Time(0), ros::Duration(3.0));

            Eigen::Matrix4f tf_eigen;

            pcl_ros::transformAsMatrix(tf_world2camera.transform, tf_eigen);


            pcl::PointCloud<pcl::PointXYZ>::Ptr pcd_voxel_raw_world(new pcl::PointCloud<pcl::PointXYZ>);

            pcl::transformPointCloud(*pointcloud_raw_voxel, *pcd_voxel_raw_world, tf_eigen);

            
            pcl::PointCloud<pcl::PointXYZ>::Ptr pcd_voxel_filtered_world(new pcl::PointCloud<pcl::PointXYZ>);
            pcl::PassThrough<pcl::PointXYZ> passthrough;  //设置滤波器对象
            passthrough.setInputCloud(pcd_voxel_raw_world);//输入点云
            passthrough.setFilterFieldName("z");//对z轴进行操作，也可以对"x"和"y"轴进行操作    
            passthrough.setFilterLimits(0.5, 3.0);//设置直通滤波器操作范围
            passthrough.setFilterLimitsNegative(false);//true表示保留范围内，false表示保留范围外
            passthrough.filter(*pcd_voxel_filtered_world);//执行滤波，过滤结果保存在 cloud_after_PassThrough



            sensor_msgs::PointCloud2 pcdMsg;

            pcl::toROSMsg(*pcd_voxel_filtered_world, pcdMsg);

            pcdMsg.header.frame_id = "world";


            pub_pcd_voxel.publish(pcdMsg);

        }
        catch (tf2::TransformException &ex)
        {
            ROS_WARN("%s", ex.what());
        }
    }

private:
    ros::NodeHandle n_;

    // ros::Publisher pub_octomap;
    // ros::Publisher pub_octomap_points;

    ros::Publisher pub_pcd_voxel;
    ros::Publisher pub_pcd;

    ros::Subscriber sub_;

    int pub_freq = 30;
};

int main(int argc, char **argv)
{
    //Initiate ROS
    ros::init(argc, argv, "subscribe_and_publish");

    //Create an object of class SubscribeAndPublish that will take care of everything
    StateProcess SAPObject;

    ros::Rate loop_rate = 30;

    while (ros::ok())
    {

        ros::spinOnce();

        loop_rate.sleep();
    }

    // ros::spin();

    return 0;
}