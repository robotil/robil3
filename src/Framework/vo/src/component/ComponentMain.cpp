
/*
 * ComponentMain.cpp
 *
 *  Created on: Thursday, 30. January 2014 04:16PM
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

void ComponentMain::handleCamera(const config::VO::sub::Camera& msg)
{
	std::cout<< "VO say:" << msg.data << std::endl;
}
	

void ComponentMain::handleINS(const config::VO::sub::INS& msg)
{
	std::cout<< "VO say:" << msg.data << std::endl;
}
	

void ComponentMain::handleTF(const config::VO::sub::TF& msg)
{
	std::cout<< "VO say:" << msg.data << std::endl;
}
	

void ComponentMain::publishPosAttVel(config::VO::pub::PosAttVel& msg)
{
	_roscomm->publishPosAttVel(msg);
}
	
