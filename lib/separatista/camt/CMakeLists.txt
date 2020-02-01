if(CMAKE_COMPILER_IS_GNUCC)
  # needed for gcc 4.6+
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
endif()

add_library(camt OBJECT camt.053.001.02.cpp)
target_include_directories(camt PUBLIC "${PROJECT_SOURCE_DIR}/lib/")

