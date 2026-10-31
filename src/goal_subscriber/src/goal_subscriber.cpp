#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include <functional>

using std::placeholders::_1;

class GoalSubscriber : public rclcpp::Node {
public:
    GoalSubscriber() : Node("goal_subscriber") {
        goal_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
            "/goal_pose", 10,
            std::bind(&GoalSubscriber::goalCallback, this, _1));
    }

private:
    void goalCallback(const geometry_msgs::msg::PoseStamped::SharedPtr msg) {
        RCLCPP_INFO(this->get_logger(), "Received goal: x=%.2f, y=%.2f", 
                    msg->pose.position.x, msg->pose.position.y);
    }

    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr goal_sub_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<GoalSubscriber>());
    rclcpp::shutdown();
    return 0;
}