
/*
 * RosComm.cpp
 *
 *  Created on: Thursday, 30. January 2014 06:41PM
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
	_sub_PosAttVel=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"LOC","PosAttVel","sub"), 10, &RosComm::PosAttVelCallback,this));
	_sub_PositionUpdate=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"LOC","PositionUpdate","sub"), 10, &RosComm::PositionUpdateCallback,this));
	_pub_PosAttVel=ros::Publisher(_nh.advertise<config::LOC::pub::PosAttVel>(fetchParam(&_nh,"LOC","PosAttVel","pub"),10));
}
RosComm::~RosComm()
{
}

void RosComm::PosAttVelCallback(const config::LOC::sub::PosAttVel::ConstPtr &msg)
{
	_comp->handlePosAttVel(*msg);
}
	

void RosComm::PositionUpdateCallback(const config::LOC::sub::PositionUpdate::ConstPtr &msg)
{
	_comp->handlePositionUpdate(*msg);
}
	

void RosComm::publishPosAttVel( config::LOC::pub::PosAttVel &msg)
{
	_pub_PosAttVel.publish(msg);
}
	
