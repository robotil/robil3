
/*
 * ComponentMain.h
 *
 *  Created on: Wednesday, 19. February 2014 04:26PM
 *      Author: autogenerated
 */
#ifndef COMPONENTMAIN_H_
#define COMPONENTMAIN_H_
#include <std_msgs/String.h>
#include <ParameterTypes.h>
#include <tf/tf.h>
class RosComm;
class ComponentMain {
	RosComm* _roscomm;
public:
	ComponentMain(int argc,char** argv);
	virtual ~ComponentMain();
	void handlePerVelocity(const config::PER::sub::PerVelocity& msg);
	void handleLocation(const config::PER::sub::Location& msg);
	void handleSensorINS(const config::PER::sub::SensorINS& msg);
	void handleSensorGPS(const config::PER::sub::SensorGPS& msg);
	void handleSensorCamL(const config::PER::sub::SensorCamL& msg);
	void handleSensorCamR(const config::PER::sub::SensorCamR& msg);
	void handleSensorWire(const config::PER::sub::SensorWire& msg);
	void handleSensorSICK(const config::PER::sub::SensorSICK& msg);
	void handleSensorIBEO1(const config::PER::sub::SensorIBEO1& msg);
	void handleSensorIBEO2(const config::PER::sub::SensorIBEO2& msg);
	void handleSensorIBEO3(const config::PER::sub::SensorIBEO3& msg);
	void handleSensorIBEO4(const config::PER::sub::SensorIBEO4& msg);
	void handleEffortsTh(const config::PER::sub::EffortsTh& msg);
	void handleEffortsSt(const config::PER::sub::EffortsSt& msg);
	void handleEffortsJn(const config::PER::sub::EffortsJn& msg);
	void publishGPS(config::PER::pub::GPS& msg);
	void publishINS(config::PER::pub::INS& msg);
	void publishBladePosition(config::PER::pub::BladePosition& msg);
	void publishMap(config::PER::pub::Map& msg);
	void publishMiniMap(config::PER::pub::MiniMap& msg);
	void publishVOOdometry(config::PER::pub::VOOdometry& msg);
	void publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame);
	tf::StampedTransform getLastTrasform(std::string srcFrame, std::string distFrame);
	void publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report);
	void publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report);
};
#endif /* COMPONENTMAIN_H_ */
