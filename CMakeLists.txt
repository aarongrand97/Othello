cmake_minimum_required(VERSION 2.8)
include(ExternalProject)

# Adding customized cmake module for building boost
list(APPEND CMAKE_MODULE_PATH  "${CMAKE_SOURCE_DIR}/cmake/Modules/")

project(tutorial)

  

  # Find default python libraries and interpreter
  find_package(PythonInterp REQUIRED)
  find_package(PythonLibs REQUIRED)
  include(BuildBoost) # Custom module

  include_directories(${Boost_INCLUDE_DIR} ${PYTHON_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIR})

  # Build and link the pylib module
  add_library(othellolib SHARED 
  othellolib.cpp 
  gameState.cpp)
  target_link_libraries(othellolib ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
  add_dependencies(othellolib Boost)

  # Tweaks the name of the library to match what Python expects
  set_target_properties(othellolib PROPERTIES SUFFIX .so)
  set_target_properties(othellolib PROPERTIES PREFIX "")
