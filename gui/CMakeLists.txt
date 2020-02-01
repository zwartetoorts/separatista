add_executable(separatistaGUI
    app.cpp
    app.h
    currencytextctrl.cpp
    currencytextctrl.h
    documenteditor.cpp
    documenteditor.h
    expertdataviewmodel.cpp
    expertdataviewmodel.h
    expertdataviewrenderer.cpp
    expertdataviewrenderer.h
    ibantextctrl.cpp
    ibantextctrl.h
    mainframe.cpp
    mainframe.h
    simpledataviewmodel.cpp
    simpledataviewmodel.h
    simpledataviewrenderer.cpp
    simpledataviewrenderer.h
    simpleviewdata.cpp
    simpleviewdata.h
)

find_package(wxWidgets REQUIRED core base adv)
include(${wxWidgets_USE_FILE})

find_package(XercesC REQUIRED)

if(CMAKE_COMPILER_IS_GNUCC)
  # needed for gcc 4.6+
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
endif()

target_include_directories(separatistaGUI PUBLIC "${PROJECT_SOURCE_DIR}/lib/")
target_link_libraries(separatistaGUI separatista iban ${wxWidgets_LIBRARIES} ${XercesC_LIBRARIES})

install(PROGRAMS separatistaGUI DESTINATION ${CMAKE_INSTALL_FULL_BINDIR})
