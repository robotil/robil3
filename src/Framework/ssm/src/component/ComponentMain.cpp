
/*
 * ComponentMain.cpp
 *
 *  Created on: Thursday, 27. February 2014 12:29PM
 *      Author: autogenerated
 */
#include "ComponentMain.h"

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

ComponentMain::ComponentMain(int argc,char** argv)
: _inited(init(argc, argv))
{
	_sub_BladePosition=ros::Subscriber(_nh.subscribe("/PER/BladPosition", 10, &ComponentMain::handleBladePosition,this));
	_sub_Location=ros::Subscriber(_nh.subscribe("/LOC/Pose", 10, &ComponentMain::handleLocation,this));
	_sub_PerVelocity=ros::Subscriber(_nh.subscribe("/LOC/Velocity", 10, &ComponentMain::handlePerVelocity,this));

	_pub_diagnostic=ros::Publisher(_nh.advertise<diagnostic_msgs::DiagnosticArray>("/diagnostics",100));
	_maintains.add_thread(new boost::thread(boost::bind(&ComponentMain::heartbeat,this)));
}

ComponentMain::~ComponentMain() {
}
bool ComponentMain::init(int argc,char** argv){
	ros::init(argc,argv,"SSM_node");
	return true;
}

void ComponentMain::handleBladePosition(const sensor_msgs::JointState& msg)
{
	//std::cout<< "SSM say:" << msg << std::endl;
}
	

void ComponentMain::handleLocation(const geometry_msgs::PoseWithCovarianceStamped& msg)
{
	//std::cout<< "SSM say:" << msg << std::endl;
}
	

void ComponentMain::handlePerVelocity(const geometry_msgs::TwistStamped& msg)
{
	//std::cout<< "SSM say:" << msg << std::endl;
}
	

void ComponentMain::publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame){
	static tf::TransformBroadcaster br;
	br.sendTransform(tf::StampedTransform(_tf, ros::Time::now(), srcFrame, distFrame));
}
tf::StampedTransform ComponentMain::getLastTransform(std::string srcFrame, std::string distFrame){
	tf::StampedTransform _tf;
		static tf::TransformListener listener;
		try {
		    listener.waitForTransform(distFrame, srcFrame, ros::Time(0), ros::Duration(10.0) );
		    listener.lookupTransform(distFrame, srcFrame, ros::Time(0), _tf);
		} catch (tf::TransformException& ex) {
		    ROS_ERROR("%s",ex.what());
		}
		return _tf;
}
void ComponentMain::publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report){
	diagnostic_msgs::DiagnosticArray msg;
		msg.status.push_back(_report);
		_pub_diagnostic.publish(msg);
}
void ComponentMain::publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report){
	diagnostic_msgs::DiagnosticArray msg;
		msg.header = header;
		msg.status.push_back(_report);
		_pub_diagnostic.publish(msg);
}

void ComponentMain::heartbeat(){
		using namespace boost::posix_time;
		ros::Publisher _pub = _nh.advertise<std_msgs::String>("/heartbeat", 10);
		double hz = HEARTBEAT_FREQUANCY;
		while(ros::ok()){
			boost::system_time stop_time = boost::get_system_time() + milliseconds((1/hz)*1000);
			std_msgs::String msg;
			msg.data = "SSM";
			_pub.publish(msg);
		    boost::this_thread::sleep(stop_time);
		}
}
