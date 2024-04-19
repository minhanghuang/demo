cmake_minimum_required(VERSION 3.0.2)
project(unittest_demo)

find_package(catkin REQUIRED COMPONENTS
  rospy
)

catkin_package()

###########
## Build ##
###########

include_directories(
  ${catkin_INCLUDE_DIRS}
)

#############
## Install ##
#############
catkin_install_python(
  PROGRAMS
  test/demo.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

if(CATKIN_ENABLE_TESTING)
  find_package(catkin COMPONENTS rostest)
  add_custom_target(MAKE_TESTPY_EXECUTABLE ALL
    COMMAND chmod a+x ${CMAKE_CURRENT_SOURCE_DIR}/test/*.py
  )
  add_rostest(test/demo.test)
endif()
