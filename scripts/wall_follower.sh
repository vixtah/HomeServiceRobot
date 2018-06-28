#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# xterm  -e  " source /opt/ros/kinetic/setup.bash; roscore" & 
# sleep 5
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=${DIR}/../worlds/myWorld " &
sleep 5
xterm  -e  " roslaunch turtlebot_gazebo gmapping_demo.launch custom_gmapping_launch_file:=${DIR}/../gmapping.launch.xml" &
sleep 5
# xterm  -e  " roslaunch turtlebot_teleop keyboard_teleop.launch" &
xterm -e " rosrun wall_follower wall_follower" &
sleep 5
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch"