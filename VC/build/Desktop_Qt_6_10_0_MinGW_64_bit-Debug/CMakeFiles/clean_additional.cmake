# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\VC_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\VC_autogen.dir\\ParseCache.txt"
  "VC_autogen"
  )
endif()
