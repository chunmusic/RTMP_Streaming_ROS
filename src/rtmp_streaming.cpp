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

    ros::NodeHandle nh;
    ros::NodeHandle pnh("~");

    cv::Mat frame;
    sensor_msgs::ImagePtr msg;
    cv::VideoCapture cap;
    
    std::string rtmp_address;
    std::string publish_topic;
    int fps;

    pnh.getParam("rtmp_address", rtmp_address);
    pnh.getParam("publish_topic", publish_topic);
    pnh.getParam("fps", fps);

    image_transport::ImageTransport it(nh);
    image_transport::Publisher image_pub = it.advertise(publish_topic,1);

    cap.open(rtmp_address,cv::CAP_ANY);
    cap.set(cv::CAP_PROP_FPS,int(fps));

    if(!cap.isOpened()){
        std::cerr << "ERROR! Unable to open camera \n" << std::endl;
        return -1;
    }

    ros::Rate loop_rate(100);
    ROS_INFO("Start Streaming");

    while(cap.isOpened()){

        cap >> frame;

        if(!frame.empty()) {
            msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
            image_pub.publish(msg);
        }

        ros::spinOnce();
        loop_rate.sleep();
    }

    cap.release();
    cv::destroyAllWindows();

}