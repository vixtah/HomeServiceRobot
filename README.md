# HomeServiceRobot

This project simulates a robot that can perform SLAM to map its environment and utilize the map to navigate and perform simple tasks.

Commands:
- test_slam.sh: utilize SLAM with manual keyboard teleop control to map the environment
- wall_follower.sh: utilize SLAM with autonomously with a wall following algorithm
- test_navigation.sh: plan a path and navigate to any locations on the map
- home_service.sh: navigate and pick up a object at a predetermined location and drop it off at a goal


## Setup Instructions
**Clone the repository**
```
//in the src directory of your catkin workspace
$ git clone https://github.com/vixtah/HomeServiceRobot
$ git submodule init
$ git submodule update
$ cd ..
$ catkin_make
$ source devel/setup.bash
```

## Example
Create custom map in gazebo and use the following to generate a 2D occupancy grid map.
```
./wall_follower.sh
```
Then save the resulting pgm and yaml files and run the navigation script or homeService script:
```
./home_service.sh
```
