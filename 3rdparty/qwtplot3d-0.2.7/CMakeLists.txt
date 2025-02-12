#-----------------------------------------------------------------------------------------------------------------------
# Set cmake min version and policy
#-----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)


#-----------------------------------------------------------------------------------------------------------------------
# Set project name and version
#-----------------------------------------------------------------------------------------------------------------------
message(STATUS "================================================QwtPlot3D===================================================")
project(QwtPlot3D VERSION 0.2.7.1 LANGUAGES CXX)
set(QWTPLOT3D_VERSION_NAME ${PROJECT_VERSION})
set(QWTPLOT3D_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(QWTPLOT3D_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(QWTPLOT3D_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(QWTPLOT3D_VERSION_TWEAK ${PROJECT_VERSION_TWEAK})
set(QWTPLOT3D_VERSION ${QWTPLOT3D_VERSION_MAJOR}.${QWTPLOT3D_VERSION_MINOR}.${QWTPLOT3D_VERSION_PATCH})
set(QWTPLOT3D_SO_VERSION ${QWTPLOT3D_VERSION_MAJOR}.${QWTPLOT3D_VERSION_MINOR})
set(QWTPLOT3D_DEBUG_POSTFIX "d")
set(QWTPLOT3D_VERSION_STR "${QWTPLOT3D_VERSION_MAJOR}.${QWTPLOT3D_VERSION_MINOR}.${QWTPLOT3D_VERSION_PATCH}")
set(QWTPLOT3D_LICENSE "QwtPlot3D License")
set(QWTPLOT3D_PRODUCT_NAME "QwtPlot3D")
set(QWTPLOT3D_CXX_STANDARD 98)
math(EXPR QWTPLOT3D_VERSION_CALC "${QWTPLOT3D_VERSION_MAJOR}*1000 + ${QWTPLOT3D_VERSION_MINOR}*100 + ${QWTPLOT3D_VERSION_PATCH}")
message(STATUS "Project version: QwtPlot3D ${QWTPLOT3D_VERSION}")
message(STATUS "Project license: ${QWTPLOT3D_LICENSE}")


#-----------------------------------------------------------------------------------------------------------------------
# find qt and include path, set cmake moc uic rcc on
#-----------------------------------------------------------------------------------------------------------------------
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt4 QUIET COMPONENTS QtCore QUIET)
if(NOT QT_FOUND)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core QUIET)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core QUIET)
endif()
set(QWTPLOT3D_QT_VERSION_MAJOR ${QT_VERSION_MAJOR})
set(QWTPLOT3D_QT_VERSION_MINOR ${QT_VERSION_MINOR})
set(QWTPLOT3D_QT_VERSION_PATCH ${QT_VERSION_PATCH})
set(QWTPLOT3D_QT_VERSION "${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")
set(QWTPLOT3D_QT_OPENGL_FOUND OFF)
set(QWTPLOT3D_QT_OPENGL)
if(QWTPLOT3D_QT_VERSION_MAJOR EQUAL 4)
    if(QWTPLOT3D_QT_VERSION_MINOR LESS 5)
        message(FATAL_ERROR "Expected Qt4 version must greater than or equal to Qt4.5")
    endif()
    message(STATUS "Expected Qt version is Qt4")
    set(QWTPLOT3D_QT_DEP_COMPONENTS QtCore QtGui QtOpenGL)
    find_package(Qt4 COMPONENTS ${QWTPLOT3D_QT_DEP_COMPONENTS} REQUIRED)
    INCLUDE(${QT_USE_FILE})
    ADD_DEFINITIONS(${QT_DEFINITIONS})
elseif(QWTPLOT3D_QT_VERSION_MAJOR EQUAL 5)
    message(STATUS "Expected Qt version is Qt${QWTPLOT3D_QT_VERSION}")
    set(QWTPLOT3D_QT_DEP_COMPONENTS Core Widgets OpenGL Concurrent PrintSupport)
    find_package(Qt${QWTPLOT3D_QT_VERSION_MAJOR} COMPONENTS ${QWTPLOT3D_QT_DEP_COMPONENTS} REQUIRED)
elseif(QWTPLOT3D_QT_VERSION_MAJOR EQUAL 6)
    message(STATUS "Expected Qt version is Qt${QWTPLOT3D_QT_VERSION}")
    set(QWTPLOT3D_QT_DEP_COMPONENTS Core Widgets OpenGL Concurrent PrintSupport)
    find_package(Qt${QWTPLOT3D_QT_VERSION_MAJOR} COMPONENTS ${QWTPLOT3D_QT_DEP_COMPONENTS} REQUIRED)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()
set(QWTPLOT3D_QT_FINDPKG_CMD Qt${QWTPLOT3D_QT_VERSION_MAJOR} COMPONENTS ${QWTPLOT3D_QT_DEP_COMPONENTS} REQUIRED)
string(REPLACE ";" " " QWTPLOT3D_QT_FINDPKG_CMDSTR "${QWTPLOT3D_QT_FINDPKG_CMD}")

