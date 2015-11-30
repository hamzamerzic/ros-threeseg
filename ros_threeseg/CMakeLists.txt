cmake_minimum_required(VERSION 2.8.3)
project(ros_threeseg)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
  std_msgs
  tf
)

catkin_package()

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(state_publisher_threeseg src/state_publisher_threeseg.cpp)
target_link_libraries(state_publisher_threeseg ${catkin_LIBRARIES})
