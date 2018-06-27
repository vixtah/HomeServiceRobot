#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "std_msgs/Bool.h"

bool hasPickedUp = false;

ros::Publisher marker_pub;
ros::Subscriber did_reach_goal_sub;
visualization_msgs::Marker marker;

visualization_msgs::Marker createMarker(float x, float y) {
  uint32_t shape = visualization_msgs::Marker::CUBE;

  visualization_msgs::Marker marker;
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();
  marker.ns = "basic_shapes";
  marker.id = 0;
  marker.type = shape;
  marker.action = visualization_msgs::Marker::ADD;
  
  marker.pose.position.x = x;
  marker.pose.position.y = y;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

  marker.scale.x = 0.5;
  marker.scale.y = 0.5;
  marker.scale.z = 0.5;

  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;

  marker.lifetime = ros::Duration();
  
  return marker;
}

void didReachGoalCallback(const std_msgs::Bool::ConstPtr& msg)
{
  ROS_INFO("Goal Reached");
  if (!hasPickedUp) 
  {
    ROS_INFO("Hiding marker");
    marker.color.a = 0;
    marker_pub.publish(marker);
	hasPickedUp = true;
  } 
  else 
  {
    ROS_INFO("Dropping off marker");
    marker = createMarker(-1, 0);
    marker_pub.publish(marker);
  }
}

// %Tag(INIT)%
int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  did_reach_goal_sub = n.subscribe("did_reach_goal", 1000, didReachGoalCallback);
  
//   visualization_msgs::Marker marker;
  
  if (ros::ok) {
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    marker = createMarker(4, 3);
    ROS_INFO("Showing marker to pick up");
    marker_pub.publish(marker);
  }
  ros::spin();
//   while(ros::ok() && !goalReached) { 
//     ROS_INFO("Waiting");
//     sleep(1); 
//   }
//   ROS_INFO("Hiding marker");
//   marker.color.a = 0;
//   marker_pub.publish(marker);
//   goalReached = false;
  
//   while(ros::ok() && !goalReached) { sleep(1); }
//   ROS_INFO("Dropping off marker");
//   marker = createMarker(-1, 0);
//   marker_pub.publish(marker);
//   goalReached = false;
  
}
