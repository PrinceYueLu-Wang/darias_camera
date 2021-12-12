#include <vector>
#include <string>

//ros
#include <ros/ros.h>

//ros msg
#include <sensor_msgs/JointState.h>

using namespace std;

int main(int argc,char ** argv){

    ros::init(argc, argv,"joint_states");

    ros::NodeHandle n_;


    ros::Publisher pub_=n_.advertise<sensor_msgs::JointState>("joint_states",10);

    sensor_msgs::JointState joint_msg;

    

    vector<string> joint_name =  {"L_SFE","L_SAA","L_HR","L_EB","L_WR","L_WFE","L_WAA",
                                  "L_THS","L_THP","L_THD",
                                  "L_INS","L_INP","L_IND",
                                  "L_MIS","L_MIP","L_MID",
                                  "L_RIS","L_RIP","L_RID",
                                  "L_SMS","L_SMP","L_SMD",
                                  "R_SFE","R_SAA","R_HR","R_EB","R_WR","R_WFE","R_WAA",
                                  "R_THS","R_THP","R_THD",
                                  "R_INS","R_INP","R_IND",
                                  "R_MIS","R_MIP","R_MID",
                                  "R_RIS","R_RIP","R_RID",
                                  "R_SMS","R_SMP","R_SMD"};

    vector<double> position = {0.30000001192092896, -0.8999999761581421, -2.0, 1.399999976158142, -2.0, 0.5, -1.0, 0.0, 0.08699999749660492, 0.08699999749660492, 0.0, 0.08699999749660492, 0.08699999749660492, 0.0, 0.08699999749660492, 0.08699999749660492, 0.0, 0.08699999749660492, 0.08699999749660492, 0.0, 0.08699999749660492, 0.08699999749660492, 1.1012223958969116, 1.4643657207489014, 0.7061947584152222, -1.1087623834609985, 2.1497199535369873, -0.487669438123703, 0.9996455311775208, 0.0, 0.08699999749660492, 0.08699999749660492, 0.0, 0.08699999749660492, 0.08699999749660492, 0.0, 0.08699999749660492, 0.08699999749660492, 0.0, 0.08699999749660492, 0.08699999749660492, 0.0, 0.08699999749660492, 0.08699999749660492};
    vector<double> velocity(44,0.0);
    vector<double> effort={};

    joint_msg.position = position;
    joint_msg.velocity = velocity;
    joint_msg.name = joint_name;

    ROS_INFO("%zu",position.size());
    ROS_INFO("%zu",velocity.size());

    ros::Rate loop_rate(10);


    while(ros::ok()){

        joint_msg.header.stamp = ros::Time::now();

        pub_.publish(joint_msg);

        loop_rate.sleep();
    }

    return 0;

}