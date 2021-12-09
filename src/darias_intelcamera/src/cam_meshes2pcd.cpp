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

//pcl filter
#include <pcl/filters/voxel_grid.h>
#include<pcl/filters/passthrough.h>  
#include<pcl/filters/voxel_grid.h>  

//ros msg
#include <sensor_msgs/PointCloud2.h>
#include <geometry_msgs/Transform.h>
#include <geometry_msgs/Quaternion.h>


//tf2
#include <tf2_ros/transform_listener.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

//boost
#include <boost/filesystem.hpp>

//msgs
// #include "eigen.h"

using namespace std;

namespace fs = boost::filesystem;

class MeshPCDPub
{

public:
    MeshPCDPub()
    {  
        cppPath = fs::path(__FILE__);
        pkgFolder = cppPath.parent_path().parent_path();
        meshFolder_ = pkgFolder / "mesh/arm/pointcloud/";

        string meshFolder = meshFolder_.string();

        // define ply pointcloud file location
        rightArm_mesheFile[0] = meshFolder+"R_1_link.ply";
        rightArm_mesheFile[1] = meshFolder+"R_2_link.ply";
        rightArm_mesheFile[2] = meshFolder+"R_3_link.ply";
        rightArm_mesheFile[3] = meshFolder+"R_4_link.ply";
        rightArm_mesheFile[4] = meshFolder+"R_5_link.ply";
        rightArm_mesheFile[5] = meshFolder+"R_6_link.ply";


        // initialise  pointcloud pointer 
        for (size_t i = 0; i < 6; ++i)
        {   
            cout<<i<<endl;
            init_ptr.reset(new pcl::PointCloud<pcl::PointXYZ>);
            pcd_rightarm_.push_back(init_ptr);
            cout<<i<<endl;
        }

        for (size_t i = 0; i < 6; ++i)
        {   
            cout<<i<<endl;
            init_ptr.reset(new pcl::PointCloud<pcl::PointXYZ>);
            pcd_rightarm_world_.push_back(init_ptr);
            cout<<i<<endl;
        }
        // convert PLY into PCD

        for (size_t i = 0; i < 6; ++i){

            pcl::io::loadPLYFile<pcl::PointXYZ>(rightArm_mesheFile[i], *pcd_rightarm_[i]);

            cout<<pcd_rightarm_[i]->size()<<endl;
        }
        //publisher initialization

        pub_rightArm_ = n_.advertise<sensor_msgs::PointCloud2>("/camera_visual/mesh/rightArm", 1);

        //tf_listener initialization
        tfListener_ = new tf2_ros::TransformListener(tfBuffer_);
    }

    void armCompentTransfer(int link_idx){
        try
        {

            string link_name = string("R_")+to_string(link_idx) +string("_link");

            cout<<link_name<<endl;

            geometry_msgs::TransformStamped tf_link;

            tf_link = tfBuffer_.lookupTransform("world", link_name, ros::Time(0), ros::Duration(3.0));

            // tf to eigen
            Eigen::Matrix4f tf_in;

            pcl_ros::transformAsMatrix(tf_link.transform, tf_in);

            Eigen::Matrix4f tf_trans;

            Eigen::Matrix4f tf_out;

            tf_trans.setZero();

            for (int i = 0; i<4;++i){
                tf_trans(i,i)=1.0;
            }

            tf_trans(0,0) = -1.0;
            tf_trans(1,1) = -1.0;

            tf_out = tf_in * tf_trans;

            pcl::PointCloud<pcl::PointXYZ>::Ptr pcd_rightarm_world_tmp(new  pcl::PointCloud<pcl::PointXYZ>());

            pcl::transformPointCloud(*pcd_rightarm_[link_idx-1], *pcd_rightarm_world_tmp, tf_out);

            // voxel grid

            pcl::VoxelGrid<pcl::PointXYZ> voxel_grid;

            voxel_grid.setInputCloud (pcd_rightarm_world_tmp);

            voxel_grid.setLeafSize (0.02f, 0.02f, 0.02f);

            pcl::PointCloud<pcl::PointXYZ>::Ptr pcd_voxel(new pcl::PointCloud<pcl::PointXYZ>);

            voxel_grid.filter (*pcd_voxel);

            *pcd_rightarm_world_[link_idx-1] =  *pcd_voxel;

        }
        catch (tf2::TransformException &ex)
        {
            ROS_WARN("%s", ex.what());
        }


    }

    void armCompentJoin(){

        pcd_combined_ = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>);

        for(size_t i = 1 ; i <=5 ; ++i)
        {
            armCompentTransfer(i);

            ROS_INFO("No. %d link pointcloud is converted",char(i));
        }

        *pcd_combined_ = *pcd_rightarm_world_[0]+*pcd_rightarm_world_[1];
        *pcd_combined_ = *pcd_combined_+*pcd_rightarm_world_[2];
        *pcd_combined_ = *pcd_combined_+*pcd_rightarm_world_[3];
        *pcd_combined_ = *pcd_combined_+*pcd_rightarm_world_[4];
        *pcd_combined_ = *pcd_combined_+*pcd_rightarm_world_[5];
        // pointcloud message

        sensor_msgs::PointCloud2 pcdMsg;

        pcl::toROSMsg(*pcd_combined_, pcdMsg);
        pcdMsg.header.frame_id = "world";
        pub_rightArm_.publish(pcdMsg);

    }


private:
    ros::NodeHandle n_;

    ros::Publisher pub_rightArm_;
    ros::Publisher pub_leftArm_;

    tf2_ros::Buffer tfBuffer_;
    tf2_ros::TransformListener *tfListener_;

    vector<pcl::PointCloud<pcl::PointXYZ>::Ptr> pcd_rightarm_;
    vector<pcl::PointCloud<pcl::PointXYZ>::Ptr> pcd_rightarm_world_;


    pcl::PointCloud<pcl::PointXYZ>::Ptr pcd_combined_;

    pcl::PointCloud<pcl::PointXYZ>::Ptr init_ptr;


    vector<string> rightArm_mesheFile = vector<string>(6);
    vector<string> leftArm_mesheFile = vector<string>(6);

    fs::path cppPath;
    fs::path pkgFolder;
    fs::path meshFolder_;


    int pub_freq =30;

};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "pcl_example");

    MeshPCDPub pcd_pub;

    ros::Rate loop_rate(100);

    while (ros::ok())
    {
        pcd_pub.armCompentJoin();
        loop_rate.sleep();
    }
    return 0;
}

