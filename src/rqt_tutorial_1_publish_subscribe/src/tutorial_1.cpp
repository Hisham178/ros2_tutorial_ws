#include "pluginlib/class_list_macros.hpp"
#include "rqt_tutorial_1_publish_subscribe/tutorial_1.hpp"

#include <qwt_dial_needle.h>
#include <QtGui>

using namespace std::chrono_literals;

namespace rqt_tutorial_1_publish_subscribe
{
Dashboard::Dashboard() : rqt_gui_cpp::Plugin(), widget_(0)
{
  setObjectName("ROS2 RQT");
}

Dashboard::~Dashboard()
{
  shutdownPlugin();
}

void Dashboard::initPlugin(qt_gui_cpp::PluginContext& context)
{
  widget_ = new QWidget();

  timer_ = new QTimer(widget_);

  basic_timer_ = new QTimer(widget_);

  node_ = rclcpp::Node::make_shared("control_plugin_rclcpp_node");

  ui_.setupUi(widget_);

  context.addWidget(widget_);

  rclcpp::QoS qos(1);
  qos.reliability(RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT);
  qos.durability(RMW_QOS_POLICY_DURABILITY_VOLATILE);
  timer_->start(30);
  timer_->connect(timer_, SIGNAL(timeout()), this, SLOT(teleoperation()));
  cmd_vel_publisher_ = node_->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 1);

  cmd_vel_subscriber_ = node_->create_subscription<geometry_msgs::msg::Twist>(
      "/cmd_vel", 1, std::bind(&Dashboard::twist_callback, this, std::placeholders::_1));
}

void Dashboard::teleoperation()
{
  geometry_msgs::msg::Twist twist;

  ui_.speed->setScaleArc(30, 330);
  ui_.speed->setLineWidth(3);
  QwtDialSimpleNeedle* nd = new QwtDialSimpleNeedle(QwtDialSimpleNeedle::Arrow, true, Qt::red, Qt::black);
  QwtDialSimpleNeedle* nd2 = new QwtDialSimpleNeedle(QwtDialSimpleNeedle::Arrow, true, Qt::red, Qt::black);

  ui_.speed->setNeedle(nd);
  ui_.steering->setNeedle(nd2);

  // Update the Twist message
  twist.linear.x = ui_.Slider_Speed->value();
  twist.angular.z = ui_.Slider_LR->value();
  ;

  cmd_vel_publisher_->publish(twist);
  rclcpp::spin_some(node_);
}

void Dashboard::shutdownPlugin()
{
  delete widget_;
  delete timer_;
  delete basic_timer_;
}

void Dashboard::twist_callback(geometry_msgs::msg::Twist::SharedPtr msg)
{
  geometry_msgs::msg::Twist twist;

  // Update the Twist message
  twist.linear.x = msg->linear.x;
  twist.angular.z = msg->angular.z;

  double value1 = twist.linear.x;
  double value2 = twist.angular.z;

  if (value1 < 0)
  {
    value1 = (-1) * value1;
  }

  QString s = QString::number(value1, 'f', 2);
  ui_.linear_x->clear();
  ui_.linear_x->setText(s + " m/s");

  QString turning = QString::number(value2, 'f', 2);
  ui_.angular_z->clear();
  ui_.angular_z->setText(turning + " r/s");

  ui_.speed->setValue(value1);
  ui_.steering->setValue(value2);
}

}  // namespace rqt_tutorial_1_publish_subscribe
PLUGINLIB_EXPORT_CLASS(rqt_tutorial_1_publish_subscribe::Dashboard, rqt_gui_cpp::Plugin)
