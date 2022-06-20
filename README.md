# **BTS project**
# Implementation of Autonomous Driving System with AgileX Scout-mini gazebo simulator

## **0.   Install the Gazebo software**

Gazebo is  a simulator. Gazebo simulates multiple robots in a 3D environment, with extensive dynamic interaction between objects.

[http://gazebosim.org](http://gazebosim.org/)

Download and install gazebo you can go to the website :http://gazebosim.org/install

------

## 	**1.  Environment**

<!-- ### Development Environment

​	ubuntu 18.04 + [ROS Melodic desktop full](http://wiki.ros.org/melodic/Installation/Ubuntu) -->

### Development Environment

​	ubuntu 20.04 + [ROS Noetic desktop full](http://wiki.ros.org/noetic/Installation/Ubuntu)


## **2.   Download and install required function package**

### *For detailed description for installed packages, refer ugv_gazebo_sim/scout/README.md*

1. ROS melodic

    ```
    sudo apt-get install libasio-dev ros-melodic-ros-control ros-melodic-ros-controllers ros-melodic-gazebo-ros ros-melodic-gazebo-ros-control ros-melodic-joint-state-publisher-gui ros-melodic-teleop-twist-keyboard ros-melodic-navigation ros-melodic-gmapping
    ```

2. ROS noetic

    ```
    sudo apt-get install libasio-dev ros-noetic-ros-control ros-noetic-ros-controllers ros-noetic-gazebo-ros ros-noetic-gazebo-ros-control ros-noetic-joint-state-publisher-gui ros-noetic-teleop-twist-keyboard ros-noetic-navigation ros-noetic-gmapping
    ```

## **3.	About Usage**

### 1.	Create workspace, download simulation model function package and compile

​		Open a new terminal and create a workspace named scout_ws, enter in the terminal:

```
mkdir -p scout_ws/src
```

​		Enter the scout_ws folder

```
cd ~/scout_ws/src
```

​		Download simulation model function package

```
git clone --recursive https://github.com/hjinnkim/BTS_scout_mini.git
```

​		Enter the scout_ws folder

```
cd ~/scout_ws
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

​	Start the simulation environment of scout_mini

```
roslaunch scout_gazebo_sim scout_mini_playpen.launch
```

#Control by keyboard, the scout_mini can be controlled to move forward, left, right and backward through "w", "a", "s" and "d" on the keyboard

```
roslaunch scout_teleop scout_teleop_key.launch 
```

---

### 4.	Start the gazebo simulation environment of scout_mini and gmapping in the gazebo

​	Start the simulation environment of scout_mini

```
roslaunch scout_slam scout_slam.launch
```

### 5.	Start the gazebo simulation environment of scout_mini and navigation in the gazebo

​	Start the simulation environment of scout_mini

```
roslaunch scout_navigation scout_navigation.launch
```

