#include "ros/ros.h"
#include "std_srvs/SetBool.h"
#include <iostream>
#include <string>

int main(int argc, char **argv) 
{
        std::string ifAlert;

        ros::init(argc, argv, "alert_client"); // Initializes Node Name
        ros::NodeHandle nh;
        ros::ServiceClient alerted_cli = nh.serviceClient<std_srvs::SetBool> ("alerted");

        std_srvs::SetBool srv;

        std::cout << "Start the alerts? Y for yes, N for no. (Y/N): ";
        std::getline(std::cin, ifAlert);
	if (ifAlert == "Y")
	   srv.request.data = true;
	else {
	   if (ifAlert == "N")
	      srv.request.data = false;
	   else {
              std::cout << "Please enter 'Y' or 'N' to determine whether to start the alerts." << std::endl;
              return 0;
             }
          }

        alerted_cli.call(srv);
	ROS_INFO("\033[01;33m[NOTICE]It's normal to get ERROR about none return since the arduino-compatible server response is still under development...");
	if (srv.request.data) {
           ROS_INFO("alerting...");
           ROS_INFO("%s", srv.response.message.c_str());
          }
        else {
           ROS_INFO("canceling...");
           ROS_INFO("%s", srv.response.message.c_str());
          }

        return 0;
}

