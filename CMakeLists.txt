cmake_minimum_required(VERSION 3.10)

# set the project name
project(Separatista)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(GNUInstallDirs REQUIRED)
set(SEPARATISTA_SCHEMA_DIR ${CMAKE_INSTALL_FULL_DATAROOTDIR}/Separatista)
set(SEPARATISTA_SCHEMA_PATH ${SEPARATISTA_SCHEMA_DIR}/schema)
install(DIRECTORY schema DESTINATION ${SEPARATISTA_SCHEMA_DIR})

add_subdirectory(lib)
add_subdirectory(gui)

