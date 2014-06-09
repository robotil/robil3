
/*
 * ComponentMain.cpp
 *
 *  Created on: Thursday, 27. February 2014 12:29PM
 *      Author: autogenerated
 */
#include "ComponentMain.h"
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/Bool.h>
#include "../roscomm/RosComm.h"
#include "heightmap.h"
#include "heightmap_projection.h"
#include "helpermath.h"
#include "stereo.h"
#include "rdbg.h"

#define DEGREE_TO_M		111000

using namespace std; 
typedef string String;
typedef bool boolean;
using namespace cv;
Rotation myRot, ibeoRot, leftSickRot, rightSickRot;
Vec3D position;
Quaternion myQuat;
bool loc_received = false;
bool camL = false;
bool camR = false;
Mat camLImg, camRImg;
bool visualize = false;



ComponentMain::ComponentMain(int argc,char** argv)
{
	_roscomm = new RosComm(this,argc, argv);
	 height_map = new HeightMap(500,500);
	 
	
}
ComponentMain::~ComponentMain() {
	if(_roscomm) delete _roscomm; _roscomm=0;
}

void ComponentMain::handleLocation(const config::PER::sub::Location& msg)
{
  geometry_msgs::Pose pose = msg.pose.pose;
  position = Vec3D(pose.position.x, pose.position.y, pose.position.z);
  myQuat = Quaternion(pose.orientation.x, pose.orientation.y, pose.orientation.z, pose.orientation.w);
  myRot = GetRotation(myQuat);
  ibeoRot = myRot.add(Rotation(0, 0.284, -0));
  leftSickRot = Rotation(myRot.pitch, myRot.roll, myRot.yaw+1.57);
  rightSickRot = Rotation(-myRot.pitch, -myRot.roll, myRot.yaw-1.57);
  loc_received = true;
  
  //rdbg("VISUALISE");
  if(visualize)
  {
    //height_map->displayGUI(myRot.yaw*180/3.14159, position.x, position.y);
    //waitKey(1);
    HeightMap m = height_map->deriveMap(position.x, position.y, myRot);
    m.displayGUI(0,-5,0);
    waitKey(1);
    m.calculateTypes();
    m.displayTypesGUI();
  }
  
  //height_map->calculateTypes();
  //height_map->displayTypesGUI();
}


void ComponentMain::setVisualize(bool flag)
{
  visualize = flag;
}

void ComponentMain::handlePerVelocity(const config::PER::sub::PerVelocity& msg)
{
	//std::cout<< "PER say:" << msg << std::endl;
}
	

void ComponentMain::handleSensorINS(const config::PER::sub::SensorINS& msg)
{
	_imuData = msg;
	//std::cout<< "PER say:" << msg << std::endl;
	config::PER::pub::INS msg2;
	msg2 = msg;
	publishINS(msg2);
	
}
	

void ComponentMain::handleSensorGPS(const config::PER::sub::SensorGPS& msg)
{
	//std::cout<< "PER say:" << msg << std::endl;
	_gpsData = msg;
	config::PER::pub::GPS msg2;
	msg2 = msg;
	publishGPS(msg2);	
	//rdbg("gps");
}
	

void ComponentMain::handleSensorCamL(const config::PER::sub::SensorCamL& msg)
{
  //rdbg("leftcam");
  cv_bridge::CvImagePtr cv_ptr;
  try
  {
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }
  camLImg = cv_ptr->image;
  camL = true;
  if(camL && camR)
  {
      camL = camR = false;
      handleStereo(camLImg, camRImg);
  }
}
	

void ComponentMain::handleSensorCamR(const config::PER::sub::SensorCamR& msg)
{
  //rdbg("rightcam");
  cv_bridge::CvImagePtr cv_ptr;
  try
  {
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }
  camRImg = cv_ptr->image;
  camR = true;
  if(camL && camR)
  {
      camL = camR = false;
      handleStereo(camLImg, camRImg);
      
  }
  
}
	

void ComponentMain::handleSensorWire(const config::PER::sub::SensorWire& msg)
{
  //rdbg("wire");
}
	

