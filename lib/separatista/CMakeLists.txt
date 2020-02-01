add_subdirectory(iban)
add_subdirectory(camt)
add_subdirectory(pain)
add_subdirectory(debug)

configure_file(setup.h.in setup.h)

add_library(separatista SHARED 
    attributedleafelement.cpp
    attributedleafelement.h
    automagic.cpp
    automagic.h
    branchelement.cpp
    branchelement.h
    choiceelement.cpp
    choiceelement.h
    documentreader.cpp
    documentreader.h
    documentregistry.cpp
    documentregistry.h
    element.cpp
    element.h
    elementlist.cpp
    elementlist.h
    exception.cpp
    exception.h
    leafelement.cpp
    leafelement.h
    separatista.cpp
    separatista.h
    separatistadocument.cpp
    separatistadocument.h
    validator.cpp
    validator.h
    nix.cpp
)

find_package(XercesC REQUIRED)

target_compile_definitions(separatista PRIVATE SEPARATISTA_DEBUG SEPARATISTA_DEBUG_METHODS)
target_include_directories(separatista PRIVATE "${PROJECT_SOURCE_DIR}/lib/" PUBLIC ${XercesC_INCLUDE_DIRS})
target_link_libraries(separatista iban camt pain separatistaDEBUG)

install(TARGETS separatista iban separatistaDEBUG DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR})

if (MSVC)
    add_property(TARGET separatista PROPERTY SOURCES "windows.h dll.cpp")
endif ()


