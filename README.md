# ProjectM Test Project

This is a simple test project to test ProjectM with Qt.

## Build

You can pass the following options to CMake:

### QT_VERSION_MAJOR

Set this to either 5 or 6.
 
### USE_QGLWIDGET

If building with Qt 5, you can set this to ON to use the old deprecated `QGLWidget` class.
 
### USE_PROJECTM4

Either `ON` or `OFF`.

This will use the new ProjectM version 4, only a few presets works.

To build with ProjectM version 4 use: `USE_PROJECTM4=ON`.

### Build with Qt 5 and QGLWidget

    cmake .. -DCMAKE_BUILD_TYPE=Debug -DUSE_PROJECTM4=OFF -DUSE_QGLWIDGET=ON -DQT_VERSION_MAJOR=5

### Build with Qt 6 and QOpenGLWidget

    cmake .. -DCMAKE_BUILD_TYPE=Debug -DUSE_PROJECTM4=OFF -DUSE_QGLWIDGET=OFF -DQT_VERSION_MAJOR=6
