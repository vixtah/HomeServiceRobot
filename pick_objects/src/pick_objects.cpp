#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "std_msgs/Bool.h"

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle n;
  ros::Publisher did_reach_goal_pub = n.advertise<std_msgs::Bool>("did_reach_goal", 1000);
  std_msgs::Bool reached;
  reached.data = true;
  
  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = 4.0;
  goal.target_pose.pose.position.y = 3.0;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("Hooray, the base moved 1 meter forward");
    ac.cancelGoal();
    did_reach_goal_pub.publish(reached);
    
    goal.target_pose.pose.position.x = -1.0;
    goal.target_pose.pose.position.y = 0.0;
    goal.target_pose.pose.orientation.w = 4.0;

    ros::Duration(5.0).sleep();
    ac.sendGoal(goal);
    ROS_INFO("Sent new goal");

    ac.waitForResult();
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    	ROS_INFO("Hooray, reached 2nd goal!");
        did_reach_goal_pub.publish(reached);
    } else {
        ROS_INFO("The base failed to move forward 5 meter for some reason");
    }
  }
  else
    ROS_INFO("The base failed to move forward 1 meter for some reason");
  return 0;
}