void ComponentMain::handleSensorSICK1(const config::PER::sub::SensorSICK1& msg)
{
  if(!loc_received) return;
  Quaternion q = GetFromRPY(leftSickRot);
  Vec3D front = GetFrontVector(q.x,q.y,q.z,q.w);
  Vec3D right = GetRightVector(q.x,q.y,q.z,q.w);
  Vec3D up = GetUpVector(q.x,q.y,q.z,q.w);
  
  Vec3D pos = position.add(front.multiply(-0.2187)).add(right.multiply(0.85)).add(up.multiply(0.631));
  
  for(int i = 0; i < msg.ranges.size(); i++) 
    if(msg.ranges[i] < 0.5*msg.range_max && msg.ranges[i] > 2)
      ProjectLaserRange(
		      height_map, 
		      right, 
		      front,
		      pos, 
		      msg.ranges[i],
		      msg.angle_min + i*msg.angle_increment);
}
void ComponentMain::handleSensorSICK2(const config::PER::sub::SensorSICK2& msg)
{
  if(!loc_received) return;
  Quaternion q = GetFromRPY(rightSickRot);
  Vec3D front = GetFrontVector(q.x,q.y,q.z,q.w);
  Vec3D right = GetRightVector(q.x,q.y,q.z,q.w);
  Vec3D up = GetUpVector(q.x,q.y,q.z,q.w);
  
  Vec3D pos = position.add(front.multiply(-0.2187)).add(right.multiply(-0.85)).add(up.multiply(0.631));
  
  for(int i = 0; i < msg.ranges.size(); i++) 
    if(msg.ranges[i] < 0.5*msg.range_max && msg.ranges[i]>2)
      ProjectLaserRange(
		      height_map, 
		      right, 
		      front,
		      pos, 
		      msg.ranges[i],
		      msg.angle_min + i*msg.angle_increment);
}
	