get_filename_component(QWTPLOT3D_QT_BIN_DIR "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
get_filename_component(QWTPLOT3D_QT_KIT_DIR "${QWTPLOT3D_QT_BIN_DIR}" DIRECTORY)
set(QWTPLOT3D_QT_LIB_DIR ${QWTPLOT3D_QT_KIT_DIR}/lib)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


#-----------------------------------------------------------------------------------------------------------------------
# Set option
#-----------------------------------------------------------------------------------------------------------------------
option(QWTPLOT3D_BUILD_SHARED_LIBS "Build shared library" ON)
option(QWTPLOT3D_BUILD_TESTS "Build tests" OFF)
option(QWTPLOT3D_BUILD_EXAMPLES "Build examples" OFF)
option(QWTPLOT3D_BUILD_COMPILER_WARNING "Build target with compiler warnings" OFF)
option(QWTPLOT3D_BUILD_INSTALL "Build with install" OFF)
option(QWTPLOT3D_BUILD_ALL "Build all artifacts" OFF)

if(QWTPLOT3D_BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ON CACHE BOOL "Build as shared libraries")
    message(STATUS "Build as shared libraries")
else()
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build as static libraries")
    message(STATUS "Build as static libraries")
endif()

if(QWTPLOT3D_BUILD_TESTS OR QWTPLOT3D_BUILD_ALL)
    enable_testing()
endif()

if(CMAKE_CONFIGURATION_TYPES)
    message(STATUS "QwtPlot3D CMAKE_CONFIGURATION_TYPES was set to: '${CMAKE_BUILD_TYPE}'")
    set(CMAKE_CONFIGURATION_TYPES "${CMAKE_BUILD_TYPE}" CACHE INTERNAL "Force disable CMAKE_CONFIGURATION_TYPES." FORCE)
endif()


#-----------------------------------------------------------------------------------------------------------------------
# Sources
#-----------------------------------------------------------------------------------------------------------------------
set(QWTPLOT3D_HEADERS
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
    ${PROJECT_SOURCE_DIR}/include/qwt3d_io_reader.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_label.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_mapping.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_openglhelper.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_parametricsurface.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_portability.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_scale.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_surfaceplot.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_types.h
    ${PROJECT_SOURCE_DIR}/include/qwt3d_volumeplot.h)

set(QWTPLOT3D_SOURCES
    ${PROJECT_SOURCE_DIR}/src/qwt3d_autoscaler.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_axis.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_colorlegend.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_coordsys.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_drawable.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_enrichment_std.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_function.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_gridmapping.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_gridplot.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_io.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_io_reader.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_label.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_lighting.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_meshplot.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_parametricsurface.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_scale.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_surfaceplot.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt3d_types.cpp)

set(QWTPLOT3D_3RDPARTY_SOURCES
    ${PROJECT_SOURCE_DIR}/3rdparty/gl2ps/gl2ps.c
    ${PROJECT_SOURCE_DIR}/3rdparty/gl2ps/gl2ps.h)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
if(QWTPLOT3D_BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED ${QWTPLOT3D_HEADERS} ${QWTPLOT3D_SOURCES} ${QWTPLOT3D_3RDPARTY_SOURCES})
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC
        $<$<BOOL:MSVC>:QWT3D_DLL>
        PRIVATE
        $<$<BOOL:MSVC>:QWT3D_MAKEDLL>)
else()
    add_library(${PROJECT_NAME} STATIC ${QWTPLOT3D_HEADERS} ${QWTPLOT3D_SOURCES})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

if(QWTPLOT3D_QT_VERSION_MAJOR EQUAL 4)
    target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Qt4::QtCore
        Qt4::QtGui
        Qt4::QtOpenGL)
else(QWTPLOT3D_QT_VERSION_MAJOR GREATER 4)
    target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Qt${QWTPLOT3D_QT_VERSION_MAJOR}::Core
        Qt${QWTPLOT3D_QT_VERSION_MAJOR}::Widgets
        Qt${QWTPLOT3D_QT_VERSION_MAJOR}::OpenGL)
endif()
include(cmake/FindWrapFreeGLUT.cmake)
target_link_libraries(${PROJECT_NAME} PUBLIC QwtPlot3D3rdparty::WrapFreeGLUT)

if(QWTPLOT3D_BUILD_INSTALL)
    include(GNUInstallDirs)
    install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}-target
        FRAMEWORK DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/QwtPlot3D
        ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR})

    install(FILES ${QWTPLOT3D_HEADERS}
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/QwtPlot3D)

    install(EXPORT ${PROJECT_NAME}-target
        FILE ${PROJECT_NAME}-targets.cmake
        NAMESPACE QwtPlot3D::
        DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}/cmake/QwtPlot3D")

    export(EXPORT ${PROJECT_NAME}-target
        FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-targets.cmake
        NAMESPACE QwtPlot3D::)

    include(CMakePackageConfigHelpers)
    set(INCLUDE_INSTALL_DIRS "${CMAKE_INSTALL_FULL_INCLUDEDIR}/QwtPlot3D")
    set(version_config "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake")
    set(project_config "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake")
    write_basic_package_version_file("${version_config}"
        VERSION ${QWTPLOT3D_VERSION}
        COMPATIBILITY SameMajorVersion)
    configure_package_config_file(${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in "${project_config}"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
        PATH_VARS INCLUDE_INSTALL_DIRS)
    install(FILES "${project_config}" "${version_config}"
        DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}/cmake/${PROJECT_NAME}")
endif()


#-----------------------------------------------------------------------------------------------------------------------
# Add subdirectory
#-----------------------------------------------------------------------------------------------------------------------
if(QWTPLOT3D_BUILD_EXAMPLES OR QWTPLOT3D_BUILD_ALL)
    add_subdirectory(examples)
endif()
message(STATUS "QwtPlot3D Configuring Generating Done")
