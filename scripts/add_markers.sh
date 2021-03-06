#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=${DIR}/../worlds/myWorld " &
sleep 5
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=${DIR}/../worlds/my_map.yaml" &
sleep 5
xterm  -e  " rosrun rviz rviz -d ${DIR}/../config/default.rviz" &
sleep 5
xterm  -e  " rosrun add_markers add_markers_delay"
