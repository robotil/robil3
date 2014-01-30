
/*
 * RosComm.h
 *
 *  Created on: Thursday, 30. January 2014 06:41PM
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
	ros::Subscriber _sub_PosAttVel;
	ros::Subscriber _sub_StatusData;
	ros::Subscriber _sub_MissionStatus;
	ros::Subscriber _sub_Map;
	ros::Subscriber _sub_LocalPathPlan;
	ros::Subscriber _sub_IEDDetectionEvent;
	ros::Subscriber _sub_IEDLocation;
	ros::Publisher  _pub_PositionUpdate;
	ros::Publisher  _pub_MissionPlan;
	ros::Publisher  _pub_Teleoperation;
	ros::Publisher  _pub_IEDDetectionEvent;
	ros::Publisher  _pub_IEDLocation;

public:
	RosComm(ComponentMain* comp,int argc,char** argv);
	virtual ~RosComm();
	void PosAttVelCallback(const config::OCU::sub::PosAttVel::ConstPtr &msg);
	void StatusDataCallback(const config::OCU::sub::StatusData::ConstPtr &msg);
	void MissionStatusCallback(const config::OCU::sub::MissionStatus::ConstPtr &msg);
	void MapCallback(const config::OCU::sub::Map::ConstPtr &msg);
	void LocalPathPlanCallback(const config::OCU::sub::LocalPathPlan::ConstPtr &msg);
	void IEDDetectionEventCallback(const config::OCU::sub::IEDDetectionEvent::ConstPtr &msg);
	void IEDLocationCallback(const config::OCU::sub::IEDLocation::ConstPtr &msg);
	void publishPositionUpdate( config::OCU::pub::PositionUpdate &msg);
	void publishMissionPlan( config::OCU::pub::MissionPlan &msg);
	void publishTeleoperation( config::OCU::pub::Teleoperation &msg);
	void publishIEDDetectionEvent( config::OCU::pub::IEDDetectionEvent &msg);
	void publishIEDLocation( config::OCU::pub::IEDLocation &msg);

};
#endif /* ROSCOMM_H_ */
