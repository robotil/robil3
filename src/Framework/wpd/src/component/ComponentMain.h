
/*
 * ComponentMain.h
 *
 *  Created on: Thursday, 27. February 2014 12:29PM
 *      Author: autogenerated
 */
#ifndef COMPONENTMAIN_H_
#define COMPONENTMAIN_H_
#include <std_msgs/String.h>
#include <tf/tf.h>
#include <ros/ros.h>

#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>

#include <boost/thread.hpp>

#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <diagnostic_msgs/DiagnosticArray.h>
#include <robil_msgs/Path.h>
#include <robil_msgs/Map.h>

class MoveBase;
class ComponentMain {
	bool _inited;

	  ros::NodeHandle _nh;
	  ros::Publisher _pub_diagnostic;
	  boost::thread_group _maintains;
		ros::Subscriber _sub_LocalPath;
		ros::Subscriber _sub_MiniMap;
		ros::Subscriber _sub_Location;
		ros::Publisher  _pub_WPDVelocity;

	  bool init(int argc,char** argv);

	MoveBase* _move_base;
public:
	ComponentMain(int argc,char** argv);
	virtual ~ComponentMain();
	void handleLocalPath(const robil_msgs::Path& msg);
	void handleMiniMap(const robil_msgs::Map& msg);
	void handleLocation(const geometry_msgs::PoseWithCovarianceStamped& msg);
	void publishWPDVelocity(geometry_msgs::TwistStamped& msg);
	void publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame);
	tf::StampedTransform getLastTransform(std::string srcFrame, std::string distFrame);
	void publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report);
	void publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report);
	void heartbeat();
};
#endif /* COMPONENTMAIN_H_ */
