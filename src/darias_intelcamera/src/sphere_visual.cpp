#include <iostream>
#include <vector>

//ros
#include <ros/ros.h>
#include <math.h>
//msg
#include <visualization_msgs/Marker.h>

using namespace std;

class SphereMarker
{

public:
    SphereMarker()
    {
        pub_marker_ = n_.advertise<visualization_msgs::Marker>("test/marker", 10);

        shape_ = visualization_msgs::Marker::SPHERE;

        count_=0;

        markerMsg_ = new visualization_msgs::Marker;

        markerMsgInit();
    }

    void markerMsgInit()
    {
        markerMsg_->header.frame_id = "darias";
        markerMsg_->header.stamp = ros::Time::now();

        // Set the namespace and id for this markerMsg_->  This serves to create a unique ID
        // Any marker sent with the same namespace and id will overwrite the old one
        markerMsg_->ns = "basic_shapes";
        markerMsg_->id = 0;

        // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
        markerMsg_->type = shape_;

        // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
        markerMsg_->action = visualization_msgs::Marker::ADD;

        // Set the pose of the markerMsg_->  This is a full 6DOF pose relative to the frame/time specified in the header
        markerMsg_->pose.position.x = 0;
        markerMsg_->pose.position.y = 0;
        markerMsg_->pose.position.z = 0;
        markerMsg_->pose.orientation.x = 0.0;
        markerMsg_->pose.orientation.y = 0.0;
        markerMsg_->pose.orientation.z = 0.0;
        markerMsg_->pose.orientation.w = 1.0;

        // Set the scale of the marker -- 1x1x1 here means 1m on a side
        markerMsg_->scale.x = 0.2;
        markerMsg_->scale.y = 0.2;
        markerMsg_->scale.z = 0.2;

        // Set the color -- be sure to set alpha to something non-zero!
        markerMsg_->color.r = 0.0f;
        markerMsg_->color.g = 1.0f;
        markerMsg_->color.b = 0.0f;
        markerMsg_->color.a = 1.0;

        markerMsg_->lifetime = ros::Duration();
    }

    void markerMsgUpdate(){

        if (count_ == 64){

            count_ = 0;
        }

        markerMsg_->pose.position.x = cos(count_ * M_PI_64);
        markerMsg_->pose.position.y = sin(count_ * M_PI_64);

        ++count_;

    }

    void markerPublish(){

        pub_marker_.publish(*markerMsg_);
    }

    private:

    ros::NodeHandle n_;
    ros::Publisher pub_marker_;
    ros::Subscriber sub_joystick_;
    uint32_t shape_;
    visualization_msgs::Marker* markerMsg_;
    uint16_t count_;
    const double M_PI_64 = M_PI/64.;
    
    };

int main(int argc, char **argv)
{

    ros::init(argc, argv, "rviz_marker");

    SphereMarker Sphere;

    ros::Rate loop_rate = 10;

    while (ros::ok())
    {   
        Sphere.markerMsgUpdate();
        Sphere.markerPublish();

        ros::spinOnce();

        loop_rate.sleep();
    }
    return 0;
}
