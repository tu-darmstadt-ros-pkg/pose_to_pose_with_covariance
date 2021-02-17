#include <ros/ros.h>

#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/PoseStamped.h>

class PoseToPoseCovStamped
{
public:

  PoseToPoseCovStamped()
  {
    ros::NodeHandle nodeHandle("~");

    pose_cov_pub_ = nodeHandle.advertise<geometry_msgs::PoseWithCovarianceStamped>("/pose_cov", 3, false);

    pose_sub_ = nodeHandle.subscribe("/robot_pose", 1, &PoseToPoseCovStamped::poseCallback, this);

    out_msg_.pose.covariance[0] = 0.05;
    out_msg_.pose.covariance[7] = 0.05;
    out_msg_.pose.covariance[14] = 0.05;
    out_msg_.pose.covariance[21] = 0.01;
    out_msg_.pose.covariance[28] = 0.01;
    out_msg_.pose.covariance[35] = 0.01;
  }

  void poseCallback(const geometry_msgs::PoseStampedConstPtr& msg)
  {
    //geometry_msgs::PoseWithCovarianceStamped out_msg;
    out_msg_.pose.pose = msg->pose;
    out_msg_.header = msg->header;

    pose_cov_pub_.publish(out_msg_);
  }

protected:
  ros::Publisher pose_cov_pub_;
  ros::Subscriber pose_sub_;
  
  geometry_msgs::PoseWithCovarianceStamped out_msg_;

};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "pose_to_pose_with_covariance");

  PoseToPoseCovStamped odom_to_pose;

  ros::spin();
  return 0;
}
