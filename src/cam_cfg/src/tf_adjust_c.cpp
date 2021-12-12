#include "ros/ros.h"

#include <dynamic_reconfigure/server.h>
#include <cam_cfg/tf_adjustConfig.h>

#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>

class TF_DynamicAdjust
{
public:

    void callback(cam_cfg::tf_adjustConfig &config, uint32_t level)
    
    {

        ROS_INFO("changed!");
        transform_.transform.translation.x = config.x;
        transform_.transform.translation.y = config.y;
        transform_.transform.translation.z = config.z;

        tf2::Quaternion q;
        q.setRPY(config.R,config.P,config.Y);

        transform_.transform.rotation.x = q.x();
        transform_.transform.rotation.y = q.y();
        transform_.transform.rotation.z = q.z();
        transform_.transform.rotation.w = q.w();
        
    }
    TF_DynamicAdjust()
    {
        f_ = boost::bind(&TF_DynamicAdjust::callback,this, _1, _2);
        server_.setCallback(f_);

        transform_.header.frame_id = "darias";
        transform_.child_frame_id = "camera_link";
    }

    void tf_update(){

        transform_.header.stamp = ros::Time::now();

        br_.sendTransform(transform_);
    }
    // ros::Publisher tf_publisher;

    dynamic_reconfigure::Server<cam_cfg::tf_adjustConfig> server_;
    dynamic_reconfigure::Server<cam_cfg::tf_adjustConfig>::CallbackType f_;

    tf2_ros::TransformBroadcaster br_;
    geometry_msgs::TransformStamped transform_;
};

int main(int argc, char **argv)

{
    ros::init(argc, argv, "node_dynamic_reconfigure");

    ros::NodeHandle n_;

    ros::Rate loop_rate(10);

    TF_DynamicAdjust tf_;


    while (ros::ok()){

        ros::spinOnce();
        tf_.tf_update();
        
        loop_rate.sleep();

    }

}
