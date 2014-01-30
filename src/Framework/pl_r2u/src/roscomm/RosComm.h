
/*
 * RosComm.h
 *
 *  Created on: Thursday, 30. January 2014 04:16PM
 *      Author: autogenerated
 */
#ifndef ROSCOMM_H_
#define ROSCOMM_H_
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>
#include <ParameterTypes.h>
class ComponentMain;
class RosComm {
  ComponentMain   * _comp;
  ros::NodeHandle _nh;
	ros::Subscriber _sub_TrottleEffort;
	ros::Subscriber _sub_SteeringEffort;
	ros::Subscriber _sub_JointsEffort;


public:
	RosComm(ComponentMain* comp,int argc,char** argv);
	virtual ~RosComm();
	void TrottleEffortCallback(const config::PL_R2U::sub::TrottleEffort::ConstPtr &msg);
	void SteeringEffortCallback(const config::PL_R2U::sub::SteeringEffort::ConstPtr &msg);
	void JointsEffortCallback(const config::PL_R2U::sub::JointsEffort::ConstPtr &msg);


};
#endif /* ROSCOMM_H_ */
