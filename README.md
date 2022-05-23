# BTS project
# Implementation of Autonomous Driving System with AgileX Scout-mini gazebo simulator

## For Detailed Simulation Function Package, Refer ugv_gazebo_sim/scout
---
## Install the Gazebo software

Gazebo is  a simulator. Gazebo simulates multiple robots in a 3D environment, with extensive dynamic interaction between objects.

[http://gazebosim.org](http://gazebosim.org/)

Download and install gazebo you can go to the website :http://gazebosim.org/install

------

## 	1.  Environment

<!-- ### Development Environment

​	ubuntu 18.04 + [ROS Melodic desktop full](http://wiki.ros.org/melodic/Installation/Ubuntu) -->

### Development Environment

​	ubuntu 20.04 + [ROS Noetic desktop full](http://wiki.ros.org/noetic/Installation/Ubuntu)


## 2.   Download and install required function package

### For detailed description for installed packages, refer ugv_gazebo_sim/scout

1. ROS melodic

```
sudo apt-get install ros-melodic-ros-control ros-melodic-ros-controllers ros-melodic-gazebo-ros ros-melodic-gazebo-ros-control ros-melodic-joint-state-publisher-gui ros-melodic-teleop-twist-keyboard 
```

2. ROS noetic

```
sudo apt-get install ros-noetic-ros-control ros-noetic-ros-controllers ros-noetic-gazebo-ros ros-noetic-gazebo-ros-control ros-noetic-joint-state-publisher-gui ros-noetic-teleop-twist-keyboard 
```

## 3.	About Usage

### 1.	Create workspace, download simulation model function package and compile

​		Open a new terminal and create a workspace named scout_ws, enter in the terminal:

```
mkdir -p scout_ws/src
```

​		Enter the scout_ws folder

```
cd scout_ws
```

​		Initialize workspace

```
catkin_make
```

​		Enter the src folder

```
cd src
```

​		Download simulation model function package

```
git clone --recursive https://github.com/hjinnkim/BTS_scout_mini.git
```

​		Enter the scout_ws folder

```
cd scout_ws
```

​		Confirm whether the dependency of the function package is installed
```
rosdep install --from-paths src --ignore-src -r -y 
```

​		Compile

```
catkin_make
```



### 2.	Run the star file of scout_v2 and scout_mini, and visualize the urdf file in Rviz

​	Enter the scout_ws folder

```
cd scout_ws
```

​	Declare the environment variable

```
source devel/setup.bash
```

​	Run the start file of scout_v2 model and visualize the model in Rviz

```
roslaunch scout_description display_scout_v2.launch 
```


​	Run the start file of scout_mini model and visualize the model in Rviz

```
roslaunch scout_description display_scout_mini.launch 
```
 

### 3.	Start the gazebo simulation environment of scout_v2 and scout_mini and control scout_v2 and scout_mini movement in the gazebo

​	Enter the scout_ws folder

```
cd scout_ws
```

​	Declare the environment variable

```
source devel/setup.bash
```

​	Start the simulation environment of scout_v2

```
roslaunch scout_gazebo_sim scout_empty_world.launch
```


#Control by keyboard, the scout2.0 and scout_mini can be controlled to move forward, left, right and backward through "i", "j", "l",and "," on the keyboard

```
rosrun teleop_twist_keyboard teleop_twist_keyboard.py 
```


​	Start the simulation environment of scout_mini

```
roslaunch scout_gazebo_sim scout_mini_playpen.launch
```

#Control by keyboard, the scout2.0 and scout_mini can be controlled to move forward, left, right and backward through "i", "j", "l",and "," on the keyboard

```
rosrun teleop_twist_keyboard teleop_twist_keyboard.py 
```

---
## 4.   Sensors
### Add LiDAR
#### Reference

* https://www.youtube.com/watch?v=jJzzw2jk-lY

* https://classic.gazebosim.org/tutorials?tut=ros_gzplugins#GPULaser

* https://level-asphalt-6c6.notion.site/Gazebo-Scout-mini-add-lidar-086c23578e904467864f284ad02c8564

* hokuyo.dae : https://github.com/osrf/gazebo_models/tree/master/hokuyo/meshes


### Add realsense camera
#### Reference

* https://github.com/pal-robotics/realsense_gazebo_plugin

* https://github.com/pal-robotics/realsense_gazebo_plugin/issues/7

* https://github.com/IntelRealSense/realsense-ros

* urdf : https://github.com/IntelRealSense/realsense-ros/tree/development/realsense2_description/urdf

* d435.dae : https://github.com/IntelRealSense/realsense-ros/tree/development/realsense2_description/meshes

#### If compressed image topics are not published, try to install following ros packages where '<'distribution'>' is your ros-distro
```
sudo apt install ros-<distribution>-image-transport-plugins ros-<distribution>-compressed-image-transport ros-<distribution>-theora-image-transport ros-<distribution>-compressed-depth-image-transport
```

---

