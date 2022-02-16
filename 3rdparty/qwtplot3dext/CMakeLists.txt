#--------------------------------------------------------------------------------
# Set cmake min version and policy
#--------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)



#--------------------------------------------------------------------------------
# Set project name and version
#--------------------------------------------------------------------------------
project(QwtPlot3DExt VERSION 0.3.1 LANGUAGES CXX)
set(QWTPLOT3DEXT_VERSION_NAME ${PROJECT_VERSION})
set(QWTPLOT3DEXT_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(QWTPLOT3DEXT_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(QWTPLOT3DEXT_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(QWTPLOT3DEXT_VERSION_TWEAK ${PROJECT_VERSION_TWEAK})
set(QWTPLOT3DEXT_VERSION ${QWTPLOT3DEXT_VERSION_MAJOR}.${QWTPLOT3DEXT_VERSION_MINOR}.${QWTPLOT3DEXT_VERSION_PATCH})
set(QWTPLOT3DEXT_SO_VERSION ${QWTPLOT3DEXT_VERSION_MAJOR}.${QWTPLOT3DEXT_VERSION_MINOR})
set(QWTPLOT3DEXT_DEBUG_POSTFIX "d")
set(QWTPLOT3DEXT_VERSION_STR "${QWTPLOT3DEXT_VERSION_MAJOR}.${QWTPLOT3DEXT_VERSION_MINOR}.${QWTPLOT3DEXT_VERSION_PATCH}")
set(QWTPLOT3DEXT_LICENSE "ZLib License")
set(QWTPLOT3DEXT_PRODUCT_NAME "QwtPlot3DExt")
set(QWTPLOT3DEXT_CXX_STANDARD 98)
math(EXPR QWTPLOT3DEXT_VERSION_CALC "${QWTPLOT3DEXT_VERSION_MAJOR}*1000 + ${QWTPLOT3DEXT_VERSION_MINOR}*100 + ${QWTPLOT3DEXT_VERSION_PATCH}")
message(STATUS "==============================================================================")
message(STATUS "----QwtPlot3DExt---- Project version: ${QWTPLOT3DEXT_VERSION}")
message(STATUS "----QwtPlot3DExt---- Project license: ${QWTPLOT3DEXT_LICENSE}")




#--------------------------------------------------------------------------------
# find qt and include path, set cmake moc uic rcc on
#--------------------------------------------------------------------------------
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt4 QUIET COMPONENTS QtCore QUIET)
if (NOT QT_FOUND)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core QUIET)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core QUIET)
endif()
set(QWTPLOT3DEXT_QT_VERSION_MAJOR ${QT_VERSION_MAJOR})
set(QWTPLOT3DEXT_QT_VERSION_MINOR ${QT_VERSION_MINOR})
set(QWTPLOT3DEXT_QT_VERSION_PATCH ${QT_VERSION_PATCH})
set(QWTPLOT3DEXT_QT_VERSION "${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")
set(QWTPLOT3DEXT_QT_OPENGL_FOUND OFF)
set(QWTPLOT3DEXT_QT_OPENGL)
if (QWTPLOT3DEXT_QT_VERSION_MAJOR EQUAL 4)
    if (QWTPLOT3DEXT_QT_VERSION_MINOR LESS 5)
        message(FATAL_ERROR "----QwtPlot3DExt---- Expected Qt4 version must greater than or equal to Qt4.5")
    endif()
    message(STATUS "----QwtPlot3DExt---- Expected Qt version is Qt${QWTPLOT3DEXT_QT_VERSION}")
    find_package(Qt4 REQUIRED QtCore QtGui)
    find_package(Qt4 COMPONENTS QtOpenGL)
    set(QWTPLOT3DEXT_QT_OPENGL_FOUND ${QT_QTOPENGL_FOUND})
    if (QWTPLOT3DEXT_QT_OPENGL_FOUND)
        set(QWTPLOT3DEXT_QT_OPENGL Qt4::QtOpenGL)
    endif()
    INCLUDE(${QT_USE_FILE})
    ADD_DEFINITIONS(${QT_DEFINITIONS})
