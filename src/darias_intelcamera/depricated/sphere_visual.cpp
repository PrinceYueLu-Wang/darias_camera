#include <iostream>
#include <vector>

//ros
#include <ros/ros.h>
#include <math.h>
//msg
#include <visualization_msgs/Marker.h>
#include <darias_intelcamera/joystick.h>

using namespace std;

class JoyInput
{   
    public:
    JoyInput()
    {
        axis_x=0.0;

        axis_y=0.0;

        axis_z=0.0;

        scale = 0.05;
    }

    void joyInputUpdate(double x, double y,double z){
        
        axis_x = scale * x;
        axis_y = scale * y;
        axis_z = scale/5.0 * z;

    }

    double axis_x;
    double axis_y;
    double axis_z;

    double scale;



};

class SphereMarker
{

public:
    SphereMarker()
    {
        pub_marker_ = n_.advertise<visualization_msgs::Marker>("test/marker", 10);

        sub_joystick_ = n_.subscribe("/joystick/controller",1, &SphereMarker::joystickMsgCallback, this);

        shape_ = visualization_msgs::Marker::SPHERE;

        count_=0;

        markerMsg_ = new visualization_msgs::Marker;

        markerMsgInit();

        // joystick init

        joystick_ = new (JoyInput);

        joy_newInput_ = false;

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
        markerMsg_->scale.x = 0.05;
        markerMsg_->scale.y = 0.05;
        markerMsg_->scale.z = 0.05;

        // Set the color -- be sure to set alpha to something non-zero!
        markerMsg_->color.r = 0.0f;
        markerMsg_->color.g = 1.0f;
        markerMsg_->color.b = 0.0f;
        markerMsg_->color.a = 1.0;

        markerMsg_->lifetime = ros::Duration();
    }


    void markerMsgUpdate(string mode = "joystick"){
        
        if (joy_newInput_){
            markerMsg_->pose.position.x = markerMsg_->pose.position.x + joystick_->axis_x;
            markerMsg_->pose.position.y = markerMsg_->pose.position.y + joystick_->axis_y;
            markerMsg_->pose.position.z = markerMsg_->pose.position.z + joystick_->axis_z;
        }


        
    }

    void markerPublish(){

        pub_marker_.publish(*markerMsg_);
    }

    void joystickMsgCallback(const darias_intelcamera::joystick &joystick_msgs)
    {
        // here attetion!
        // joystick axis X == - rviz aixs Y
        joystick_->joyInputUpdate(-joystick_msgs.lh_axisY,joystick_msgs.lh_axisX,joystick_msgs.button_axisZ);

        joy_newInput_ = true;
    }

    private:

    ros::NodeHandle n_;

    ros::Publisher pub_marker_;
    ros::Subscriber sub_joystick_;

    uint32_t shape_;
    visualization_msgs::Marker* markerMsg_;
    uint16_t count_;
    
    const double M_PI_64 = M_PI/64.;

    JoyInput* joystick_;
    bool joy_newInput_;
    
    };

int main(int argc, char **argv)
{

    ros::init(argc, argv, "rviz_marker");

    SphereMarker Sphere;

    ros::Rate loop_rate = 10;

    while (ros::ok())

    
    {   
        ros::spinOnce();

        Sphere.markerMsgUpdate();
        Sphere.markerPublish();

        loop_rate.sleep();
    }
    return 0;
}
