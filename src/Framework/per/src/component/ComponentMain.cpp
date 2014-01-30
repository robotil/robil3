
/*
 * ComponentMain.cpp
 *
 *  Created on: Thursday, 30. January 2014 06:41PM
 *      Author: autogenerated
 */
#include "ComponentMain.h"
#include "../roscomm/RosComm.h"
ComponentMain::ComponentMain(int argc,char** argv)
{
	_roscomm = new RosComm(this,argc, argv);
}
ComponentMain::~ComponentMain() {
	if(_roscomm) delete _roscomm; _roscomm=0;
}

void ComponentMain::handleSensor_SICK(const config::PER::sub::Sensor_SICK& msg)
{
	std::cout<< "PER say:" << msg << std::endl;
}
	

void ComponentMain::handleSensor_IBEO(const config::PER::sub::Sensor_IBEO& msg)
{
	std::cout<< "PER say:" << msg << std::endl;
}
	

void ComponentMain::handleSensor_CAM_R(const config::PER::sub::Sensor_CAM_R& msg)
{
	std::cout<< "PER say:" << msg << std::endl;
}
	

void ComponentMain::handleSensor_CAM_L(const config::PER::sub::Sensor_CAM_L& msg)
{
	std::cout<< "PER say:" << msg << std::endl;
}
	

void ComponentMain::handleSensor_WIRE(const config::PER::sub::Sensor_WIRE& msg)
{
	std::cout<< "PER say:" << msg << std::endl;
}
	

void ComponentMain::handleSensor_GPS(const config::PER::sub::Sensor_GPS& msg)
{
	std::cout<< "PER say:" << msg << std::endl;
}
	

void ComponentMain::handleSensor_INS(const config::PER::sub::Sensor_INS& msg)
{
	std::cout<< "PER say:" << msg << std::endl;
}
	

void ComponentMain::publishWiresLengths(config::PER::pub::WiresLengths& msg)
{
	_roscomm->publishWiresLengths(msg);
}
	

void ComponentMain::publishCamera(config::PER::pub::Camera& msg)
{
	_roscomm->publishCamera(msg);
}
	

void ComponentMain::publishLaser(config::PER::pub::Laser& msg)
{
	_roscomm->publishLaser(msg);
}
	

void ComponentMain::publishINS(config::PER::pub::INS& msg)
{
	_roscomm->publishINS(msg);
}
	

void ComponentMain::publishGPS(config::PER::pub::GPS& msg)
{
	_roscomm->publishGPS(msg);
}
	

void ComponentMain::publishTF(config::PER::pub::TF& msg)
{
	_roscomm->publishTF(msg);
}
	
