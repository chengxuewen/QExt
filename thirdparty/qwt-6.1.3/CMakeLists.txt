#--------------------------------------------------------------------------------
# Set cmake min version and policy
#--------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)



#--------------------------------------------------------------------------------
# Set project name and version
#--------------------------------------------------------------------------------
project(Qwt VERSION 6.1.3 LANGUAGES CXX)
set(QWT_VERSION_NAME ${PROJECT_VERSION})
set(QWT_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(QWT_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(QWT_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(QWT_VERSION_TWEAK ${PROJECT_VERSION_TWEAK})
set(QWT_VERSION ${QWT_VERSION_MAJOR}.${QWT_VERSION_MINOR}.${QWT_VERSION_PATCH})
set(QWT_SO_VERSION ${QWT_VERSION_MAJOR}.${QWT_VERSION_MINOR})
set(QWT_DEBUG_POSTFIX "d")
set(QWT_VERSION_STR "${QWT_VERSION_MAJOR}.${QWT_VERSION_MINOR}.${QWT_VERSION_PATCH}")
set(QWT_LICENSE "Qwt License")
set(QWT_PRODUCT_NAME "Qwt")
set(QWT_CXX_STANDARD 98)
math(EXPR QWT_VERSION_CALC "${QWT_VERSION_MAJOR}*1000 + ${QWT_VERSION_MINOR}*100 + ${QWT_VERSION_PATCH}")
message(STATUS "==============================================================================")
message(STATUS "----QWT---- Project version: ${QWT_VERSION}")
message(STATUS "----QWT---- Project license: ${QWT_LICENSE}")




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
set(QWT_QT_VERSION_MAJOR ${QT_VERSION_MAJOR})
set(QWT_QT_VERSION_MINOR ${QT_VERSION_MINOR})
set(QWT_QT_VERSION_PATCH ${QT_VERSION_PATCH})
set(QWT_QT_VERSION "${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")
set(QWT_QT_OPENGL_FOUND OFF)
set(QWT_QT_OPENGL)
if (QWT_QT_VERSION_MAJOR EQUAL 4)
    if (QWT_QT_VERSION_MINOR LESS 5)
        message(FATAL_ERROR "----QWT---- Expected Qt4 version must greater than or equal to Qt4.5")
    endif()
    message(STATUS "----QWT---- Expected Qt version is Qt${QWT_QT_VERSION}")
    find_package(Qt4 REQUIRED QtCore QtGui QtSvg QtXml)
    find_package(Qt4 COMPONENTS QtOpenGL)
    set(QWT_QT_OPENGL_FOUND ${QT_QTOPENGL_FOUND})
    if (QWT_QT_OPENGL_FOUND)
        set(QWT_QT_OPENGL Qt4::QtOpenGL)
    endif()
    INCLUDE(${QT_USE_FILE})
    ADD_DEFINITIONS(${QT_DEFINITIONS})
elseif(QWT_QT_VERSION_MAJOR GREATER 4)
    message(STATUS "----QWT---- Expected Qt version is Qt${QWT_QT_VERSION}")
    find_package(Qt${QWT_QT_VERSION_MAJOR} COMPONENTS Core Widgets Concurrent PrintSupport Svg Xml REQUIRED)
    find_package(Qt${QWT_QT_VERSION_MAJOR} COMPONENTS OpenGL)
    set(QWT_QT_OPENGL_FOUND ${Qt${QWT_QT_VERSION_MAJOR}OpenGL_FOUND})
    if (QWT_QT_OPENGL_FOUND)
        set(QWT_QT_OPENGL Qt${QWT_QT_VERSION_MAJOR}::OpenGL)
    endif()
else()
    message(FATAL_ERROR "----QWT---- Not find Qt package")
endif()

if (QWT_QT_OPENGL_FOUND)
    message(STATUS "----QWT---- Qt${QWT_QT_VERSION_MAJOR} OpenGL found")
endif()

get_filename_component(QWT_QT_BIN_DIR "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
get_filename_component(QWT_QT_KIT_DIR "${QWT_QT_BIN_DIR}" DIRECTORY)
set(QWT_QT_LIB_DIR ${QWT_QT_KIT_DIR}/lib)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)



#--------------------------------------------------------------------------------
# Specify the output dir
#--------------------------------------------------------------------------------
set(QWT_PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(QWT_PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR})
if (NOT QWT_APP_OUTPUT_DIR)
    set(QWT_APP_OUTPUT_DIR "${PROJECT_BINARY_DIR}/bin")
endif()

if (NOT QWT_LIB_OUTPUT_DIR)
    set(QWT_LIB_OUTPUT_DIR "${PROJECT_BINARY_DIR}/lib")
endif()

if (NOT QWT_QTLIB_OUTPUT_DIR)
    set(QWT_QTLIB_OUTPUT_DIR "${PROJECT_BINARY_DIR}/lib/qt")
endif()

if (NOT QWT_SYSLIB_OUTPUT_DIR)
    set(QWT_SYSLIB_OUTPUT_DIR "${PROJECT_BINARY_DIR}/lib/sys")
endif()

if (NOT QWT_PLUGIN_OUTPUT_DIR)
    set(QWT_PLUGIN_OUTPUT_DIR "${PROJECT_BINARY_DIR}/plugin")
endif()

if (NOT QWT_INCLUDE_OUTPUT_DIR)
    set(QWT_INCLUDE_OUTPUT_DIR "${PROJECT_BINARY_DIR}/include")
endif()

if (NOT QWT_EXAMPLE_OUTPUT_DIR)
    set(QWT_EXAMPLE_OUTPUT_DIR "${PROJECT_BINARY_DIR}/example")
endif()

if (NOT QWT_TEST_OUTPUT_DIR)
    set(QWT_TEST_OUTPUT_DIR "${PROJECT_BINARY_DIR}/test")
endif()

# here we specify the installation directory
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${PROJECT_BINARY_DIR}/install" CACHE PATH  "QWT install prefix" FORCE)
endif()



#--------------------------------------------------------------------------------
# Set option
#--------------------------------------------------------------------------------
option(QWT_BUILD_SHARED_LIBS "Build shared library" ON)
option(QWT_BUILD_TESTS "Build tests" ON)
option(QWT_BUILD_EXAMPLES "Build examples" ON)
option(QWT_BUILD_COMPILER_WARNING "Build target with compiler warnings" OFF)
option(QWT_BUILD_ALL "Build all artifacts" OFF)

if(QWT_BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ON CACHE BOOL "Build as shared libraries")
    message(STATUS "----QWT---- Build as shared libraries")
else()
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build as static libraries")
    message(STATUS "----QWT---- Build as static libraries")
endif()

if(QWT_BUILD_TESTS OR QWT_BUILD_ALL)
    enable_testing()
endif()



#--------------------------------------------------------------------------------
# add subdirectory
#--------------------------------------------------------------------------------
add_subdirectory(src)
add_subdirectory(textengines)

if(QWT_BUILD_EXAMPLES OR QWT_BUILD_ALL)
    add_subdirectory(examples)
endif()
