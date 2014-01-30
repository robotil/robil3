
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
	void handleExecuteWorkSequenceCommand(const config::WSM::sub::ExecuteWorkSequenceCommand& msg);
	void handlePosAttVel(const config::WSM::sub::PosAttVel& msg);
	void handleWiresLengths(const config::WSM::sub::WiresLengths& msg);
	void publishBladePosition(config::WSM::pub::BladePosition& msg);
	void publishTrottleEffort(config::WSM::pub::TrottleEffort& msg);
	void publishSteeringEffort(config::WSM::pub::SteeringEffort& msg);
	void publishJointsEffort(config::WSM::pub::JointsEffort& msg);
};
#endif /* COMPONENTMAIN_H_ */
