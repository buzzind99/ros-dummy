#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

int main(int argc, char **argv)
{
  //ROS
  ros::init(argc, argv, "CV");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
  ros::Rate loop_rate(10);
  int count = 0;
  //OPENCV
  cv::VideoCapture cap(0);
  cv::Mat src_gray;
  cv::namedWindow("circle", 1);
  while (ros::ok())
  {
    cv::Mat src;
    cap >> src;
    cv::cvtColor( src, src_gray, CV_BGR2GRAY );
    cv::GaussianBlur( src_gray, src_gray, cv::Size(9, 9), 2, 2 );
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8, 200, 100, 0, 0 );
		  for( size_t i = 0; i < circles.size(); i++ )
		  {
		      cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		      int radius = cvRound(circles[i][2]);
		      // circle center
		      cv::circle( src, center, 3, cv::Scalar(0,255,0), -1, 8, 0 );
		      // circle outline
		      cv::circle( src, center, radius, cv::Scalar(0,0,255), 3, 8, 0 );
		      std_msgs::String msg;
		      std::stringstream ss;
		      ss << "-- Messages -- Circles detected #" << i+1;
		      msg.data = ss.str();
		      ROS_INFO("%s", msg.data.c_str());
		      chatter_pub.publish(msg);
		      ros::spinOnce();
		      loop_rate.sleep();
		      ++count;
		   }
	cv::imshow( "Circle detectionh", src );
	if(cv::waitKey(30) >= 0);
  }
  return 0;
}
