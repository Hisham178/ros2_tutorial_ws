#ifndef rqt_tutorial_1_HPP_
#define rqt_tutorial_1_HPP_

// QT headers
#include <QtCore/QTimer>
#include <QtConcurrent/QtConcurrent>

#include "rqt_gui_cpp/plugin.h"
#include "geometry_msgs/msg/twist.hpp"

#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

#include <qwt_dial_needle.h>

#include "ui_odometer.h"

using namespace std;

using std::placeholders::_1;

namespace rqt_tutorial_1
{
/**
 * @brief A RQT instance, to control and visualize robot states conviniently
 *
 */
class Dashboard : public rqt_gui_cpp::Plugin
{
  Q_OBJECT

public:
  Dashboard();

  ~Dashboard();

  virtual void initPlugin(qt_gui_cpp::PluginContext& context);

  virtual void shutdownPlugin();

protected slots:

  virtual void teleoperation();
  virtual void twist_callback(geometry_msgs::msg::Twist::SharedPtr);

private:
  Dashboard* cp;

signals:

protected:
  // GUI designed in QT Designer, automatically created from .ui file
  Ui::Odometer ui_;

  // QT widget instance
  QPointer<QWidget> widget_;
  // RCLCPP node
  rclcpp::Node::SharedPtr node_;
  // ROS2 oublisher to publish velocity commands , for maual robot jogging
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_publisher_;
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_subscriber_;

  rclcpp::Time time_now = rclcpp::Clock().now();

  // QT timer to update robot states and publish velocity commands(if user is doing manual jog)
  QPointer<QTimer> timer_;
  // A timer used to check on the completion status of the action
  QPointer<QTimer> basic_timer_;
};

}  // namespace rqt_tutorial_1

#endif  // rqt_tutorial_1_HPP
