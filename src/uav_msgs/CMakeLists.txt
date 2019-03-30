cmake_minimum_required(VERSION 2.8.3)
project(uav_msgs)

add_compile_options(-std=c++11)
add_compile_options(-Wall)

find_package(catkin REQUIRED COMPONENTS
  geographic_msgs
  geometry_msgs
  message_generation
  roscpp
  sensor_msgs
  std_msgs
)

 add_message_files(
  DIRECTORY msg
  FILES
  PayloadPosition.msg
  PayloadROI.msg
  CameraInfoExtended.msg
  MissionParams.msg
)

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

generate_messages(
  DEPENDENCIES
  geographic_msgs   geometry_msgs   sensor_msgs   std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS geographic_msgs geometry_msgs message_runtime roscpp sensor_msgs std_msgs
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)