/*************************************************************************
	> File Name: src/camera2oct.cpp
	> Author: yifei wang
	> Mail: 329585095@qq.com
	> Created Time: 2021/11/15 20:53
 ************************************************************************/

#include <iostream>
#include <assert.h>
#include <vector>

//ros
#include <ros/ros.h>

//pcl
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>

//octomap 
#include <octomap/octomap.h>
#include <octomap_msgs/Octomap.h>
#include <octomap_msgs/conversions.h>

//tf2
#include <tf2_ros/transform_listener.h>

//msgs
#include "darias_intelcamera/maplist.h"

using namespace std;

int main (int argc, char **argv)
{
    ros::init (argc, argv, "octomap_publisher");

    ros::NodeHandle nh("oct_pub");

    ros::Publisher oct_publiser;

    pcl::PointCloud<pcl::PointXYZ> cloud;

    string addressfile = "/home/ias/Desktop/map_test1/data/obsCombination.ply";
    
    pcl::io::loadPLYFile<pcl::PointXYZ> ( addressfile, cloud );

    // ROS::INFO("Loading file");

    //声明octomap变量
    // cout<<"copy data into octomap..."<<endl;
    // 创建八叉树对象，参数为分辨率，这里设成了0.05

    // double octomap_res = stod(argv[0]);

    octomap::OcTree tree( 0.05 );

    for (auto p:cloud.points)
    {
        // 将点云里的点插入到octomap中
        tree.updateNode( octomap::point3d(p.x, p.y, p.z), true );
    }

    // 更新octomap
    tree.updateInnerOccupancy();
    
    // 存储octomap

    int count = 0;
    
    for (auto iter = tree.begin(11), end = tree.end(); iter!= end;++iter){
        ++ count;
    }

    ROS_INFO("total cubes : %d",count);

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud2(new pcl::PointCloud<pcl::PointXYZ>);

    cloud2->height = count;
    cloud2->width = 1;

    cloud2->resize(cloud2->height * cloud2->width);

    size_t i = 0;

    for(auto iter = tree.begin(11), end = tree.end(); iter != end ;++iter){
        cloud2->points[i].x=iter.getX();
        cloud2->points[i].y=iter.getY();
        cloud2->points[i].z=iter.getZ();

        ++i;

    }

    ros::Publisher pcd2_publisher;
    sensor_msgs::PointCloud2 pcdMsg2;
    pcl::toROSMsg(*cloud2, pcdMsg2);
    pcdMsg2.header.frame_id="map";

    pcd2_publisher = nh.advertise<sensor_msgs::PointCloud2>("converted_cloud",1);

    


    octomap_msgs::Octomap octomapMsg;
    octomap_msgs::fullMapToMsg(tree, octomapMsg);
    octomapMsg.header.frame_id="map";


    oct_publiser=nh.advertise<octomap_msgs::Octomap>("oct_pub",1);
    
    ros::Rate loop_rate(1);
    while (ros::ok())
    {
        // ROS_INFO_STREAM ("address " << addressfile);
        // octomapMsg.header.stamp=stamp
        oct_publiser.publish(octomapMsg);
        pcd2_publisher.publish(pcdMsg2);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}



using namespace std;


class StateProcess{
public:

  tf2_ros::Buffer tfBuffer_;
  tf2_ros::TransformListener *tfListener_;

  StateProcess()
  { 

    // tf2 listener
    tfListener_ = new tf2_ros::TransformListener(tfBuffer_);

    pub_octomap = n_.advertise<octomap_msgs::Octomap>("/camera/octomap", 1);

    pub_octomap_list = n_.advertise<darias_intelcamera::maplist>("/camera/octomap_list", 1);

    sub_ = n_.subscribe("/camera/depth/color/points", 1, &StateProcess::callback, this);
  }
 
  void callback(const sensor_msgs::PointCloud2::ConstPtr &msgs)
  {
    
    darias_intelcamera::maplist pub_msg;
    


    for (decltype(msgs->name.size()) i=0; i <7;++i ){
      joint_l[i] = msgs->name[i+7];
      joint_r[i] = msgs->name[i];
    }

    //joint values


    for (decltype(msgs->position.size()) i=0; i <7;++i ){
      joint_l_v[i] = msgs->position[i+7];
      joint_r_v[i] = msgs->position[i];
    }

    // geometry_msgs::TransformStamped r_eef_world;
    // geometry_msgs::TransformStamped l_eef_world;

    // try{
    //   r_eef_world = tfBuffer_.lookupTransform("world", "right_endeffector_link",
    //                             ros::Time(0),ros::Duration(3.0));
    //   l_eef_world = tfBuffer_.lookupTransform("world", "left_endeffector_link",
    //                     ros::Time(0),ros::Duration(3.0));

    
    // }
    // catch (tf2::TransformException &ex) {
    //   ROS_WARN("%s",ex.what());    }

    

  }
 
private:
  ros::NodeHandle n_; 
  ros::Publisher pub_octomap;
  ros::Publisher pub_octomap_list;
  ros::Subscriber sub_;
 
};

int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "subscribe_and_publish");
 
  //Create an object of class SubscribeAndPublish that will take care of everything
  StateProcess SAPObject;
 
  ros::spin();
 
  return 0;
}