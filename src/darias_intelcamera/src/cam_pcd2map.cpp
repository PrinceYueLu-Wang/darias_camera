/*************************************************************************
	> File Name: src/cam_pcd2map.cpp
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

//pcl kd_tree
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/kdtree/io.h>

//pcl filter
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/extract_indices.h>

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

class MapGeneration
{
public:
    MapGeneration() : pcd_cameraPcd(new pcl::PointCloud<pcl::PointXYZ>()), pcd_arm(new pcl::PointCloud<pcl::PointXYZ>()),pcd_cameraPcd_filtered(new pcl::PointCloud<pcl::PointXYZ>())
    {

        pub_octomap_filtered = n_.advertise<octomap_msgs::Octomap>("/camera_visual/filtered/octomap", 1);

        pub_pointcloud_filtered = n_.advertise<sensor_msgs::PointCloud2>("/camera_visual/filtered/pointcloud", 1);

        pub_array3d_filtered = n_.advertise<darias_intelcamera::maplist>("/camera_visual/filtered/point3d", 1);

        sub_pointcloud_all = n_.subscribe("/camera_visual/raw/pointcloud_voxel", 1, &MapGeneration::callback_cam, this);
        sub_pointcloud_arm = n_.subscribe("/camera_visual/mesh/rightArm", 1, &MapGeneration::callback_arm, this);
    }

    void callback_cam(const sensor_msgs::PointCloud2::ConstPtr &msgs)
    {
        pcl::PCLPointCloud2 pcl_msgs;

        pcl_conversions::toPCL(*msgs, pcl_msgs);

        pcl::fromPCLPointCloud2(pcl_msgs, *pcd_cameraPcd);
    }

    void callback_arm(const sensor_msgs::PointCloud2::ConstPtr &msgs)
    {

        pcl::PCLPointCloud2 pcl_msgs;

        pcl_conversions::toPCL(*msgs, pcl_msgs);

        pcl::fromPCLPointCloud2(pcl_msgs, *pcd_arm);
    }

    void pointCloudCompare()
    {
        if((pcd_arm->size()!=0)&(pcd_cameraPcd->size()!=0)){
        // kd tree
        pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;
        kdtree.setInputCloud(pcd_arm); //在pcd_arm中进行索引

        int K = 1;                        
        vector<int> pointIdxNKNSearch(K);
        vector<float> pointNKNSquaredDistance(K);

        pcl::PointIndices::Ptr indices_overlap(new pcl::PointIndices());

        //camera_pointcloud 中的每一个点在 pcd_arm 中找到最近的一个对应点,分别输出对应点
        for (size_t i = 0; i < pcd_cameraPcd->size(); i++)
        {
            pcl::PointXYZ searchPoint;
            searchPoint.x = pcd_cameraPcd->points[i].x;
            searchPoint.y = pcd_cameraPcd->points[i].y;
            searchPoint.z = pcd_cameraPcd->points[i].z;
            if (kdtree.nearestKSearch(searchPoint, K, pointIdxNKNSearch, pointNKNSquaredDistance) > 0)
            {
                if (pointNKNSquaredDistance[0] < 0.01)
                { 
                    // distance < 0.05 treat as overlapped points
                    indices_overlap->indices.push_back(i);
                }
            }
        }

        //eliminate overlapped points in camera_pointcloud

        pcl::ExtractIndices<pcl::PointXYZ> extract;
        extract.setInputCloud(pcd_cameraPcd);
        extract.setIndices(indices_overlap);

        //when true extract points not in indices
        extract.setNegative(true);

        extract.filter(*pcd_cameraPcd_filtered);
        
        // pointcloud msgs

        sensor_msgs::PointCloud2 pcdMsg;
        pcl::toROSMsg(*pcd_cameraPcd_filtered, pcdMsg);
        pcdMsg.header.frame_id = "world";

        pub_pointcloud_filtered.publish(pcdMsg);

        //octomap filtered 
        
        double octree_res = 0.01;
        octomap::OcTree tree(octree_res);

        for (auto p : pcd_cameraPcd_filtered->points)
        {
            // insert cloud points into octree
            tree.updateNode(octomap::point3d(p.x, p.y, p.z), true);
        }

        tree.updateInnerOccupancy();

        //publish octree
        
        octomap_msgs::Octomap octomapMsg;
        octomap_msgs::fullMapToMsg(tree, octomapMsg);
        octomapMsg.header.frame_id = "world";
        
        pub_octomap_filtered.publish(octomapMsg);

        //self-defined msgs
        int tree_depth = 15;

        darias_intelcamera::maplist pointsMsg;
        
        pointsMsg.sphere_radius = octree_res*pow(2.0,16-tree_depth);

        int cube_num = 0;
        
        for (auto iter = tree.begin(15), end = tree.end(); iter != end; ++iter)
        {
        pointsMsg.center_x.push_back(iter.getX());
        pointsMsg.center_y.push_back(iter.getY());
        pointsMsg.center_z.push_back(iter.getZ());

        ++cube_num;
        }

        pointsMsg.cube_number =cube_num;

        pub_array3d_filtered.publish(pointsMsg);

        }

    }

private:
    ros::NodeHandle n_;

    ros::Publisher pub_octomap_filtered;
    ros::Publisher pub_pointcloud_filtered;

    ros::Publisher pub_array3d_filtered;

    ros::Subscriber sub_pointcloud_all;
    ros::Subscriber sub_pointcloud_arm;

    pcl::PointCloud<pcl::PointXYZ>::Ptr pcd_cameraPcd;
    pcl::PointCloud<pcl::PointXYZ>::Ptr pcd_arm;
    pcl::PointCloud<pcl::PointXYZ>::Ptr pcd_cameraPcd_filtered;
};

int main(int argc, char **argv)
{
    //Initiate ROS
    ros::init(argc, argv, "subscribe_and_publish");

    MapGeneration map;

    ros::Rate loop_rate = 30;

    while (ros::ok())
    {

        ros::spinOnce();

        map.pointCloudCompare();
        
        loop_rate.sleep();
    }

    // ros::spin();

    return 0;
}