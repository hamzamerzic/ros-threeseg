#include <string>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char** argv) {
  ros::init(argc, argv, "state_publisher_threeseg");
  ros::NodeHandle n;
  ros::Publisher joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
  tf::TransformBroadcaster broadcaster;
  ros::Rate loop_rate(3);

  // Robot state
  double joint1 = 1.0, joint2 = -1.0, joint3 = 0;

  // State change
  double j1_inc = -0.1, j2_inc = 0.1;

  // Message declarations
  geometry_msgs::TransformStamped odom_trans;
  sensor_msgs::JointState joint_state;
  odom_trans.header.frame_id = "world";
  odom_trans.child_frame_id = "base";
  broadcaster.sendTransform(odom_trans);

  // Define joint state
  joint_state.name.resize(3);
  joint_state.position.resize(3);
  joint_state.name[0] ="joint1";
  joint_state.name[1] ="joint2";
  joint_state.name[2] ="joint3";

  while (ros::ok()) {
    // Update joint_state
    joint_state.header.stamp = ros::Time::now();
    joint_state.position[0] = joint1;
    joint_state.position[1] = joint2;
    joint_state.position[2] = joint3;

    // Send the joint state and transform
    joint_pub.publish(joint_state);

    // Change joint state
    if (joint1 > 1.0 || joint1 < 0) j1_inc *= -1;
    if (joint2 < -1.0 || joint2 > 0) j2_inc *= -1;
    joint1 += j1_inc;
    joint2 += j2_inc;

    // This will adjust as needed per iteration
    loop_rate.sleep();
  }
  return 0;
}