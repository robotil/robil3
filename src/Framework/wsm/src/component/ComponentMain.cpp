
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

void ComponentMain::handleExecuteWorkSequenceCommand(const config::WSM::sub::ExecuteWorkSequenceCommand& msg)
{
	std::cout<< "WSM say:" << msg << std::endl;
}
	

void ComponentMain::handlePosAttVel(const config::WSM::sub::PosAttVel& msg)
{
	std::cout<< "WSM say:" << msg << std::endl;
}
	

void ComponentMain::handleWiresLengths(const config::WSM::sub::WiresLengths& msg)
{
	std::cout<< "WSM say:" << msg << std::endl;
}
	

void ComponentMain::publishBladePosition(config::WSM::pub::BladePosition& msg)
{
	_roscomm->publishBladePosition(msg);
}
	

void ComponentMain::publishTrottleEffort(config::WSM::pub::TrottleEffort& msg)
{
	_roscomm->publishTrottleEffort(msg);
}
	

void ComponentMain::publishSteeringEffort(config::WSM::pub::SteeringEffort& msg)
{
	_roscomm->publishSteeringEffort(msg);
}
	

void ComponentMain::publishJointsEffort(config::WSM::pub::JointsEffort& msg)
{
	_roscomm->publishJointsEffort(msg);
}
	
