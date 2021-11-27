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
#include <geometry_msgs/Quaternion.h>

//octomap
#include <octomap/octomap.h>
#include <octomap_msgs/Octomap.h>
#include <octomap_msgs/conversions.h>

//tf2
#include <tf2_ros/transform_listener.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>



//msgs
// #include "eigen.h"

using namespace std;

class MeshPCDPub
{

public:
    MeshPCDPub()
    {
        pub_ = n_.advertise<sensor_msgs::PointCloud2>("/camera_visual/mesh_R_5_link", 1);


        pcd_arm_ = new pcl::PointCloud<pcl::PointXYZ>();
        pcd_arm_world_ = new pcl::PointCloud<pcl::PointXYZ>();

        // load PLY into PCD

        string addressfile = "/home/ias/Desktop/thesis/code/ros_camera/src/darias_intelcamera/mesh/arm/pointcloud/arm_segment_last_convex.ply";

        try
        {

            pcl::io::loadPLYFile<pcl::PointXYZ>(addressfile, *pcd_arm_);
        }
        catch (pcl::IOException &ex)
        {
            PCL_ERROR("Couldn't read file1 \n");
        }

        // tf_listener lookup files

        tfListener_ = new tf2_ros::TransformListener(tfBuffer_);
    }

    void pointcloudPub()
    {
        try
        {
            geometry_msgs::TransformStamped tf_r6link;

            tf_r6link = tfBuffer_.lookupTransform("world", "R_5_link", ros::Time(0), ros::Duration(3.0));

            // tf to eigen
            Eigen::Matrix4f tf_in;

            pcl_ros::transformAsMatrix(tf_r6link.transform, tf_in);

            Eigen::Matrix4f tf_trans1;

            Eigen::Matrix4f tf_trans2;

            Eigen::Matrix4f tf_out;

            tf_trans1.setZero();
            tf_trans2.setZero();
            
            for (int i = 0; i<4;++i){
                tf_trans1(i,i)=1.0;
            }
            
            tf_trans1(2,3) = 0.0;

            for (int i = 0; i<4;++i){
                tf_trans2(i,i)=1.0;
            }

            tf_trans2(0,0) = -1.0;
            tf_trans2(1,1) = -1.0;
            

            tf_out = tf_in * tf_trans2;
            



            // geometry_msgs::Quaternion q_raw = tf_r6link.transform.rotation;


            // tf2::Quaternion q_orig, q_rot, q_new;

            // tf2::convert(q_raw , q_orig);

            // q_rot.setRPY(0.0, 0.0, 3.14159);

            // q_new = q_orig*q_rot; 

            // q_new.normalize();

            // geometry_msgs::Quaternion q_new_msg;

            // tf2::convert(q_new , q_new_msg);

            // tf_r6link.transform.rotation = q_new_msg;
            // tf_r6link.transform.translation.z = tf_r6link.transform.translation.z+0.124;

            // pcl_ros::transformAsMatrix(tf_r6link.transform, link2world);

            // pcd to world frame

            pcl::transformPointCloud(*pcd_arm_, *pcd_arm_world_, tf_out);

            // pcd to pcdMsgs

            sensor_msgs::PointCloud2 pcdMsg;

            pcl::toROSMsg(*pcd_arm_world_, pcdMsg);

            pcdMsg.header.frame_id = "world";

            // publish pcd

            pub_.publish(pcdMsg);
        }
        catch (tf2::TransformException &ex)
        {
            ROS_WARN("%s", ex.what());
        }
    }

    void ArmCompentTransfer(){
        ;
    }

private:
    ros::NodeHandle n_;

    ros::Publisher pub_;

    tf2_ros::Buffer tfBuffer_;

    tf2_ros::TransformListener *tfListener_;

    pcl::PointCloud<pcl::PointXYZ> *pcd_arm_;
    pcl::PointCloud<pcl::PointXYZ> *pcd_arm_world_;
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "pcl_example");

    MeshPCDPub pcd_pub;

    ros::Rate loop_rate(1);

    while (ros::ok())
    {
        pcd_pub.pointcloudPub();
        loop_rate.sleep();
    }
    return 0;
}
