execute_process(COMMAND "/home/ias/Desktop/thesis/code/ros_camera/build/tf_publisher_gui/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/ias/Desktop/thesis/code/ros_camera/build/tf_publisher_gui/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
