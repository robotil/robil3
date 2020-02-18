# What?
This project is called ROBIL3 and its goal is todevelop cooperation between robots.
It comes from https://github.com/iosp/robil2 branch robil3.
The robot is a bobcat running with a simulative world in Unity.
The simulation is in:
 https://github.com/robotil/RobilSimulation/tree/2019.2.17
 
# Install:
Branch **master**: 
1. Clone this repository
2. Init catkin workspace: catkin init
3. Compile catkin build
4. You may need to install python-catkin-tools: https://catkin-tools.readthedocs.io/en/latest/installing.html

# Run robot

## First: run rosbridge:
 roslaunch roslaunch rosbridge_server rosbridge_websocket.launch
 
## At this step, 
you need to run the simulation first: https://github.com/robotil/RobilSimulation/blob/2019.2.17/README.txt
 
## Run ROBIL3:
roslaunch robil2conf frameworkUnity.launch

## Run OCU
Open the file: $ROBIL3/src/Framework/ocu/src/RobilOCU.html on a browser.
Note You have to refresh the OCU each time the robot reboots.

