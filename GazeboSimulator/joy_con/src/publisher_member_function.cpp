// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include "std_msgs/msg/int32.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */
double x, y, z;
int control_mode;
class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher"), count_(0)
  {
    publisher_ = this->create_publisher<geometry_msgs::msg::Vector3>("/ref", 10);
    timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));

    subscription_ = this->create_subscription<sensor_msgs::msg::Joy>(
		    "/joy", 10, std::bind(&MinimalPublisher::topic_callback, this, std::placeholders::_1));
		    
    subscription_1 = this->create_subscription<std_msgs::msg::Int32>(
		    "/control_mode", 10, std::bind(&MinimalPublisher::control_mode_callback, this, std::placeholders::_1));
  }

private:
  void timer_callback()
  { if(control_mode == 0){
    auto message = geometry_msgs::msg::Vector3();
    message.x = x;
    message.y = y;
    message.z = z;
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", std::to_string(message.x).c_str());
    publisher_->publish(message);
  }}

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr publisher_;
  
  size_t count_;

  void topic_callback(const sensor_msgs::msg::Joy & msg) const
    { if(control_mode == 0){
      x += msg.axes[1]/10;
      y += -msg.axes[0]/10;
      z += (- msg.axes[2] + msg.axes[5])/100;
      RCLCPP_INFO(this->get_logger(), "I heard: '%s'", std::to_string(msg.axes[1]).c_str());
    }}
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription_;

  void control_mode_callback(const std_msgs::msg::Int32 & msg) const
    {
      control_mode = msg.data;
      RCLCPP_INFO(this->get_logger(), "I heard: '%s'", std::to_string(msg.data).c_str());
    }
    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_1;

};

int main(int argc, char * argv[])
{
  x = y = z = 0;
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
