#!/bin/sh

# Install package scout-gazebo simulation dependencies
sudo apt-get install libasio-dev ros-noetic-ros-control ros-noetic-ros-controllers ros-noetic-gazebo-ros ros-noetic-gazebo-ros-control ros-noetic-joint-state-publisher-gui ros-noetic-teleop-twist-keyboard -y

# slam-gmapping package download
# Reference site : http://wiki.ros.org/gmapping
# Reference site : https://aur.archlinux.org/packages/ros-noetic-slam-gmapping
# Reference site : https://aur.archlinux.org/packages/ros-noetic-openslam-gmapping
mkdir slam-gmapping
cd slam-gmapping

wget https://github.com/ros-perception/slam_gmapping/archive/1.4.1.tar.gz -O ros-noetic-slam-gmapping-1.4.1.tar.gz
wget https://github.com/ros-perception/openslam_gmapping/archive/0.2.1.tar.gz -O ros-noetic-openslam-gmapping-0.2.1.tar.gz

tar -xvf ros-noetic-slam-gmapping-1.4.1.tar.gz
tar -xvf ros-noetic-openslam-gmapping-0.2.1.tar.gz

cd ..

# ROS navigation package download
# Reference site : http://wiki.ros.org/navigation
# Reference site : https://github.com/ros-planning/navigation

git clone -b noetic-devel https://github.com/ros-planning/navigation.git

# robot_localization package download
# Reference site : http://wiki.ros.org/robot_localization
# Reference site : https://github.com/cra-ros-pkg/robot_localization

git clone -b noetic-devel https://github.com/cra-ros-pkg/robot_localization.git

# To use gazebo_models_worlds_collection
echo 'export GAZEBO_MODEL_PATH=$GAZEBO_MODEL_PATH:'"$(pwd)/ugv_gazebo_sim/gazebo_models_worlds_collection/models" >> ~/.bashrc
echo 'export GAZEBO_RESOURCE_PATH=$GAZEBO_RESOURCE_PATH:'"$(pwd)/ugv_gazebo_sim/gazebo_models_worlds_collection/worlds" >> ~/.bashrc