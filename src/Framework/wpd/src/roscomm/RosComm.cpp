
/*
 * RosComm.cpp
 *
 *  Created on: Thursday, 30. January 2014 04:16PM
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
RosComm::RosComm(ComponentMain* comp,int argc,char** argv)
{
  ros::init(argc,argv,"PP_node");
  _comp=comp;
	_sub_RPPPath=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"WPD","RPPPath","sub"), 10, &RosComm::RPPPathCallback,this));
	_sub_PosAttVel=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"WPD","PosAttVel","sub"), 10, &RosComm::PosAttVelCallback,this));
	_pub_TrottleEffort=ros::Publisher(_nh.advertise<config::WPD::pub::TrottleEffort>(fetchParam(&_nh,"WPD","TrottleEffort","pub"),10));
	_pub_SteeringEffort=ros::Publisher(_nh.advertise<config::WPD::pub::SteeringEffort>(fetchParam(&_nh,"WPD","SteeringEffort","pub"),10));
}
RosComm::~RosComm()
{
}

void RosComm::RPPPathCallback(const config::WPD::sub::RPPPath::ConstPtr &msg)
{
	_comp->handleRPPPath(*msg);
}
	

void RosComm::PosAttVelCallback(const config::WPD::sub::PosAttVel::ConstPtr &msg)
{
	_comp->handlePosAttVel(*msg);
}
	

void RosComm::publishTrottleEffort( config::WPD::pub::TrottleEffort &msg)
{
	_pub_TrottleEffort.publish(msg);
}
	

void RosComm::publishSteeringEffort( config::WPD::pub::SteeringEffort &msg)
{
	_pub_SteeringEffort.publish(msg);
}
	
