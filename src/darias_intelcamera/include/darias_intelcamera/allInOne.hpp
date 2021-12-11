#ifndef ALLINONE
#define ALLINONE
#endif

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

class TimeProfiler{
    private:

    ros::WallTime tic_;
    ros::WallTime toc_;

    public:
    TimeProfiler() = default;

    void begin();
    void stop(int);

};

class MapGeneration
{
    private:

    ros::NodeHandle n_;

    //publisher
    ros::Publisher pub_pcdvoxel_camera_;

    ros::Publisher pub_pcd_arm_right_;
    ros::Publisher pub_pcd_arm_left_;

    ros::Publisher pub_octmap_;
    ros::Publisher pub_pcdmap_;
    ros::Publisher pub_array3d_;

    //subscriber
    ros::Subscriber sub_pcd_camera_;
    
    // tf listener
    tf2_ros::Buffer tfBuffer_cam_;
    tf2_ros::TransformListener *tfListener_cam_;

    tf2_ros::Buffer tfBuffer_link_;
    tf2_ros::TransformListener *tfListener_link_;

    // pcd
    std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr> pcd_rightarm_;
    std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr> pcd_rightarm_world_;

    pcl::PointCloud<pcl::PointXYZ>::Ptr init_ptr_;

    //mesh path string
    std::vector<std::string> rightarm_meshefile_ = std::vector<std::string>(6);
    std::vector<std::string> leftarm_meshefile_ = std::vector<std::string>(6);

    // filesystem
    boost::filesystem::path cpppath_;
    boost::filesystem::path pkgfolder_;
    boost::filesystem::path meshfolder_;

    //others
    int pub_freq = 30;
    
    TimeProfiler timeprofiler_;

    bool isfinished_camera = false;
    bool isfinished_meshes = false;
    bool isfinished_octomap = false;
    bool isfinished_pcdmap = false;
    bool isfinished_3darry = false;
    bool enable_octomap = true;


    public:

    MapGeneration();
    void CallBack(const sensor_msgs::PointCloud2::ConstPtr &msgs );
};


