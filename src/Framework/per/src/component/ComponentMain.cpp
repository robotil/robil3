
/*
 * ComponentMain.cpp
 *
 *  Created on: Thursday, 27. February 2014 12:29PM
 *      Author: autogenerated
 */
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>
#include "ParameterHandler.h"
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <sensor_msgs/Imu.h>
#include "ComponentMain.h"
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/Bool.h>
#include <sensor_msgs/Image.h>
#include "heightmap.h"
//#include "heightmap_projection.h"
#include "helpermath.h"
#include "mapper/mapper.h"
#include "rdbg.h"
#include "per/configConfig.h"
#include "robil_msgs/MultiLaserScan.h"
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
using namespace std; 
typedef string String;
typedef bool boolean;

void cb(const sensor_msgs::ImuConstPtr& msgINS, const robil_msgs::MultiLaserScanConstPtr& msgIBEO)
{
    std::cout << "got data" << msgIBEO->header.stamp << ", " << msgINS->header.stamp << std::endl;
}

ComponentMain::ComponentMain(int argc,char** argv)
: _inited(init(argc, argv))
{
    _should_pub = true;
_sub_Location=ros::Subscriber(_nh.subscribe("/LOC/Pose", 10, &ComponentMain::handleLocation,this));
_sub_SensorINS=ros::Subscriber(_nh.subscribe("/SENSORS/INS", 10, &ComponentMain::handleSensorINS,this));
_sub_SensorCamL=ros::Subscriber(_nh.subscribe("/SENSORS/CAM/L", 10, &ComponentMain::handleSensorCamL,this));
_sub_SensorCamR=ros::Subscriber(_nh.subscribe("/SENSORS/CAM/R", 10, &ComponentMain::handleSensorCamR,this));
_sub_SensorSICK1=ros::Subscriber(_nh.subscribe("/SENSORS/SICK/1", 10, &ComponentMain::handleSensorSICK1,this));
_sub_SensorSICK2=ros::Subscriber(_nh.subscribe("/SENSORS/SICK/2", 10, &ComponentMain::handleSensorSICK2,this));
_sub_SensorIBEO=ros::Subscriber(_nh.subscribe("/SENSORS/IBEO", 10, &ComponentMain::handleSensorIBEO,this));
_pub_PC=ros::Publisher(_nh.advertise<sensor_msgs::PointCloud>("/SENSORS/IBEO/PC", 10));
_pub_PC_world=ros::Publisher(_nh.advertise<sensor_msgs::PointCloud>("/SENSORS/IBEO/WORLDPC", 10));
_pub_Map=ros::Publisher(_nh.advertise<robil_msgs::Map>("/PER/Map",10));
_pub_MiniMap=ros::Publisher(_nh.advertise<robil_msgs::Map>("/PER/MiniMap",10));
_pub_diagnostic=ros::Publisher(_nh.advertise<diagnostic_msgs::DiagnosticArray>("/diagnostics",100));
_pub_hMap = ros::Publisher(_nh.advertise<sensor_msgs::Image>("/PER/DEBUG/HEIGHTMAP",3));
_pub_tMap = ros::Publisher(_nh.advertise<sensor_msgs::Image>("/PER/DEBUG/TYPEMAP",3));
_maintains.add_thread(new boost::thread(boost::bind(&ComponentMain::heartbeat,this)));
//message_filters::Subscriber<sensor_msgs::Imu> ins_sub(_nh, "/SENSORS/INS", 1);
//message_filters::Subscriber<robil_msgs::MultiLaserScan> ibeo_sub(_nh, "/SENSORS/IBEO/1", 1);
// typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Imu, robil_msgs::MultiLaserScan> MySyncPolicy;
//message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), ins_sub, ibeo_sub);
//message_filters::TimeSynchronizer<sensor_msgs::Imu, robil_msgs::MultiLaserScan> sync(ins_sub, ibeo_sub, 10);
//sync.registerCallback(boost::bind(&ComponentMain::handleSensorIBEOandINS, this, _1, _2));
//sync.registerCallback(boost::bind(&cb, _1, _2));
	 Mapper::component = this;
     //Mapper::listener = new(tf::TransformListener);
     boost::thread mapper(Mapper::MainLoop, &this->_dyn_conf);
	 boost::this_thread::sleep(boost::posix_time::milliseconds(300));
	 boost::thread mapper2(Mapper::VisualizeLoop);
	 /// walrus func:
	  boost::this_thread::sleep(boost::posix_time::milliseconds(300));
	 //boost::thread mapper3(Mapper::StereoThread);
	 //boost::this_thread::sleep(boost::posix_time::milliseconds(300));
}
ComponentMain::~ComponentMain() {

    //delete Mapper::listener;
}
bool ComponentMain::init(int argc,char** argv){
	ros::init(argc,argv,"PER_node");
	return true;
}

void ComponentMain::handleLocation(const config::PER::sub::Location& msg)
{
  Mapper::handleLocation(msg);
}


void ComponentMain::setVisualize(char flags)
{
  Mapper::setVisualize((unsigned char)flags);
}

void ComponentMain::handlePerVelocity(const config::PER::sub::PerVelocity& msg)
{
}
	

void ComponentMain::handleSensorINS(const config::PER::sub::SensorINS& msg)
{
    _imuData = msg;
    tf::Quaternion q(msg.orientation.x, msg.orientation.y, msg.orientation.z, msg.orientation.w);
    tf::Matrix3x3 m(q);
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);
    double acc2 = msg.linear_acceleration.x * msg.linear_acceleration.x + msg.linear_acceleration.y * msg.linear_acceleration.y;
