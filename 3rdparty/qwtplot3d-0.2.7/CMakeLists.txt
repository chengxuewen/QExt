#--------------------------------------------------------------------------------
# Set cmake min version and policy
#--------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)



#--------------------------------------------------------------------------------
# Set project name and version
#--------------------------------------------------------------------------------
project(QwtPlot3D VERSION 0.2.7 LANGUAGES CXX)
set(QWTPLOT3D_VERSION_NAME ${PROJECT_VERSION})
set(QWTPLOT3D_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(QWTPLOT3D_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(QWTPLOT3D_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(QWTPLOT3D_VERSION_TWEAK ${PROJECT_VERSION_TWEAK})
set(QWTPLOT3D_VERSION ${QWTPLOT3D_VERSION_MAJOR}.${QWTPLOT3D_VERSION_MINOR}.${QWTPLOT3D_VERSION_PATCH})
set(QWTPLOT3D_SO_VERSION ${QWTPLOT3D_VERSION_MAJOR}.${QWTPLOT3D_VERSION_MINOR})
set(QWTPLOT3D_DEBUG_POSTFIX "d")
set(QWTPLOT3D_VERSION_STR "${QWTPLOT3D_VERSION_MAJOR}.${QWTPLOT3D_VERSION_MINOR}.${QWTPLOT3D_VERSION_PATCH}")
set(QWTPLOT3D_LICENSE "ZLib License")
set(QWTPLOT3D_PRODUCT_NAME "QwtPlot3D")
set(QWTPLOT3D_CXX_STANDARD 98)
math(EXPR QWTPLOT3D_VERSION_CALC "${QWTPLOT3D_VERSION_MAJOR}*1000 + ${QWTPLOT3D_VERSION_MINOR}*100 + ${QWTPLOT3D_VERSION_PATCH}")
message(STATUS "==============================================================================")
message(STATUS "----QwtPlot3D---- Project version: ${QWTPLOT3D_VERSION}")
message(STATUS "----QwtPlot3D---- Project license: ${QWTPLOT3D_LICENSE}")




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
set(QWTPLOT3D_QT_VERSION_MAJOR ${QT_VERSION_MAJOR})
set(QWTPLOT3D_QT_VERSION_MINOR ${QT_VERSION_MINOR})
set(QWTPLOT3D_QT_VERSION_PATCH ${QT_VERSION_PATCH})
set(QWTPLOT3D_QT_VERSION "${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")
set(QWTPLOT3D_QT_OPENGL_FOUND OFF)
set(QWTPLOT3D_QT_OPENGL)
if (QWTPLOT3D_QT_VERSION_MAJOR EQUAL 4)
    if (QWTPLOT3D_QT_VERSION_MINOR LESS 5)
        message(FATAL_ERROR "----QwtPlot3D---- Expected Qt4 version must greater than or equal to Qt4.5")
    endif()
    message(STATUS "----QwtPlot3D---- Expected Qt version is Qt${QWTPLOT3D_QT_VERSION}")
    find_package(Qt4 REQUIRED QtCore QtGui)
    find_package(Qt4 COMPONENTS QtOpenGL)
    set(QWTPLOT3D_QT_OPENGL_FOUND ${QT_QTOPENGL_FOUND})
    if (QWTPLOT3D_QT_OPENGL_FOUND)
        set(QWTPLOT3D_QT_OPENGL Qt4::QtOpenGL)
    endif()
    INCLUDE(${QT_USE_FILE})
    ADD_DEFINITIONS(${QT_DEFINITIONS})
elseif(QWTPLOT3D_QT_VERSION_MAJOR GREATER 4)
    message(STATUS "----QwtPlot3D---- Expected Qt version is Qt${QWTPLOT3D_QT_VERSION}")
    find_package(Qt${QWTPLOT3D_QT_VERSION_MAJOR} COMPONENTS Core Widgets REQUIRED)
    find_package(Qt${QWTPLOT3D_QT_VERSION_MAJOR} COMPONENTS OpenGL)
    set(QWTPLOT3D_QT_OPENGL_FOUND ${Qt${QWTPLOT3D_QT_VERSION_MAJOR}OpenGL_FOUND})
    if (QWTPLOT3D_QT_OPENGL_FOUND)
        set(QWTPLOT3D_QT_OPENGL Qt${QWTPLOT3D_QT_VERSION_MAJOR}::OpenGL)
    endif()
else()
    message(FATAL_ERROR "----QwtPlot3D---- Not find Qt package")
endif()

if (QWTPLOT3D_QT_OPENGL_FOUND)
    message(STATUS "----QwtPlot3D---- Qt${QWTPLOT3D_QT_VERSION_MAJOR} OpenGL found")
endif()

get_filename_component(QWTPLOT3D_QT_BIN_DIR "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
get_filename_component(QWTPLOT3D_QT_KIT_DIR "${QWTPLOT3D_QT_BIN_DIR}" DIRECTORY)
set(QWTPLOT3D_QT_LIB_DIR ${QWTPLOT3D_QT_KIT_DIR}/lib)

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
set(QWTPLOT3D_PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(QWTPLOT3D_PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR})
set(QWTPLOT3D_APP_OUTPUT_DIR "${PROJECT_BINARY_DIR}/bin")
set(QWTPLOT3D_LIB_OUTPUT_DIR "${PROJECT_BINARY_DIR}/lib")
set(QWTPLOT3D_QTLIB_OUTPUT_DIR "${PROJECT_BINARY_DIR}/lib/qt")
set(QWTPLOT3D_PLUGIN_OUTPUT_DIR "${PROJECT_BINARY_DIR}/plugin")
set(QWTPLOT3D_INCLUDE_OUTPUT_DIR "${PROJECT_BINARY_DIR}/include")
set(QWTPLOT3D_EXAMPLE_OUTPUT_DIR "${PROJECT_BINARY_DIR}/example")
set(QWTPLOT3D_TEST_OUTPUT_DIR "${PROJECT_BINARY_DIR}/test")

# here we specify the installation directory
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${PROJECT_BINARY_DIR}/install" CACHE PATH  "QwtPlot3D install prefix" FORCE)
endif()



#--------------------------------------------------------------------------------
# Set option
#--------------------------------------------------------------------------------
option(QWTPLOT3D_BUILD_SHARED_LIBS "Build shared library" ON)
option(QWTPLOT3D_BUILD_TESTS "Build tests" OFF)
option(QWTPLOT3D_BUILD_EXAMPLES "Build examples" OFF)
option(QWTPLOT3D_BUILD_COMPILER_WARNING "Build target with compiler warnings" OFF)
option(QWTPLOT3D_BUILD_ALL "Build all artifacts" OFF)

if(QWTPLOT3D_BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ON CACHE BOOL "Build as shared libraries")
    message(STATUS "----QwtPlot3D---- Build as shared libraries")
else()
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build as static libraries")
    message(STATUS "----QwtPlot3D---- Build as static libraries")
endif()

if(QWTPLOT3D_BUILD_TESTS OR QWTPLOT3D_BUILD_ALL)
    enable_testing()
endif()



#--------------------------------------------------------------------------------
# Set lib base name and out put path
#--------------------------------------------------------------------------------
set(QWTPLOT3D_LIB_NAME QwtPlot3D)
set(LIBRARY_OUTPUT_PATH ${QWTPLOT3D_LIB_OUTPUT_DIR})



#----------------------------------------------------------------
# Sources
#----------------------------------------------------------------
set(QWTPLOT3D_HEADERS
    ${PROJECT_SOURCE_DIR}/include/qwt3d_autoptr.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_autoscaler.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_axis.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_color.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_colorlegend.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_coordsys.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_drawable.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_enrichment.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_enrichment_std.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_function.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_global.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_graphplot.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_gridmapping.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_helper.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_io.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_io_gl2ps.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_io_reader.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_label.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_mapping.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_multiplot.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_openglhelper.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_parametricsurface.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_plot.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_portability.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_scale.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_surfaceplot.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_types.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_volumeplot.h
    ${PROJECT_SOURCE_DIR}/3rdparty/gl2ps/gl2ps.h
    )

set(QWTPLOT3D_SOURCES
    ${PROJECT_SOURCE_DIR}/src/qwt3d_autoscaler.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_axis.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_color.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_colorlegend.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_coordsys.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_dataviews.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_drawable.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_enrichment_std.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_function.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_gridmapping.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_gridplot.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_io.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_io_gl2ps.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_io_reader.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_label.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_lighting.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_meshplot.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_mousekeyboard.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_movements.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_parametricsurface.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_plot.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_scale.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_surfaceplot.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_types.cpp
    ${PROJECT_SOURCE_DIR}/3rdparty/gl2ps/gl2ps.c
    )



#----------------------------------------------------------------
# Add lib target
#----------------------------------------------------------------
if(QWTPLOT3D_BUILD_SHARED_LIBS)
    add_library(${QWTPLOT3D_LIB_NAME} SHARED ${QWTPLOT3D_HEADERS} ${QWTPLOT3D_SOURCES})
    target_compile_definitions(${QWTPLOT3D_LIB_NAME}
        PUBLIC
        $<$<BOOL:MSVC>:QWT3D_DLL>
        PRIVATE
        $<$<BOOL:MSVC>:QWT3D_MAKEDLL>
        )
else()
    add_library(${QWTPLOT3D_LIB_NAME} STATIC ${QWTPLOT3D_HEADERS} ${QWTPLOT3D_SOURCES})
endif()

if (NOT QWTPLOT3D_QT_OPENGL_FOUND)
    target_compile_definitions(${QWTPLOT3D_LIB_NAME} PUBLIC QWT3D_NO_OPENGL)
endif()

target_include_directories(${QWTPLOT3D_LIB_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/3rdparty/gl2ps
    ${OPENGL_INCLUDE_DIR}
    )

if (QWTPLOT3D_QT_VERSION_MAJOR EQUAL 4)
    target_link_libraries(${QWTPLOT3D_LIB_NAME}
        PUBLIC
        Qt4::QtCore
        Qt4::QtGui
        ${QWTPLOT3D_QT_OPENGL}
        ${OPENGL_LIBRARIES}
        )
else(QWTPLOT3D_QT_VERSION_MAJOR GREATER 4)
    target_link_libraries(${QWTPLOT3D_LIB_NAME}
        PUBLIC
        Qt${QWTPLOT3D_QT_VERSION_MAJOR}::Core
        Qt${QWTPLOT3D_QT_VERSION_MAJOR}::Gui
        Qt${QWTPLOT3D_QT_VERSION_MAJOR}::Widgets
        ${QWTPLOT3D_QT_OPENGL}
        ${OPENGL_LIBRARIES}
        )
endif()



#--------------------------------------------------------------------------------
# add subdirectory
#--------------------------------------------------------------------------------
if(QWTPLOT3D_BUILD_EXAMPLES OR QWTPLOT3D_BUILD_ALL)
    add_subdirectory(examples)
endif()
