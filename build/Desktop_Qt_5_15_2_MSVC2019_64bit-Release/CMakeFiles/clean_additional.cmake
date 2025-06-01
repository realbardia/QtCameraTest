# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\CameraTest_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CameraTest_autogen.dir\\ParseCache.txt"
  "CameraTest_autogen"
  )
endif()
