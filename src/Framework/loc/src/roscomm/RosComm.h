
/*
 * RosComm.h
 *
 *  Created on: Wednesday, 19. February 2014 04:26PM
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
	ros::Subscriber _sub_PositionUpdate;
	ros::Subscriber _sub_GPS;
	ros::Subscriber _sub_INS;
	ros::Subscriber _sub_VOOdometry;
	ros::Publisher  _pub_PerVelocity;
	ros::Publisher  _pub_Location;

  bool init(int argc,char** argv);
public:
	RosComm(ComponentMain* comp,int argc,char** argv);
	virtual ~RosComm();
	void PositionUpdateCallback(const config::LOC::sub::PositionUpdate::ConstPtr &msg);
	void GPSCallback(const config::LOC::sub::GPS::ConstPtr &msg);
	void INSCallback(const config::LOC::sub::INS::ConstPtr &msg);
	void VOOdometryCallback(const config::LOC::sub::VOOdometry::ConstPtr &msg);
	void publishPerVelocity( config::LOC::pub::PerVelocity &msg);
	void publishLocation( config::LOC::pub::Location &msg);

	void publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame);
	tf::StampedTransform getLastTrasform(std::string srcFrame, std::string distFrame);
	void publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report);
	void publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report);
	void heartbeat();
};
#endif /* ROSCOMM_H_ */