elseif(QWTPLOT3DEXT_QT_VERSION_MAJOR GREATER 4)
    message(STATUS "----QwtPlot3DExt---- Expected Qt version is Qt${QWTPLOT3DEXT_QT_VERSION}")
    find_package(Qt${QWTPLOT3DEXT_QT_VERSION_MAJOR} COMPONENTS Core Widgets REQUIRED)
    find_package(Qt${QWTPLOT3DEXT_QT_VERSION_MAJOR} COMPONENTS OpenGL)
    set(QWTPLOT3DEXT_QT_OPENGL_FOUND ${Qt${QWTPLOT3DEXT_QT_VERSION_MAJOR}OpenGL_FOUND})
    if (QWTPLOT3DEXT_QT_OPENGL_FOUND)
        set(QWTPLOT3DEXT_QT_OPENGL Qt${QWTPLOT3DEXT_QT_VERSION_MAJOR}::OpenGL)
    endif()
else()
    message(FATAL_ERROR "----QwtPlot3DExt---- Not find Qt package")
endif()

if (QWTPLOT3DEXT_QT_OPENGL_FOUND)
    message(STATUS "----QwtPlot3DExt---- Qt${QWTPLOT3DEXT_QT_VERSION_MAJOR} OpenGL found")
endif()

get_filename_component(QWTPLOT3DEXT_QT_BIN_DIR "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
get_filename_component(QWTPLOT3DEXT_QT_KIT_DIR "${QWTPLOT3DEXT_QT_BIN_DIR}" DIRECTORY)
set(QWTPLOT3DEXT_QT_LIB_DIR ${QWTPLOT3DEXT_QT_KIT_DIR}/lib)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if (POLICY CMP0072)
    set(OpenGL_GL_PREFERENCE LEGACY)
endif()
find_package(OpenGL REQUIRED)



#--------------------------------------------------------------------------------
# Specify the output dir
#--------------------------------------------------------------------------------
set(QWTPLOT3DEXT_PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(QWTPLOT3DEXT_PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR})
set(QWTPLOT3DEXT_APP_OUTPUT_DIR "${PROJECT_BINARY_DIR}/bin")
set(QWTPLOT3DEXT_LIB_OUTPUT_DIR "${PROJECT_BINARY_DIR}/lib")
set(QWTPLOT3DEXT_QTLIB_OUTPUT_DIR "${PROJECT_BINARY_DIR}/lib/qt")
set(QWTPLOT3DEXT_PLUGIN_OUTPUT_DIR "${PROJECT_BINARY_DIR}/plugin")
set(QWTPLOT3DEXT_INCLUDE_OUTPUT_DIR "${PROJECT_BINARY_DIR}/include")
set(QWTPLOT3DEXT_EXAMPLE_OUTPUT_DIR "${PROJECT_BINARY_DIR}/example")
set(QWTPLOT3DEXT_TEST_OUTPUT_DIR "${PROJECT_BINARY_DIR}/test")

# here we specify the installation directory
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${PROJECT_BINARY_DIR}/install" CACHE PATH  "QwtPlot3D install prefix" FORCE)
endif()



#--------------------------------------------------------------------------------
# Set option
#--------------------------------------------------------------------------------
option(QWTPLOT3DEXT_BUILD_SHARED_LIBS "Build shared library" ON)
option(QWTPLOT3DEXT_BUILD_TESTS "Build tests" OFF)
option(QWTPLOT3DEXT_BUILD_EXAMPLES "Build examples" OFF)
option(QWTPLOT3DEXT_BUILD_COMPILER_WARNING "Build target with compiler warnings" OFF)
option(QWTPLOT3DEXT_BUILD_ALL "Build all artifacts" OFF)

if(QWTPLOT3DEXT_BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ON CACHE BOOL "Build as shared libraries")
    message(STATUS "----QwtPlot3DExt---- Build as shared libraries")
else()
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build as static libraries")
    message(STATUS "----QwtPlot3DExt---- Build as static libraries")
endif()

if(QWTPLOT3DEXT_BUILD_TESTS OR QWTPLOT3DEXT_BUILD_ALL)
    enable_testing()
endif()



#--------------------------------------------------------------------------------
# Set lib base name and out put path
#--------------------------------------------------------------------------------
set(QWTPLOT3DEXT_LIB_NAME QwtPlot3DExt)
set(LIBRARY_OUTPUT_PATH ${QWTPLOT3DEXT_LIB_OUTPUT_DIR})



#----------------------------------------------------------------
# Sources
#----------------------------------------------------------------
set(QWTPLOT3DEXT_HEADERS
    ${PROJECT_SOURCE_DIR}/include/qwt3d_appearance.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_autoscaler.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_axis.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_color.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_color_std.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_colorlegend.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_coordsys.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_curveplot.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_data.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_drawable.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_enrichment.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_enrichment_std.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_extglwidget.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_function.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_global.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_graphplot.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_gridmapping.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_gridplot.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_helper.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_io.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_io_reader.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_label.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_mapping.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_meshplot.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_openglhelper.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_parametricsurface.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_plot3d.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_portability.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_scale.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_surfaceplot.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_types.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_valueptr.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_volumeplot.h
    )

set(QWTPLOT3DEXT_SOURCES
    ${PROJECT_SOURCE_DIR}/src/qwt3d_appearance.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_autoscaler.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_axis.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_color_std.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_colorlegend.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_coordsys.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_curveplot.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_data.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_drawable.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_enrichment_std.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_extglwidget.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_function.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_graphplot.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_gridmapping.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_gridplot.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_io.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_io_reader.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_label.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_lighting.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_meshplot.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_parametricsurface.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_plot3d.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_scale.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_surfaceplot.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_types.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_volumeplot.cpp
    )



#----------------------------------------------------------------
# Add lib target
#----------------------------------------------------------------
if(QWTPLOT3DEXT_BUILD_SHARED_LIBS)
    add_library(${QWTPLOT3DEXT_LIB_NAME} SHARED ${QWTPLOT3DEXT_HEADERS} ${QWTPLOT3DEXT_SOURCES})
    target_compile_definitions(${QWTPLOT3DEXT_LIB_NAME}
        PUBLIC
        QWTPLOT3DEXT_DLL
        PRIVATE
        QWTPLOT3DEXT_MAKEDLL
        )
else()
    add_library(${QWTPLOT3DEXT_LIB_NAME} STATIC ${QWTPLOT3DEXT_HEADERS} ${QWTPLOT3DEXT_SOURCES})
endif()

if (NOT QWTPLOT3DEXT_QT_OPENGL_FOUND)
    target_compile_definitions(${QWTPLOT3DEXT_LIB_NAME} PUBLIC QWTPLOT3DEXT_NO_OPENGL)
endif()

target_include_directories(${QWTPLOT3DEXT_LIB_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${OPENGL_INCLUDE_DIR}
    )

if (QWTPLOT3DEXT_QT_VERSION_MAJOR EQUAL 4)
    target_link_libraries(${QWTPLOT3DEXT_LIB_NAME}
        PUBLIC
        Qt4::QtCore
        Qt4::QtGui
        ${QWTPLOT3DEXT_QT_OPENGL}
        ${OPENGL_LIBRARIES}
        )
else(QWTPLOT3DEXT_QT_VERSION_MAJOR GREATER 4)
    target_link_libraries(${QWTPLOT3DEXT_LIB_NAME}
        PUBLIC
        Qt${QWTPLOT3DEXT_QT_VERSION_MAJOR}::Core
        Qt${QWTPLOT3DEXT_QT_VERSION_MAJOR}::Gui
        Qt${QWTPLOT3DEXT_QT_VERSION_MAJOR}::Widgets
        ${QWTPLOT3DEXT_QT_OPENGL}
        ${OPENGL_LIBRARIES}
        )
endif()



#--------------------------------------------------------------------------------
# add subdirectory
#--------------------------------------------------------------------------------
if(QWTPLOT3DEXT_BUILD_EXAMPLES OR QWTPLOT3DEXT_BUILD_ALL)
    add_subdirectory(examples)
endif()
