
/*
 * RosComm.cpp
 *
 *  Created on: Tuesday, 25. February 2014 11:19AM
 *      Author: autogenerated
 */
#include <ros/ros.h>
#include <std_msgs/String.h>
#include "RosComm.h"
#include "../component/ComponentMain.h"
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>
#include "ParameterHandler.h"
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
RosComm::RosComm(ComponentMain* comp,int argc,char** argv)
	: _inited(init(argc, argv)), _comp(comp)
{
	_sub_WPDVelocity=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"LLC","WPDVelocity","sub"), 10, &RosComm::WPDVelocityCallback,this));
	_sub_WSMVelocity=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"LLC","WSMVelocity","sub"), 10, &RosComm::WSMVelocityCallback,this));
	_sub_BladePositionCommand=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"LLC","BladePositionCommand","sub"), 10, &RosComm::BladePositionCommandCallback,this));
	_sub_PerVelocity=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"LLC","PerVelocity","sub"), 10, &RosComm::PerVelocityCallback,this));
	_sub_Location=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"LLC","Location","sub"), 10, &RosComm::LocationCallback,this));
	_pub_EffortsTh=ros::Publisher(_nh.advertise<config::LLC::pub::EffortsTh>(fetchParam(&_nh,"LLC","EffortsTh","pub"),10));
	_pub_EffortsSt=ros::Publisher(_nh.advertise<config::LLC::pub::EffortsSt>(fetchParam(&_nh,"LLC","EffortsSt","pub"),10));
	_pub_EffortsJn=ros::Publisher(_nh.advertise<config::LLC::pub::EffortsJn>(fetchParam(&_nh,"LLC","EffortsJn","pub"),10));
	_pub_diagnostic=ros::Publisher(_nh.advertise<diagnostic_msgs::DiagnosticArray>("/diagnostics",100));
	_maintains.add_thread(new boost::thread(boost::bind(&RosComm::heartbeat,this)));
}
RosComm::~RosComm()
{
}
bool RosComm::init(int argc,char** argv){
	ros::init(argc,argv,"LLC_node");
	return true;
}


void RosComm::WPDVelocityCallback(const config::LLC::sub::WPDVelocity::ConstPtr &msg)
{
	_comp->handleWPDVelocity(*msg);
}
	

void RosComm::WSMVelocityCallback(const config::LLC::sub::WSMVelocity::ConstPtr &msg)
{
	_comp->handleWSMVelocity(*msg);
}
	

void RosComm::BladePositionCommandCallback(const config::LLC::sub::BladePositionCommand::ConstPtr &msg)
{
	_comp->handleBladePositionCommand(*msg);
}
	

void RosComm::PerVelocityCallback(const config::LLC::sub::PerVelocity::ConstPtr &msg)
{
	_comp->handlePerVelocity(*msg);
}
	

void RosComm::LocationCallback(const config::LLC::sub::Location::ConstPtr &msg)
{
	_comp->handleLocation(*msg);
}
	

void RosComm::publishEffortsTh( config::LLC::pub::EffortsTh &msg)
{
	_pub_EffortsTh.publish(msg);
}
	

void RosComm::publishEffortsSt( config::LLC::pub::EffortsSt &msg)
{
	_pub_EffortsSt.publish(msg);
}
	

void RosComm::publishEffortsJn( config::LLC::pub::EffortsJn &msg)
{
	_pub_EffortsJn.publish(msg);
}
	
void RosComm::publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame){
	static tf::TransformBroadcaster br;
	br.sendTransform(tf::StampedTransform(_tf, ros::Time::now(), srcFrame, distFrame));
}
tf::StampedTransform RosComm::getLastTrasform(std::string srcFrame, std::string distFrame){
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
void RosComm::publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report){
	diagnostic_msgs::DiagnosticArray msg;
	msg.status.push_back(_report);
	_pub_diagnostic.publish(msg);
}
void RosComm::publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report){
	diagnostic_msgs::DiagnosticArray msg;
	msg.header = header;
	msg.status.push_back(_report);
	_pub_diagnostic.publish(msg);
}
void RosComm::heartbeat(){
	using namespace boost::posix_time;
	ros::Publisher _pub = _nh.advertise<std_msgs::String>("/heartbeat", 10);
	double hz = HEARTBEAT_FREQUANCY;
	while(ros::ok()){
		boost::system_time stop_time = boost::get_system_time() + milliseconds((1/hz)*1000);
		std_msgs::String msg;
		msg.data = "LLC";
		_pub.publish(msg);
	    boost::this_thread::sleep(stop_time);
	}
}