void ComponentMain::handleSensorIBEO(const config::PER::sub::SensorIBEO& msg)
{
  if(!loc_received) return;
  Rotation t2 = ibeoRot.add(Rotation(0, -msg.angle_t2, 0));
  Rotation t1 = ibeoRot.add(Rotation(0, -msg.angle_t1, 0));
  Rotation b1 = ibeoRot.add(Rotation(0, -msg.angle_b1, 0));
  Rotation b2 = ibeoRot.add(Rotation(0, -msg.angle_b2, 0));
  Quaternion qt2 = GetFromRPY(t2);
  Quaternion qt1 = GetFromRPY(t1);
  Quaternion qb1 = GetFromRPY(b1);
  Quaternion qb2 = GetFromRPY(b2);
  Vec3D t2front = GetFrontVector(qt2.x,qt2.y,qt2.z,qt2.w), t2right = GetRightVector(qt2.x,qt2.y,qt2.z,qt2.w);
  Vec3D t1front = GetFrontVector(qt1.x,qt1.y,qt1.z,qt1.w), t1right = GetRightVector(qt1.x,qt1.y,qt1.z,qt1.w);
  Vec3D b1front = GetFrontVector(qb1.x,qb1.y,qb1.z,qb1.w), b1right = GetRightVector(qb1.x,qb1.y,qb1.z,qb1.w);
  Vec3D b2front = GetFrontVector(qb2.x,qb2.y,qb2.z,qb2.w), b2right = GetRightVector(qb2.x,qb2.y,qb2.z,qb2.w);
  
  Quaternion q = GetFromRPY(ibeoRot);
  Vec3D front = GetFrontVector(q.x,q.y,q.z,q.w);
  Vec3D right = GetRightVector(q.x,q.y,q.z,q.w);
  Vec3D up = GetUpVector(q.x,q.y,q.z,q.w);
  
  Vec3D pos = position.add(front.multiply(-0.375)).add(right.multiply(0.055)).add(up.multiply(1.89));
  
  
  double incrtop = msg.angle_increment;
  double incrbottom = msg.angle_increment;
  
    for(int i = 0; i < msg.ranges_t2.size(); i++) 
    {
      if(msg.ranges_t2[i] < 0.5*msg.range_max)
      ProjectLaserRange(
			height_map, 
			t2right, 
			t2front,
			pos, 
			msg.ranges_t2[i],
			msg.angle_min_t + i*incrtop);
    }  
    
    for(int i = 0; i < msg.ranges_t1.size(); i++) 
    {
      if(msg.ranges_t1[i] < 0.5*msg.range_max)
      ProjectLaserRange(
			height_map, 
			t1right, 
			t1front,
			pos, 
			msg.ranges_t1[i],
			msg.angle_min_t + i*incrtop); 
    }
    for(int i = 0; i < msg.ranges_b1.size(); i++) 
    {
      if(msg.ranges_b1[i] < 0.5*msg.range_max)
      ProjectLaserRange(
		      height_map, 
		      b1right, 
		      b1front,
		      pos, 
		      msg.ranges_b1[i],
		      msg.angle_min_b + i*incrbottom);
    }
    for(int i = 0; i < msg.ranges_b2.size(); i++) 
    {
      if(msg.ranges_b2[i] < 0.5*msg.range_max)
      ProjectLaserRange(
		      height_map, 
		      b2right, 
		      b2front,
		      pos, 
		      msg.ranges_b2[i],
		      msg.angle_min_b + i*incrbottom);
    }
    config::PER::pub::Map msg2;
    config::PER::pub::Map msg3;
    publishMap(msg2);
    publishMiniMap(msg3);
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
	
void ComponentMain::handleGpsSpeed(const config::PER::sub::SensorGpsSpeed& msg)
{
	//std::cout<< "PER say:" << msg << std::endl;
}
	

void ComponentMain::publishGPS(config::PER::pub::GPS& msg)
{
	msg = _gpsData;
	//std::cout << "publishing: " << msg << std::endl;
	_roscomm->publishGPS(msg);
}
	

void ComponentMain::publishINS(config::PER::pub::INS& msg)
{
	msg = _imuData;
	_roscomm->publishINS(msg);
}
	

void ComponentMain::publishBladePosition(config::PER::pub::BladePosition& msg)
{
	_roscomm->publishBladePosition(msg);
}
	

void ComponentMain::publishMap(config::PER::pub::Map& msg)
{
  static int seq = 0;
  static ros::Time lastSendTime;
  if(ros::Time::now().toSec() - lastSendTime.toSec() > 0.5)
    lastSendTime = ros::Time::now();
  else return;
  msg.header.seq = seq++;
  msg.header.stamp.sec = ros::Time::now().sec;
  msg.header.stamp.nsec = ros::Time::now().nsec;
  msg.header.frame_id = "map";
  
  msg.info.map_load_time.sec = ros::Time::now().sec;
  msg.info.map_load_time.nsec = ros::Time::now().nsec;
  msg.info.width = 150;
  msg.info.height = 150;
  msg.info.resolution = 0.2;
  msg.info.origin.position.x = position.x;
  msg.info.origin.position.y = position.y;
  msg.info.origin.position.z = position.z;
  msg.info.origin.orientation.x = myQuat.x;
  msg.info.origin.orientation.y = myQuat.y;
  msg.info.origin.orientation.z = myQuat.z;
  msg.info.origin.orientation.w = myQuat.w;
  msg.data.resize(150*150);
  
  HeightMap Oded = height_map->deriveMap(position.x, position.y, myRot);
  Oded.calculateTypes();
  vector<double>& heights = Oded.getHeights();
  vector<int>& types = Oded.getTypes();
  for(int i = 0; i < 150; i++)
    for(int j = 0; j < 150; j++)
    {
      msg.data[j*150+i].height = heights[j*150+i];
      msg.data[j*150+i].type = types[j*150+i];
    }
  _roscomm->publishMap(msg);
}
	

void ComponentMain::publishMiniMap(config::PER::pub::MiniMap& msg)
{
    static int seq = 0;
    //rdbg("hi");
    msg.header.seq = seq++;
    msg.header.stamp.sec = ros::Time::now().sec;
    msg.header.stamp.nsec = ros::Time::now().nsec;
    msg.header.frame_id = "map";
    
    msg.info.map_load_time.sec = ros::Time::now().sec;
    msg.info.map_load_time.nsec = ros::Time::now().nsec;
    msg.info.width = 50;
    msg.info.height = 30;
    msg.info.resolution = 0.2;
    msg.info.origin.position.x = position.x;
    msg.info.origin.position.y = position.y;
    msg.info.origin.position.z = position.z;
    msg.info.origin.orientation.x = myQuat.x;
    msg.info.origin.orientation.y = myQuat.y;
    msg.info.origin.orientation.z = myQuat.z;
    msg.info.origin.orientation.w = myQuat.w;
    msg.data.resize(50*30);
    
    HeightMap Oded = height_map->deriveMiniMap(position.x, position.y, myRot);
    Oded.calculateTypes();
    vector<double>& heights = Oded.getHeights();
    vector<int>& types = Oded.getTypes();
    for(int j = 0; j < 50; j++) //height
      for(int i = 0; i < 30; i++) //width
      {
	msg.data[j*30+i].height = heights[j*30+i];
	msg.data[j*30+i].type = types[j*30+i];
      }
    _roscomm->publishMiniMap(msg);
}
	

void ComponentMain::publishVOOdometry(config::PER::pub::VOOdometry& msg)
{
	_roscomm->publishVOOdometry(msg);
}

void ComponentMain::publishGpsSpeed(config::PER::pub::PerGpsSpeed& msg)
{
	_roscomm->publishGpsSpeed(msg);
}
	
void ComponentMain::publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame){
	_roscomm->publishTransform(_tf, srcFrame, distFrame);
}
tf::StampedTransform ComponentMain::getLastTrasform(std::string srcFrame, std::string distFrame){
	return _roscomm->getLastTrasform(srcFrame, distFrame);
}
void ComponentMain::publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report){
	_roscomm->publishDiagnostic(_report);
}
void ComponentMain::publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report){
	_roscomm->publishDiagnostic(header, _report);
}
