#include "ros/ros.h"
#include "std_srvs/SetBool.h"
#include <iostream>
#include <string>

int main(int argc, char **argv) 
{
        std::string ifTest_thrust;

        ros::init(argc, argv, "thrustTested_client"); // Initializes Node Name
        ros::NodeHandle nh;
        ros::ServiceClient thrustTested_cli = nh.serviceClient<std_srvs::SetBool> ("thrust_tested");

        std_srvs::SetBool srv;

        std::cout << "Test the thrusters? Y for yes, N for no. (Y/N): ";
        std::getline(std::cin, ifTest_thrust);
	if (ifTest_thrust == "Y")
	   srv.request.data = true;
	else {
	   if (ifTest_thrust == "N")
	      srv.request.data = false;
	   else {
              std::cout << "Please enter 'Y' or 'N' to determine whether to test the thrusters." << std::endl;
              return 0;
             }
          }

        thrustTested_cli.call(srv);
	ROS_INFO("\033[01;33m[NOTICE]It's normal to get ERROR about none return since the arduino-compatible server response is still under development...\n\n[Others]Remeber to close the test procedure after test.");
	if (srv.request.data) {
           ROS_INFO("test the thruster...");
           ROS_INFO("%s", srv.response.message.c_str());
          }
        else {
           ROS_INFO("stop the test...");
           ROS_INFO("%s", srv.response.message.c_str());
          }

        return 0;
}

