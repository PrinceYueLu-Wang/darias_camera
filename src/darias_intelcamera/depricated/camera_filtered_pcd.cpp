/*************************************************************************
	> File Name: src/camera_oct2pcd.cpp
	> Author: yifei wang
	> Mail: 329585095@qq.com
	> Created Time: 2021/11/15 20:53
 ************************************************************************/
//pinocchio
#include "pinocchio/parsers/urdf.hpp"
#include "pinocchio/algorithm/joint-configuration.hpp"
#include "pinocchio/algorithm/kinematics.hpp"

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
#include <sensor_msgs/JointState.h>

//octomap
#include <octomap/octomap.h>
#include <octomap_msgs/Octomap.h>
#include <octomap_msgs/conversions.h>

//tf2
#include <tf2_ros/transform_listener.h>
// #include <tf2_ros/static_transform_broadcaster.h>


//msgs
#include "darias_intelcamera/maplist.h"


class FilteredPCDPublisher
{

public:

    FilteredPCDPublisher()
    {

        sub_ = n_.subscribe("/camera/octomap_list", 1, &FilteredPCDPublisher::callback, this);

        pub_ = n_.advertise<sensor_msgs::PointCloud2>("/camera/pcd_converted", 1);
    }

    void callback(const darias_intelcamera::maplist &pointsMsg)
    {

        int points_num = pointsMsg.cube_number;

        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

        cloud->height = points_num;

        cloud->width = 1;

        cloud->resize(cloud->height * cloud->width);

        size_t j = 0;

        for (auto i = 0 ; i < points_num ; ++i)
        {
            
            cloud->points[i].x=pointsMsg.center_x[i];
            cloud->points[i].y=pointsMsg.center_y[i];
            cloud->points[i].z=pointsMsg.center_z[i];

        }

        sensor_msgs::PointCloud2 pcdMsg;
        pcl::toROSMsg(*cloud, pcdMsg);
        pcdMsg.header.frame_id="darias";

        pub_.publish(pcdMsg);

    }

private:
    ros::NodeHandle n_;
    ros::Publisher pub_;
    ros::Subscriber sub_;
};

int main (int argc, char **argv)
{
    ros::init (argc, argv, "pcl_example");

    FilteredPCDPublisher pcd_pub = FilteredPCDPublisher();

    ros::Rate loop_rate(1);


    while (ros::ok())
    {
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}

