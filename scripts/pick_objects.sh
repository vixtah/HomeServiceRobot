#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=${DIR}/../worlds/myWorld " &
sleep 5
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=${DIR}/../worlds/my_map.yaml" &
sleep 5
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm  -e  " rosrun pick_objects pick_objects"
