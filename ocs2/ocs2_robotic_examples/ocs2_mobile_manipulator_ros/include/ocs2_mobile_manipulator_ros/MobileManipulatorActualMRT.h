#include <ocs2_mobile_manipulator/MobileManipulatorInterface.h>

#include <ocs2_mobile_manipulator_ros/MobileManipulatorDummyVisualization.h>

#include <ocs2_mpc/SystemObservation.h>
#include <ocs2_ros_interfaces/mrt/MRT_ROS_Dummy_Loop.h>
#include <ocs2_ros_interfaces/mrt/MRT_ROS_Interface.h>

#include <ros/init.h>
#include <ros/package.h>
#include "ocs2_ros_interfaces/common/RosMsgConversions.h"
#include <ocs2_mpc/SystemObservation.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include "ocs2_core/reference/TargetTrajectories.h"

typedef Eigen::Matrix<double, 6, 1> Vector6d;

namespace ocs2 {
namespace mobile_manipulator {

class ActualMRT
{
public:
  ActualMRT(ros::NodeHandle &n);
  void base_odometry_callback(const nav_msgs::Odometry& slam_odom);
  void arm_joint_state_callback(const geometry_msgs::Twist& arm_joint);
  void mpc_policy_callback(const ocs2_msgs::mpc_flattened_controller& msg);
  void fusion(SystemObservation& fused_observation);
  void publish_everything();
  void run();
  void reset(const TargetTrajectories& initTargetTrajectories);

public:
  ros::NodeHandle n_;
  ros::Subscriber sub_base_state_;
  ros::Subscriber sub_arm_state_;
  ros::Subscriber sub_policy_;
  ros::Publisher pub_base_command_;
  ros::Publisher pub_arm_command_;
  ros::Publisher pub_observation_;

  ros::ServiceClient mpcResetServiceClient_;
  
  
  geometry_msgs::Twist base_command_;
  geometry_msgs::Twist arm_command_;
  ocs2_msgs::mpc_observation mpcObservationMsg_;

  Eigen::Vector3d base_map_translation_;
  double theta_;
  Eigen::Quaterniond base_map_orientation_;
  Vector6d arm_joint_state_;

};



}  // namespace mobile_manipulator
}  // namespace ocs2