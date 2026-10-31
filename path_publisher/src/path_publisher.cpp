#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/path.hpp"
#include <chrono>

using namespace std::chrono_literals;

class PathPublisher : public rclcpp::Node {
public:
    PathPublisher() : Node("path_publisher") {
        path_pub_ = this->create_publisher<nav_msgs::msg::Path>("/jps_plan", 10);
        timer_ = this->create_wall_timer(1s, std::bind(&PathPublisher::timer_callback, this));
    }

private:
    void timer_callback() {
        auto path_msg = nav_msgs::msg::Path();
        path_msg.header.frame_id = "map";
        path_pub_->publish(path_msg);
        RCLCPP_INFO(this->get_logger(), "Publishing path...");
    }

    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr path_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PathPublisher>());
    rclcpp::shutdown();
    return 0;
}