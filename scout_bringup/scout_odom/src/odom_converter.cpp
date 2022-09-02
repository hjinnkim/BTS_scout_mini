#include "odom_converter.hpp"
// #include <tf/transform_broadcaster.h>

#include <random>

double add_gaussian_noise(const double& variance_, const double& mean_ = 0){
    double sigma = sqrt(variance_);

    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<> d{mean_, sigma};
    
    double noise = d(gen);

    return noise;
}

tf2::Quaternion add_gaussian_noise_quat(const double variance_[3], const double& mean_ = 0){
    double angle_v[3];
    angle_v[0] = add_gaussian_noise(variance_[0]);
    angle_v[1] = add_gaussian_noise(variance_[1]);
    angle_v[2] = add_gaussian_noise(variance_[2]);

    tf2::Quaternion quat_tf;
    quat_tf.setRPY(angle_v[0], angle_v[1], angle_v[2]);

    return quat_tf;
}

OdomConverter::OdomConverter(ros::NodeHandle *nh, double initial_x, double initial_y, double initial_z, double initial_yaw) : nh_(nh), initial_x_(initial_x), initial_y_(initial_y), initial_z_(initial_z), initial_yaw_(initial_yaw){}

void OdomConverter::SetupSubscription(){
    odom_publisher_ = nh_->advertise<nav_msgs::Odometry>(odom_topic_name_, 50);
    odom_subscriber_= nh_->subscribe<nav_msgs::Odometry>(odom_groundtruth_topic_name_, 5, &OdomConverter::OdomCallback, this);
    odom_init_ = false;

    initial_quat_.setRPY(0., 0., initial_yaw_);
}

void OdomConverter::OdomCallback(const nav_msgs::Odometry::ConstPtr& msg){
    std::lock_guard<std::mutex> guard(odom_mutex_);
    odom_groudtruth_ = *msg.get();
    if(!odom_init_){
        linear_covariance_[0] = odom_groudtruth_.pose.covariance[0];
        linear_covariance_[1] = odom_groudtruth_.pose.covariance[7];
        // linear_covariance_[2] = odom_groudtruth_.pose.covariance[14];
        angular_covariance_[0] = odom_groudtruth_.pose.covariance[21];
        angular_covariance_[1] = odom_groudtruth_.pose.covariance[28];
        angular_covariance_[2] = odom_groudtruth_.pose.covariance[35];
        odom_init_ = true;
        return;
    }
}

void OdomConverter::PublishOdometry(){
    std::lock_guard<std::mutex> guard(odom_mutex_);
    if(!odom_init_) return;

    ros::Time current_time = ros::Time::now();

    if(add_noise){
        linear_error_accumulate_[0] += add_gaussian_noise(linear_covariance_[0]);
        linear_error_accumulate_[1] += add_gaussian_noise(linear_covariance_[1]);

        tf2::Quaternion orientation_error = add_gaussian_noise_quat(angular_covariance_);
        orientation_error_accumulate_[0] += orientation_error.getX();
        orientation_error_accumulate_[1] += orientation_error.getY();
        orientation_error_accumulate_[2] += orientation_error.getZ();
    }

    nav_msgs::Odometry odom_msg(odom_groudtruth_);
    odom_msg.header.stamp = current_time;
    odom_msg.header.frame_id = odom_frame_;
    odom_msg.child_frame_id = base_frame_;

    odom_msg.pose.pose.position.x += (linear_error_accumulate_[0] - initial_x_);
    odom_msg.pose.pose.position.y += (linear_error_accumulate_[1] - initial_y_);

    odom_msg.pose.pose.orientation.x += (orientation_error_accumulate_[0] - initial_quat_.getX());
    odom_msg.pose.pose.orientation.y += (orientation_error_accumulate_[1] - initial_quat_.getY());
    odom_msg.pose.pose.orientation.z += (orientation_error_accumulate_[2] - initial_quat_.getZ());

    if(pub_tf){
        geometry_msgs::TransformStamped tf_msg;
        tf_msg.header = odom_msg.header;
        tf_msg.child_frame_id = base_frame_;

        tf_msg.transform.translation.x = odom_msg.pose.pose.position.x;
        tf_msg.transform.translation.y = odom_msg.pose.pose.position.y;
        tf_msg.transform.translation.z = odom_msg.pose.pose.position.z;

        tf_msg.transform.rotation = odom_msg.pose.pose.orientation;

        tf_broadcaster_.sendTransform(tf_msg);
    }
    odom_publisher_.publish(odom_msg);
}

