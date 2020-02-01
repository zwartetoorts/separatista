add_library(mt940s mt940s.cpp)
target_link_libraries(mt940s SHARED iban)
target_include_directories(mt940s PUBLIC "${PROJECT_SOURCE_DIR}/lib/")
