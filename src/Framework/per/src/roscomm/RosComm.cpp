/*
 * RosComm.cpp
 *
 *  Created on: Jan 16, 2014
 *      Author: yuval
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
  ros::init(argc,argv,"PER_node");
  _nh=new ros::NodeHandle;
  _comp=comp;

  _sub_Sensor_SICK=
      new ros::Subscriber(_nh->subscribe(fetchParam(_nh,"PER","Sensor_SICK","sub"), 1, &RosComm::Sensor_SICKCallback,this));

  _sub_Sensor_IBEO=
  new ros::Subscriber(_nh->subscribe(fetchParam(_nh,"PER","Sensor_IBEO","sub"), 1, &RosComm::Sensor_IBEOCallback,this));

  _sub_Sensor_CAM_R=
  new ros::Subscriber(_nh->subscribe(fetchParam(_nh,"PER","Sensor_CAM_R","sub"), 1, &RosComm::Sensor_CAM_RCallback,this));

  _sub_Sensor_CAM_L=
  new ros::Subscriber(_nh->subscribe(fetchParam(_nh,"PER","Sensor_CAM_L","sub"), 1, &RosComm::Sensor_CAM_LCallback,this));

  _sub_Sensor_WIRE=
  new ros::Subscriber(_nh->subscribe(fetchParam(_nh,"PER","Sensor_WIRE","sub"), 1, &RosComm::Sensor_WIRECallback,this));

  _sub_Sensor_INSGPS=
  new ros::Subscriber(_nh->subscribe(fetchParam(_nh,"PER","Sensor_INSGPS","sub"), 1, &RosComm::Sensor_INSGPSCallback,this));

  _pub_WiresLengths=
      new ros::Publisher(_nh->advertise<std_msgs::String>(fetchParam(_nh,"PER","WiresLengths","pub"),1));

  _pub_Camera=
      new ros::Publisher(_nh->advertise<std_msgs::String>(fetchParam(_nh,"PER","Camera","pub"),1));

  _pub_Laser=
      new ros::Publisher(_nh->advertise<std_msgs::String>(fetchParam(_nh,"PER","Laser","pub"),1));

  _pub_INS=
      new ros::Publisher(_nh->advertise<std_msgs::String>(fetchParam(_nh,"PER","INS","pub"),1));

  _pub_GPS=
      new ros::Publisher(_nh->advertise<std_msgs::String>(fetchParam(_nh,"PER","GPS","pub"),1));

  _pub_TF=
      new ros::Publisher(_nh->advertise<std_msgs::String>(fetchParam(_nh,"PER","TF","pub"),1));


}

RosComm::~RosComm()
{
	// TODO Auto-generated destructor stub
}


void RosComm::Sensor_SICKCallback(const std_msgs::String::ConstPtr &msg)
{
  _comp->handleSensor_SICK(*msg);
}
void RosComm::Sensor_IBEOCallback(const std_msgs::String::ConstPtr &msg)
{
  _comp->handleSensor_IBEO(*msg);
}
void RosComm::Sensor_CAM_RCallback(const std_msgs::String::ConstPtr &msg)
{
  _comp->handleSensor_CAM_R(*msg);
}
void RosComm::Sensor_CAM_LCallback(const std_msgs::String::ConstPtr &msg)
{
  _comp->handleSensor_CAM_L(*msg);
}
void RosComm::Sensor_WIRECallback(const std_msgs::String::ConstPtr &msg)
{
  _comp->handleSensor_WIRE(*msg);
}
void RosComm::Sensor_INSGPSCallback(const std_msgs::String::ConstPtr &msg)
{
  _comp->handleSensor_INSGPS(*msg);
}

void RosComm::publishWiresLengths(std_msgs::String &msg)
{
  _pub_WiresLengths->publish(msg);
}
void RosComm::publishCamera(std_msgs::String &msg)
{
  _pub_Camera->publish(msg);
}
void RosComm::publishLaser(std_msgs::String &msg)
{
  _pub_Laser->publish(msg);
}
void RosComm::publishINS(std_msgs::String &msg)
{
  _pub_INS->publish(msg);
}
void RosComm::publishGPS(std_msgs::String &msg)
{
  _pub_GPS->publish(msg);
}

void RosComm::publishTF(std_msgs::String &msg)
{
  _pub_TF->publish(msg);
}
