# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\ToDoList_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ToDoList_autogen.dir\\ParseCache.txt"
  "ToDoList_autogen"
  )
endif()