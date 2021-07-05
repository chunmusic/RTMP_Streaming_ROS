#include <iostream>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <std_msgs/String.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <cv_bridge/cv_bridge.h>

#include <image_transport/image_transport.h>
#include <image_transport/publisher.h>

int main(int argc, char **argv){

    ros::init(argc, argv, "rtmp_streaming");

    ros::NodeHandle nh();
    ros::NodeHandle pnh("~");

    

    std::string rtmp_address;
    pnh.getParam("rtmp_address", rtmp_address);

    image_transport::ImageTransport it;
    image_transport::Publisher pub;

    image_pub = it.advertise("/rtmp_streamping/raw",1)

    cv::Mat img;
    cv::VideoCapture cap;

    ROS_INFO("print");
    ROS_INFO("Got param: %s", rtmp_address.c_str());
    // cap.open(rtmp_address); //For rtmp streaming purpose.
    cap.open(0);

    while(cap.isOpened()){

        cap.read(img);
        cv::imshow("img",img);

        image_pub.publist(img);

        if(cv::waitKey(1) || ord('q')){
            break;
        }

    }

    cap.release();
    cv::destroyAllWindows();

}