
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

void ComponentMain::handleMap(const config::PP::sub::Map& msg)
{
	std::cout<< "PP say:" << msg << std::endl;
}
	

void ComponentMain::handleMissionGlobalPath(const config::PP::sub::MissionGlobalPath& msg)
{
	std::cout<< "PP say:" << msg << std::endl;
}
	

void ComponentMain::handleIEDPosAtt(const config::PP::sub::IEDPosAtt& msg)
{
	std::cout<< "PP say:" << msg << std::endl;
}
	

void ComponentMain::handlePosAttVel(const config::PP::sub::PosAttVel& msg)
{
	std::cout<< "PP say:" << msg << std::endl;
}
	

void ComponentMain::publishLocalPathPlan(config::PP::pub::LocalPathPlan& msg)
{
	_roscomm->publishLocalPathPlan(msg);
}
	
