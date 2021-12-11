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

#include "darias_intelcamera/allInOne.hpp"

using namespace std;

void TimeProfiler::begin(){
    tic_ = ros::WallTime::now();
};
void TimeProfiler::stop(int index){
    toc_= ros::WallTime::now();
    auto execution_time = (toc_ - tic_).toSec() * 1e3;
    ROS_INFO_STREAM("No."<<index<<" block with time (ms): " << execution_time);
    TimeProfiler::begin();
};


MapGeneration::MapGeneration (){

    tfListener_cam_ = new tf2_ros::TransformListener(tfBuffer_cam_);
    tfListener_link_ = new tf2_ros::TransformListener(tfBuffer_link_);

    sub_pcd_camera_ = n_.subscribe("/camera/depth/color/points", 1, &MapGeneration::CallBack, this);
    
    pub_pcdvoxel_camera_ = n_.advertise<sensor_msgs::PointCloud2>("/camera_visual/raw/pointcloud_voxel_filtered", 1);
    pub_pcd_arm_right_ = n_.advertise<sensor_msgs::PointCloud2>("/camera_visual/mesh/pointcloud_rightArm", 1);
    
    pub_pcdmap_ = n_.advertise<sensor_msgs::PointCloud2>("/camera_visual/filtered/pointcloud", 1);
    pub_octmap_ = n_.advertise<octomap_msgs::Octomap>("/camera_visual/filtered/octomap", 1);
    pub_array3d_ = n_.advertise<darias_intelcamera::maplist>("/camera_visual/filtered/point3d", 1);

    pub_palm_ = n_.advertise<sensor_msgs::PointCloud2>("/camera_visual/mesh/palm", 1);

    //filesystem
    cpppath_ = boost::filesystem::path(__FILE__);
    pkgfolder_ = cpppath_.parent_path().parent_path();
    meshfolder_ = pkgfolder_ / "mesh/arm/pointcloud/";

    string meshfolder = meshfolder_.string();

    // define ply pointcloud file location
    rightarm_meshefile_.push_back(meshfolder+"R_1_link.ply");
    rightarm_meshefile_.push_back(meshfolder+"R_2_link.ply");
    rightarm_meshefile_.push_back(meshfolder+"R_3_link.ply");
    rightarm_meshefile_.push_back(meshfolder+"R_4_link.ply");
    rightarm_meshefile_.push_back(meshfolder+"R_5_link.ply");
    rightarm_meshefile_.push_back(meshfolder+"R_6_link.ply");
    rightarm_meshefile_.push_back(meshfolder+"righthandbase.ply");

    rightarm_linknum_ = rightarm_meshefile_.size();


    // initialise  pointcloud pointer 
    for (int i = 0; i < rightarm_linknum_; ++i)
    {   
        init_ptr_.reset(new pcl::PointCloud<pcl::PointXYZ>);
        pcd_rightarm_.push_back(init_ptr_);
    }

    for (int i = 0; i < rightarm_linknum_; ++i)
    {   
        init_ptr_.reset(new pcl::PointCloud<pcl::PointXYZ>);
        pcd_rightarm_world_.push_back(init_ptr_);
    }
    // convert PLY into PCD

    for (int i = 0; i < rightarm_linknum_; ++i){

        pcl::io::loadPLYFile<pcl::PointXYZ>(rightarm_meshefile_[i], *pcd_rightarm_[i]);

        cout<<pcd_rightarm_[i]->size()<<endl;

        cout<<rightarm_meshefile_[i]<< "done!"<<endl;

    }

}

