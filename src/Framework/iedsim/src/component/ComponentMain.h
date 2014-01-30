
/*
 * ComponentMain.h
 *
 *  Created on: Thursday, 30. January 2014 06:41PM
 *      Author: autogenerated
 */
#ifndef COMPONENTMAIN_H_
#define COMPONENTMAIN_H_
#include <std_msgs/String.h>
#include <ParameterTypes.h>
class RosComm;
class ComponentMain {
	RosComm* _roscomm;
public:
	ComponentMain(int argc,char** argv);
	virtual ~ComponentMain();
	void handleIEDDetectionEvent(const config::IEDSIM::sub::IEDDetectionEvent& msg);
	void handleIEDLocation(const config::IEDSIM::sub::IEDLocation& msg);
	void publishIEDDetectionEvent(config::IEDSIM::pub::IEDDetectionEvent& msg);
	void publishIEDLocation(config::IEDSIM::pub::IEDLocation& msg);
};
#endif /* COMPONENTMAIN_H_ */
