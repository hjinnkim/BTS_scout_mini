cmake_minimum_required(VERSION 3.0.2)
project(scout_odom)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  nav_msgs
  roscpp
  roslaunch
  sensor_msgs
  std_msgs
  tf2
  tf2_ros
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################


###################################
## catkin specific configuration ##
###################################

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES odom_converter
#  CATKIN_DEPENDS geometry_msgs nav_msgs roscpp roslaunch sensor_msgs std_msgs tf2 tf2_ros
#  DEPENDS system_lib
)

###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(odom_converter
  STATIC src/odom_converter.cpp
)
target_link_libraries(odom_converter ${catkin_LIBRARIES})
add_dependencies(odom_converter ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(odom_converter_node src/odom_converter_node.cpp)
target_link_libraries(odom_converter_node
  ${catkin_LIBRARIES} odom_converter
)

#############
## Install ##
#############

install(TARGETS scout_messenger scout_base_node
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION})

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})

install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
