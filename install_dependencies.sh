#!/bin/sh

# slam-gmapping package download
# Reference site : https://aur.archlinux.org/packages/ros-noetic-slam-gmapping
# Reference site : https://aur.archlinux.org/packages/ros-noetic-openslam-gmapping
mkdir slam-gmapping
cd slam-gmapping

wget https://github.com/ros-perception/slam_gmapping/archive/1.4.1.tar.gz -O ros-noetic-slam-gmapping-1.4.1.tar.gz
wget https://github.com/ros-perception/openslam_gmapping/archive/0.2.1.tar.gz -O ros-noetic-openslam-gmapping-0.2.1.tar.gz

tar -xvf ros-noetic-slam-gmapping-1.4.1.tar.gz
tar -xvf ros-noetic-openslam-gmapping-0.2.1.tar.gz

cd ..