void MapGeneration::CallBack(const sensor_msgs::PointCloud2::ConstPtr &cam_msgs ){

        timeprofiler_.begin();
        // sensor::PointCloud2 msg -> pcl::PointCloud2 msg
        // pcl::PointCloud2 msg -> pcl::pointcloud
        // pcl::fromPCLPointCloud2 (const pcl::PCLPointCloud2& msg, pcl::PointCloud

        // pcl::PCLPointCloud2 pointcloud_msg;
        // pcl_conversions::toPCL(*cam_msgs, pointcloud_msg);
        // pcl::PointCloud<pcl::PointXYZ>::Ptr pointcloud_raw(new pcl::PointCloud<pcl::PointXYZ>);
        // pcl::fromPCLPointCloud2(pointcloud_msg, *pointcloud_raw);

        pcl::PointCloud<pcl::PointXYZ>::Ptr pointcloud_raw(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::fromROSMsg(*cam_msgs, *pointcloud_raw);


        //grid voxel
        pcl::VoxelGrid<pcl::PointXYZ> voxel_grid;
        voxel_grid.setInputCloud (pointcloud_raw);
        voxel_grid.setLeafSize (0.02f, 0.02f, 0.02f);
        pcl::PointCloud<pcl::PointXYZ>::Ptr pcd_voxel_raw(new pcl::PointCloud<pcl::PointXYZ>);
        voxel_grid.filter (*pcd_voxel_raw);

        isfinished_camera = false;
        isfinished_meshes = false;

        pcl::PointCloud<pcl::PointXYZ>::Ptr pcd_voxel_filtered(new pcl::PointCloud<pcl::PointXYZ>);

        try{   

            geometry_msgs::TransformStamped tf_world2camera;

            tf_world2camera = tfBuffer_cam_.lookupTransform("world", "camera_depth_optical_frame", ros::Time(0), ros::Duration(3.0));
            Eigen::Matrix4f tf_eigen;
            pcl_ros::transformAsMatrix(tf_world2camera.transform, tf_eigen);
            // pcd to world frame
            pcl::PointCloud<pcl::PointXYZ>::Ptr pcd_voxel_world(new pcl::PointCloud<pcl::PointXYZ>);
            pcl::transformPointCloud(*pcd_voxel_raw, *pcd_voxel_world, tf_eigen);

            pcl::PassThrough<pcl::PointXYZ> passthrough;  //设置滤波器对象
            passthrough.setInputCloud(pcd_voxel_world);//输入点云
            passthrough.setFilterFieldName("z");//对z轴进行操作，也可以对"x"和"y"轴进行操作    
            passthrough.setFilterLimits(0.5, 3.0);//设置直通滤波器操作范围
            passthrough.setFilterLimitsNegative(false);//true表示保留范围内，false表示保留范围外
            passthrough.filter(*pcd_voxel_filtered);//执行滤波，过滤结果保存在 cloud_after_PassThrough            

            isfinished_camera = true;
        }
        catch (tf2::TransformException &ex)
        {
            ROS_WARN("%s", ex.what());
        }

        // mesh pointclouds

        int countflag_armlink = 0;

        for(size_t i = 1 ; i <=rightarm_linknum_ ; ++i)
        {   
            string link_name;
            if (i<=6){
                link_name = string("R_")+to_string(i) +string("_link");
            }else{
                link_name = "R_palm";
            }


            geometry_msgs::TransformStamped tf_link;
            try{
            tf_link = tfBuffer_link_.lookupTransform("world", link_name, ros::Time(0), ros::Duration(3.0));
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

            pcl::PointCloud<pcl::PointXYZ>::Ptr pcd_link_world_tmp(new  pcl::PointCloud<pcl::PointXYZ>());
            pcl::transformPointCloud(*pcd_rightarm_[i-1], *pcd_link_world_tmp, tf_out);

            // voxel grid
            pcl::VoxelGrid<pcl::PointXYZ> voxel_grid;
            voxel_grid.setInputCloud (pcd_link_world_tmp);
            voxel_grid.setLeafSize (0.02f, 0.02f, 0.02f);
            pcl::PointCloud<pcl::PointXYZ>::Ptr pcd_link_voxel_world(new pcl::PointCloud<pcl::PointXYZ>);
            voxel_grid.filter (*pcd_link_voxel_world);
            *pcd_rightarm_world_[i-1] =  *pcd_link_voxel_world;

            if(i == 7){
                sensor_msgs::PointCloud2::Ptr msg_palm(new sensor_msgs::PointCloud2);
                pcl::toROSMsg(*pcd_link_world_tmp, *msg_palm);
                msg_palm->header.frame_id = "world";
                pub_palm_.publish(*msg_palm);
            }

            ++countflag_armlink;
            }
            catch (tf2::TransformException &ex){
                ROS_WARN("%s", ex.what());
            }
        }

        pcl::PointCloud<pcl::PointXYZ>::Ptr pcd_linkcombined(new pcl::PointCloud<pcl::PointXYZ>);
        if (countflag_armlink == rightarm_linknum_){             
            isfinished_meshes = true;

            for (int i = 0; i< rightarm_linknum_; ++i){
                *pcd_linkcombined = *pcd_linkcombined+*pcd_rightarm_world_[i];
            }
        }


        if (isfinished_camera && isfinished_meshes){
            if((pcd_voxel_filtered->size()!=0)&(pcd_linkcombined->size()!=0)){
            
                pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;
                kdtree.setInputCloud(pcd_linkcombined); //在pcd_arm中进行索引

                int K = 1;                        
                vector<int> pointIdxNKNSearch(K);
                vector<float> pointNKNSquaredDistance(K);

                pcl::PointIndices::Ptr indices_overlap(new pcl::PointIndices());

                //camera_pointcloud 中的每一个点在 pcd_arm 中找到最近的一个对应点,分别输出对应点
                for (size_t i = 0; i < pcd_voxel_filtered->size(); i++)
                {
                    pcl::PointXYZ searchPoint;
                    searchPoint.x = pcd_voxel_filtered->points[i].x;
                    searchPoint.y = pcd_voxel_filtered->points[i].y;
                    searchPoint.z = pcd_voxel_filtered->points[i].z;
                    if (kdtree.nearestKSearch(searchPoint, K, pointIdxNKNSearch, pointNKNSquaredDistance) > 0)
                    {
                        if (pointNKNSquaredDistance[0] < OVERLAP_DIST)
                        { 
                            // distance < 0.03 treat as overlapped points
                            indices_overlap->indices.push_back(i);
                        }
                    }
                }

                //eliminate overlapped points in camera_pointcloud
                pcl::PointCloud<pcl::PointXYZ>::Ptr pcd_final(new  pcl::PointCloud<pcl::PointXYZ>);
                pcl::ExtractIndices<pcl::PointXYZ> extract;
                extract.setInputCloud(pcd_voxel_filtered);
                extract.setIndices(indices_overlap);
                extract.setNegative(true);
                extract.filter(*pcd_final);

                //octomap filtered 

                double octree_res = 0.01;
                octomap::OcTree tree(octree_res);

                for (auto p : pcd_final->points)
                {
                    // insert cloud points into octree
                    tree.updateNode(octomap::point3d(p.x, p.y, p.z), true);
                }

                tree.updateInnerOccupancy();

                //publisher!!

                auto sendtime = ros::Time::now();

                sensor_msgs::PointCloud2::Ptr msg_pcdvoxel(new sensor_msgs::PointCloud2);
                pcl::toROSMsg(*pcd_voxel_filtered, *msg_pcdvoxel);
                msg_pcdvoxel->header.frame_id = "world";
                pub_pcdvoxel_camera_.publish(*msg_pcdvoxel);

                sensor_msgs::PointCloud2::Ptr msg_linkcombined(new sensor_msgs::PointCloud2);
                pcl::toROSMsg(*pcd_linkcombined, *msg_linkcombined);
                msg_linkcombined->header.frame_id = "world";
                pub_pcd_arm_right_.publish(*msg_linkcombined);

                sensor_msgs::PointCloud2::Ptr msg_pcdfinal(new sensor_msgs::PointCloud2);
                pcl::toROSMsg(*pcd_final, *msg_pcdfinal);
                msg_pcdfinal->header.frame_id = "world";
                pub_pcdmap_.publish(*msg_pcdfinal);


                
                octomap_msgs::Octomap msg_octomap;
                octomap_msgs::fullMapToMsg(tree, msg_octomap);
                msg_octomap.header.frame_id = "world";
                pub_octmap_.publish(msg_octomap);

                //self-defined msgs
                int tree_depth = 15;
                darias_intelcamera::maplist msg_3darray;
                msg_3darray.sphere_radius = octree_res*pow(2.0,16-tree_depth);
                int cube_num = 0;
                for (auto iter = tree.begin(15), end = tree.end(); iter != end; ++iter){
                msg_3darray.center_x.push_back(iter.getX());
                msg_3darray.center_y.push_back(iter.getY());
                msg_3darray.center_z.push_back(iter.getZ());
                ++cube_num;
                }

                msg_3darray.cube_number =cube_num;
                pub_array3d_.publish(msg_3darray);

                // timeprofiler_.stop(1);


                    }
                }



        




}


int main(int argc, char **argv){

    ros::init(argc, argv, "pcl_example");

    MapGeneration map;

    ros::Rate looprate(30);

    while(ros::ok()){

        ros::spinOnce();

        // looprate.sleep();
        
    }



}

