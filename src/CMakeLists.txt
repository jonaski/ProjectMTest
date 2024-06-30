configure_file(config.h.in config.h)

set(SOURCES
  visualizationcontainer.cpp
  projectmvisualization.cpp
  projectmpresetmodel.cpp
  visualizationselectordialog.cpp
)

set(HEADERS
  visualizationcontainer.h
  projectmvisualization.h
  projectmpresetmodel.h
  visualizationselectordialog.h
)

if(USE_QGLWIDGET)
  list(APPEND SOURCES visualizationoglwidget.cpp)
  list(APPEND HEADERS visualizationoglwidget.h)
else()
  list(APPEND SOURCES visualizationopenglwidget.cpp)
  list(APPEND HEADERS visualizationopenglwidget.h)
endif()

qt_wrap_cpp(MOC ${HEADERS})
qt_wrap_ui(UIC visualizationselectordialog.ui)
add_library(projectmtest_lib STATIC ${SOURCES} ${MOC} ${UIC})
target_include_directories(projectmtest_lib PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(projectmtest_lib PUBLIC
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  ${LIBPROJECTM_LIBRARIES}
)
if(QT_VERSION_MAJOR EQUAL 5)
  target_link_libraries(projectmtest_lib PUBLIC Qt${QT_VERSION_MAJOR}::OpenGL)
else()
  target_link_libraries(projectmtest_lib PUBLIC Qt${QT_VERSION_MAJOR}::OpenGLWidgets)
endif()
set(EXECUTABLE_OUTPUT_PATH ..)
add_executable(projectmtest main.cpp)
target_include_directories(projectmtest PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(projectmtest PRIVATE projectmtest_lib)
