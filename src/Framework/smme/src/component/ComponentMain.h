
/*
 * ComponentMain.h
 *
 *  Created on: Thursday, 27. February 2014 12:29PM
 *      Author: autogenerated
 */
#ifndef COMPONENTMAIN_H_
#define COMPONENTMAIN_H_
#include <std_msgs/String.h>
#include <ParameterTypes.h>
#include <tf/tf.h>
#include <boost/thread.hpp>

class RosComm;
class MissionManager;
namespace decision_making{ class EventQueue; }

class ComponentMain {
	RosComm* _roscomm;
	MissionManager* _mission_manager;
	boost::thread_group threads;
	decision_making::EventQueue* _events;
public:
	ComponentMain(int argc,char** argv);
	virtual ~ComponentMain();
	void handleAssignNavTask(const config::SMME::sub::AssignNavTask& msg);
	void handleAssignManTask(const config::SMME::sub::AssignManTask& msg);
	void handleAssignMission(const config::SMME::sub::AssignMission& msg);
	void handleBladePosition(const config::SMME::sub::BladePosition& msg);
	void handleLocation(const config::SMME::sub::Location& msg);
	void handleIEDLocation(const config::IEDSIM::pub::IEDLocation& msg);
	void publishGlobalPath(config::SMME::pub::GlobalPath& msg);
	void publishWorkSeqData(config::SMME::pub::WorkSeqData& msg);
	void publishMissionAcceptance(config::SMME::pub::MissionAcceptance& msg);
	void publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame);
	tf::StampedTransform getLastTrasform(std::string srcFrame, std::string distFrame);
	void publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report);
	void publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report);

	MissionManager * const mission_manager(){return _mission_manager;}

	void set_events(decision_making::EventQueue* e){ _events = e; }
	decision_making::EventQueue* events()const{ return _events; }
};
#endif /* COMPONENTMAIN_H_ */
