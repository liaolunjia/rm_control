//
// Created by ljq on 2021/12/3.
//

#pragma once

#include <rm_common/ros_utilities.h>
#include <ros/timer.h>
#include <rm_common/decision/command_sender.h>

#include "rm_referee/ui/ui_base.h"
#include "rm_referee/ui/trigger_change_ui.h"
#include "rm_referee/ui/time_change_ui.h"
#include "rm_referee/ui/flash_ui.h"

namespace rm_referee
{
class RefereeBase
{
public:
  explicit RefereeBase(ros::NodeHandle& nh, Base& base);
  virtual void addUi();

  // unpack call back
  virtual void robotStatusDataCallBack(const rm_msgs::GameRobotStatus& game_robot_status_data,
                                       const ros::Time& last_get_data_time);
  virtual void gameStatusDataCallBack(const rm_msgs::GameStatus& game_status_data, const ros::Time& last_get_data_time);
  virtual void capacityDataCallBack(const rm_msgs::CapacityData& capacity_data, ros::Time& last_get_data_time);
  virtual void powerHeatDataCallBack(const rm_msgs::PowerHeatData& power_heat_data, const ros::Time& last_get_data_time);
  virtual void robotHurtDataCallBack(const rm_msgs::RobotHurt& robot_hurt_data, const ros::Time& last_get_data_time);
  virtual void interactiveDataCallBack(const rm_referee::InteractiveData& interactive_data,
                                       const ros::Time& last_get_data_time);
  virtual void eventDataCallBack(const rm_msgs::EventData& event_data, const ros::Time& last_get_data_time);

  // sub call back
  virtual void jointStateCallback(const sensor_msgs::JointState::ConstPtr& joint_state);
  virtual void actuatorStateCallback(const rm_msgs::ActuatorState::ConstPtr& data);
  virtual void dbusDataCallback(const rm_msgs::DbusData::ConstPtr& data);
  virtual void chassisCmdDataCallback(const rm_msgs::ChassisCmd::ConstPtr& data);
  virtual void vel2DCmdDataCallback(const geometry_msgs::Twist::ConstPtr& data);
  virtual void shootStateCallback(const rm_msgs::ShootState::ConstPtr& data);
  virtual void gimbalCmdDataCallback(const rm_msgs::GimbalCmd::ConstPtr& data);
  virtual void cardCmdDataCallback(const rm_msgs::StateCmd::ConstPtr& data);
  virtual void engineerUiDataCallback(const rm_msgs::EngineerUi::ConstPtr& data);
  virtual void manualDataCallBack(const rm_msgs::ManualToReferee::ConstPtr& data);
  virtual void radarDataCallBack(const std_msgs::Int8MultiArrayConstPtr& data);
  virtual void cameraNameCallBack(const std_msgs::StringConstPtr& data);

  ros::Subscriber joint_state_sub_;
  ros::Subscriber actuator_state_sub_;
  ros::Subscriber dbus_sub_;
  ros::Subscriber chassis_cmd_sub_;
  ros::Subscriber vel2D_cmd_sub_;
  ros::Subscriber shoot_state_sub_;
  ros::Subscriber gimbal_cmd_sub_;
  ros::Subscriber detection_status_sub_;
  ros::Subscriber card_cmd_sub_;
  ros::Subscriber calibration_status_sub_;
  ros::Subscriber engineer_cmd_sub_;
  ros::Subscriber radar_date_sub_;
  ros::Subscriber manual_data_sub_;
  ros::Subscriber camera_name_sub_;

  ChassisTriggerChangeUi* chassis_trigger_change_ui_{};
  ShooterTriggerChangeUi* shooter_trigger_change_ui_{};
  GimbalTriggerChangeUi* gimbal_trigger_change_ui_{};
  TargetTriggerChangeUi* target_trigger_change_ui_{};
  CameraTriggerChangeUi* camera_trigger_change_ui_{};

  CapacitorTimeChangeUi* capacitor_time_change_ui_{};
  EffortTimeChangeUi* effort_time_change_ui_{};
  ProgressTimeChangeUi* progress_time_change_ui_{};
  DartStatusTimeChangeUi* dart_status_time_change_ui_{};
  LaneLineTimeChangeUi* lane_line_time_change_ui_{};

  FixedUi* fixed_ui_{};

  CoverFlashUi* cover_flash_ui_{};
  SpinFlashUi* spin_flash_ui_{};

  Base& base_;
  ros::Timer add_ui_timer_;
  int add_ui_times_ = 0;
  bool add_ui_flag_ = false;
  Graph* interactive_data_sender_;
  ros::NodeHandle nh_;
};
}  // namespace rm_referee
