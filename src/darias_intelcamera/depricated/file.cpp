#include <ros/ros.h>

#include <iostream>

#include <string>

#include <boost/filesystem.hpp>

int main(int argc, char** argv)
{

    ros::init(argc, argv, "boostFilesystem");

    ros::NodeHandle n_;

    ros::Rate loop_rate = 1;
    
    boost::filesystem::path rootFolder = boost::filesystem::path(__FILE__);
    boost::filesystem::path pkgFolder = rootFolder.parent_path().parent_path();
    boost::filesystem::path meshFolder = pkgFolder / "mesh/arm/pointcloud/";
    boost::filesystem::path link = meshFolder / "R_1_link.ply";

    std::cout<<"rootFolder :  "<<rootFolder<<std::endl;
    std::cout<<"pkgFolder :  "<<pkgFolder<<std::endl;
    std::cout<<"meshfolder :  "<<meshFolder<<std::endl;
    std::cout<<"link :  "<<link<<std::endl;
    std::cout<<"link exist ? :  "<<boost::filesystem::exists(link)<<std::endl;

    std::string a = meshFolder.string();



    // while (ros::ok())
    // {

    //     ros::spinOnce();


    //     loop_rate.sleep();
    // }

    // ros::spin();


    return 0;
}
