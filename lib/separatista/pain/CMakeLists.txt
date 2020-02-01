if(CMAKE_COMPILER_IS_GNUCC)
  # needed for gcc 4.6+
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
endif()

add_library(pain OBJECT pain.001.001.03.cpp pain.008.001.02.cpp)
target_include_directories(pain PUBLIC "${PROJECT_SOURCE_DIR}/lib/")