
/*
 * RosComm.h
 *
 *  Created on: Tuesday, 25. February 2014 11:19AM
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
#include <tf/tf.h>
#include <boost/thread.hpp>
class ComponentMain;
class RosComm {
  bool _inited;
  ComponentMain   * _comp;
  ros::NodeHandle _nh;
  ros::Publisher _pub_diagnostic;
  boost::thread_group _maintains;
	ros::Subscriber _sub_WPDVelocity;
	ros::Subscriber _sub_WSMVelocity;
	ros::Subscriber _sub_BladePositionCommand;
	ros::Subscriber _sub_PerVelocity;
	ros::Subscriber _sub_Location;
	ros::Publisher  _pub_EffortsTh;
	ros::Publisher  _pub_EffortsSt;
	ros::Publisher  _pub_EffortsJn;

  bool init(int argc,char** argv);
public:
	RosComm(ComponentMain* comp,int argc,char** argv);
	virtual ~RosComm();
	void WPDVelocityCallback(const config::LLC::sub::WPDVelocity::ConstPtr &msg);
	void WSMVelocityCallback(const config::LLC::sub::WSMVelocity::ConstPtr &msg);
	void BladePositionCommandCallback(const config::LLC::sub::BladePositionCommand::ConstPtr &msg);
	void PerVelocityCallback(const config::LLC::sub::PerVelocity::ConstPtr &msg);
	void LocationCallback(const config::LLC::sub::Location::ConstPtr &msg);
	void publishEffortsTh( config::LLC::pub::EffortsTh &msg);
	void publishEffortsSt( config::LLC::pub::EffortsSt &msg);
	void publishEffortsJn( config::LLC::pub::EffortsJn &msg);

	void publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame);
	tf::StampedTransform getLastTrasform(std::string srcFrame, std::string distFrame);
	void publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report);
	void publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report);
	void heartbeat();
};
#endif /* ROSCOMM_H_ */