//    cout << msg.angular_velocity << endl;
    if (abs(pitch) > _dyn_conf.pitch_filter)
        _should_pub = true;
    else
        _should_pub = true;

//    cout << "got INS\n";
//    config::PER::pub::INS msg2;
//    msg2 = msg;
//    publishINS(msg2);
}
	

void ComponentMain::handleSensorGPS(const config::PER::sub::SensorGPS& msg)
{
	_gpsData = msg;
	config::PER::pub::GPS msg2;
	msg2 = msg;
	publishGPS(msg2);
}
	

void ComponentMain::handleSensorCamL(const config::PER::sub::SensorCamL& msg)
{
  Mapper::handleCamL(msg);
}
	

void ComponentMain::handleSensorCamR(const config::PER::sub::SensorCamR& msg)
{
  Mapper::handleCamR(msg);
}
	

void ComponentMain::handleSensorWire(const config::PER::sub::SensorWire& msg)
{
  //rdbg("wire");
}
	

void ComponentMain::handleSensorSICK1(const config::PER::sub::SensorSICK1& msg)
{
  Mapper::handleSickR(msg);
}
void ComponentMain::handleSensorSICK2(const config::PER::sub::SensorSICK2& msg)
{
  
  Mapper::handleSickL(msg);
}
	

void ComponentMain::handleSensorIBEO(const config::PER::sub::SensorIBEO& msgIBEO)
{
    int check=0;
    ros::param::param("/LOC/Ready",check,0);
    if(!check) return;
    if (_should_pub)
        Mapper::handleIBEO(msgIBEO, this->_pub_PC_world, this->_pub_PC);
}



void ComponentMain::handleSensorIBEOandINS(const sensor_msgs::ImuConstPtr& msgINS, const robil_msgs::MultiLaserScanConstPtr& msgIBEO)
{
    std::cout << "Got iamge" << std::endl;
  int check=0; 
  ros::param::param("/LOC/Ready",check,0);
  if(!check) return;
  // TODO if Pitch change is to extreme return from function and don't use IBEO measurement


//  Mapper::handleIBEO(*msgIBEO, this->_pub_PC_world, this->_pub_PC);

}
	


void ComponentMain::handleEffortsTh(const config::PER::sub::EffortsTh& msg)
{
	//std::cout<< "PER say:" << msg << std::endl;
}
	

void ComponentMain::handleEffortsSt(const config::PER::sub::EffortsSt& msg)
{
	//std::cout<< "PER say:" << msg << std::endl;
}
	

void ComponentMain::handleEffortsJn(const config::PER::sub::EffortsJn& msg)
{
	//std::cout<< "PER say:" << msg << std::endl;
}
	

void ComponentMain::publishGPS(config::PER::pub::GPS& msg)
{
	msg = _gpsData;
	//std::cout << "publishing: " << msg << std::endl;
	_pub_GPS.publish(msg);
}
	

void ComponentMain::publishINS(config::PER::pub::INS& msg)
{
	msg = _imuData;
	_pub_INS.publish(msg);
}
	

void ComponentMain::publishBladePosition(config::PER::pub::BladePosition& msg)
{
	_pub_BladePosition.publish(msg);
}
	

void ComponentMain::publishMap(config::PER::pub::Map& msg)
{
  _pub_Map.publish(msg);
}
	

void ComponentMain::publishMiniMap(config::PER::pub::MiniMap& msg)
{
   _pub_MiniMap.publish(msg);
}

void ComponentMain::publishDebug(sensor_msgs::ImagePtr hmsg, sensor_msgs::ImagePtr tmsg)
{
    _pub_hMap.publish(*hmsg);
    _pub_tMap.publish(*tmsg);
}

void ComponentMain::publishVOOdometry(config::PER::pub::VOOdometry& msg)
{
	_pub_VOOdometry.publish(msg);
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

void ComponentMain::handleGpsSpeed(const config::PER::sub::SensorGpsSpeed& msg)
{
	config::PER::pub::PerGpsSpeed msg2;
	msg2 = msg;
	publishGpsSpeed(msg2);
}

void ComponentMain::publishGpsSpeed(config::PER::pub::PerGpsSpeed& msg)
{
	_pub_GpsSpeed.publish(msg);
}

/**
 * Walrus Changes:
 */
void ComponentMain::setLanes(Mat m)
{
  Mapper::setLanes(m);
}

void ComponentMain::configCallback(per::configConfig &config, uint32_t level)
{
  // Set class variables to new values. They should match what is input at the dynamic reconfigure GUI.
    _dyn_conf = config;
    char flags = 0;
    if (config.heightMap)
        flags += 1;
    if (config.typeMap)
        flags += 8;
    if (config.Debug)
        ros::param::set("/PER/DEBUG",true);
    else
        ros::param::set("/PER/DEBUG", false);
    Mapper::setVisualize((unsigned char)flags);
}
void ComponentMain::heartbeat(){
	using namespace boost::posix_time;
	ros::Publisher _pub = _nh.advertise<std_msgs::String>("/heartbeat", 10);
	double hz = HEARTBEAT_FREQUANCY;
	while(ros::ok()){
		boost::system_time stop_time = boost::get_system_time() + milliseconds((1/hz)*1000);
		std_msgs::String msg;
		msg.data = "PER";
		_pub.publish(msg);
	    boost::this_thread::sleep(stop_time);
	}
}
