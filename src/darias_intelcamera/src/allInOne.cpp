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

#include "darias_intelcamera/allInOne.hpp"

using namespace std;

MapGeneration::MapGeneration (){

    tfListener_cam_ = new tf2_ros::TransformListener(tfBuffer_cam_);

    sub_pcd_camera_ = n_.subscribe("/camera/depth/color/points", 1, &MapGeneration::CallBack, this);
    pub_pcdvoxel_camera_ = n_.advertise<sensor_msgs::PointCloud2>("/camera_visual/raw/pointcloud_voxel_filtered", 1);


}

void MapGeneration::CallBack(const sensor_msgs::PointCloud2::ConstPtr &cam_msgs ){

        pcl::PCLPointCloud2 pointcloud_msg;
        // sensor::PointCloud2 msg -> pcl::PointCloud2 msg
        pcl_conversions::toPCL(*cam_msgs, pointcloud_msg);
        pcl::PointCloud<pcl::PointXYZ>::Ptr pointcloud_raw(new pcl::PointCloud<pcl::PointXYZ>);
        // pcl::PointCloud2 msg -> pcl::pointcloud
        // pcl::fromPCLPointCloud2 (const pcl::PCLPointCloud2& msg, pcl::PointCloud
        pcl::fromPCLPointCloud2(pointcloud_msg, *pointcloud_raw);
        // pcl pointcloud transform
        // tf lookup reference frame : "world"  target frame : "camera_depth_optical_frame"
        geometry_msgs::TransformStamped tf_world2camera;
        
        //grid voxel
        pcl::VoxelGrid<pcl::PointXYZ> voxel_grid;
        voxel_grid.setInputCloud (pointcloud_raw);
        voxel_grid.setLeafSize (0.02f, 0.02f, 0.02f);
        pcl::PointCloud<pcl::PointXYZ>::Ptr pcd_voxel_raw(new pcl::PointCloud<pcl::PointXYZ>);
        voxel_grid.filter (*pcd_voxel_raw);

        try
        {   

            tf_world2camera = tfBuffer_cam_.lookupTransform("world", "camera_depth_optical_frame", ros::Time(0), ros::Duration(3.0));

            Eigen::Matrix4f tf_eigen;
            pcl_ros::transformAsMatrix(tf_world2camera.transform, tf_eigen);
            // pcd to world frame
            pcl::PointCloud<pcl::PointXYZ>::Ptr pcd_voxel_world(new pcl::PointCloud<pcl::PointXYZ>);
            pcl::transformPointCloud(*pcd_voxel_raw, *pcd_voxel_world, tf_eigen);

            pcl::PointCloud<pcl::PointXYZ>::Ptr pcd_voxel_filtered(new pcl::PointCloud<pcl::PointXYZ>);
            pcl::PassThrough<pcl::PointXYZ> passthrough;  //设置滤波器对象
            passthrough.setInputCloud(pcd_voxel_world);//输入点云
            passthrough.setFilterFieldName("z");//对z轴进行操作，也可以对"x"和"y"轴进行操作    
            passthrough.setFilterLimits(0.5, 3.0);//设置直通滤波器操作范围
            passthrough.setFilterLimitsNegative(false);//true表示保留范围内，false表示保留范围外
            passthrough.filter(*pcd_voxel_filtered);//执行滤波，过滤结果保存在 cloud_after_PassThrough
    

            // sensor_msgs::PointCloud2 pcd_world_msg;
            // pcl::toROSMsg(*pcd_voxel_filtered, pcd_world_msg);
            // pcd_world_msg.header.frame_id = "world";
            // pub_pcdvoxel_camera_.publish(pcd_world_msg);

        }
        catch (tf2::TransformException &ex)
        {
            ROS_WARN("%s", ex.what());
        }
}


int main(int argc, char **argv){

    ros::init(argc, argv, "pcl_example");

    MapGeneration map;

    ros::Rate looprate(30);

    while(ros::ok()){

        ros::spinOnce();

        looprate.sleep();
        
    }



}

