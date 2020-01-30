# What?
This project is called ROBIL3 and its goal is todevelop cooperation between robots.
It comes from https://github.com/iosp/robil2 branch robil3.
The robot is a bobcat running with a simulative world in Unity.
The simulation is in:
 https://github.com/robotil/RobilSimulation/tree/2019.2.17
 
# Install:
Branch **master**: 
1. Before we clone and compile the new robil3 workspace it is required to clean the environment.
   Every time we launch the Termimal it is already defined to work in the robil2 environment (as defined in .bashrc file).
   Remove any source command of robil 2 from the .bashrc file. Now you may proceed.
2. Clone the repository 
3. Init catkin workspace: catkin init
4. Compile catkin build
5. You may need to install python-catkin-tools: https://catkin-tools.readthedocs.io/en/latest/installing.html

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


