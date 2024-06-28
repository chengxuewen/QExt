#-----------------------------------------------------------------------------------------------------------------------
# Set cmake min version and policy
#-----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)


#-----------------------------------------------------------------------------------------------------------------------
# Set project name and version
#-----------------------------------------------------------------------------------------------------------------------
project(QtWebApp VERSION 1.9.0 LANGUAGES CXX)
set(QtWebApp_VERSION_NAME ${PROJECT_VERSION})
set(QtWebApp_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(QtWebApp_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(QtWebApp_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(QtWebApp_VERSION_TWEAK ${PROJECT_VERSION_TWEAK})
set(QtWebApp_VERSION ${QtWebApp_VERSION_MAJOR}.${QtWebApp_VERSION_MINOR}.${QtWebApp_VERSION_PATCH})
set(QtWebApp_SO_VERSION ${QtWebApp_VERSION_MAJOR}.${QtWebApp_VERSION_MINOR})
set(QtWebApp_DEBUG_POSTFIX "d")
set(QtWebApp_VERSION_STR "${QtWebApp_VERSION_MAJOR}.${QtWebApp_VERSION_MINOR}.${QtWebApp_VERSION_PATCH}")
set(QtWebApp_LICENSE "LGPL License")
set(QtWebApp_PRODUCT_NAME "QtWebApp")
set(QtWebApp_CXX_STANDARD 98)
math(EXPR QtWebApp_VERSION_CALC "${QtWebApp_VERSION_MAJOR}*1000 + ${QtWebApp_VERSION_MINOR}*100 + ${QtWebApp_VERSION_PATCH}")
message(STATUS "Project version: QtWebApp ${QtWebApp_VERSION}")
message(STATUS "Project license: ${QtWebApp_LICENSE}")


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
set(QtWebApp_QT_VERSION_MAJOR ${QT_VERSION_MAJOR})
set(QtWebApp_QT_VERSION_MINOR ${QT_VERSION_MINOR})
set(QtWebApp_QT_VERSION_PATCH ${QT_VERSION_PATCH})
set(QtWebApp_QT_VERSION "${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")
set(QtWebApp_QT_OPENGL_FOUND OFF)
set(QtWebApp_QT_OPENGL)
if(QtWebApp_QT_VERSION_MAJOR EQUAL 4)
    if(QtWebApp_QT_VERSION_MINOR LESS 5)
        message(FATAL_ERROR "Expected Qt4 version must greater than or equal to Qt4.5")
    endif()
    message(STATUS "Expected Qt version is Qt4")
    set(QtWebApp_QT_DEP_COMPONENTS QtCore QtNetwork)
    find_package(Qt4 COMPONENTS ${QtWebApp_QT_DEP_COMPONENTS} REQUIRED)
    INCLUDE(${QT_USE_FILE})
    ADD_DEFINITIONS(${QT_DEFINITIONS})
elseif(QtWebApp_QT_VERSION_MAJOR EQUAL 5)
    message(STATUS "Expected Qt version is Qt${QtWebApp_QT_VERSION}")
    set(QtWebApp_QT_DEP_COMPONENTS Core Network)
    find_package(Qt${QtWebApp_QT_VERSION_MAJOR} COMPONENTS ${QtWebApp_QT_DEP_COMPONENTS} REQUIRED)
elseif(QtWebApp_QT_VERSION_MAJOR EQUAL 6)
    message(STATUS "Expected Qt version is Qt${QtWebApp_QT_VERSION}")
    set(QtWebApp_QT_DEP_COMPONENTS Core Network Compat)
    find_package(Qt${QtWebApp_QT_VERSION_MAJOR} COMPONENTS ${QtWebApp_QT_DEP_COMPONENTS} REQUIRED)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()
set(QtWebApp_QT_FINDPKG_CMD Qt${QtWebApp_QT_VERSION_MAJOR} COMPONENTS ${QtWebApp_QT_DEP_COMPONENTS} REQUIRED)
string(REPLACE ";" " " QtWebApp_QT_FINDPKG_CMDSTR "${QtWebApp_QT_FINDPKG_CMD}")

get_filename_component(QtWebApp_QT_BIN_DIR "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
get_filename_component(QtWebApp_QT_KIT_DIR "${QtWebApp_QT_BIN_DIR}" DIRECTORY)
set(QtWebApp_QT_LIB_DIR ${QtWebApp_QT_KIT_DIR}/lib)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


#-----------------------------------------------------------------------------------------------------------------------
# Set option
#-----------------------------------------------------------------------------------------------------------------------
option(QtWebApp_BUILD_SHARED_LIBS "Build shared library" ON)
option(QtWebApp_BUILD_EXAMPLES "Build examples" ON)
option(QtWebApp_BUILD_COMPILER_WARNING "Build target with compiler warnings" OFF)
option(QtWebApp_BUILD_INSTALL "Build with install" OFF)
option(QtWebApp_BUILD_ALL "Build all artifacts" OFF)

if(QtWebApp_BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ON CACHE BOOL "Build as shared libraries")
    message(STATUS "Build as shared libraries")
else()
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build as static libraries")
    message(STATUS "Build as static libraries")
endif()

if(QtWebApp_BUILD_TESTS OR QtWebApp_BUILD_ALL)
    enable_testing()
endif()


#-----------------------------------------------------------------------------------------------------------------------
# Sources
#-----------------------------------------------------------------------------------------------------------------------
set(QtWebApp_HTTPSERVER_HEADERS
    ${PROJECT_SOURCE_DIR}/QtWebApp/httpserver/httpglobal.h
    ${PROJECT_SOURCE_DIR}/QtWebApp/httpserver/httplistener.h
    ${PROJECT_SOURCE_DIR}/QtWebApp/httpserver/httpconnectionhandler.h
    ${PROJECT_SOURCE_DIR}/QtWebApp/httpserver/httpconnectionhandlerpool.h
    ${PROJECT_SOURCE_DIR}/QtWebApp/httpserver/httprequest.h
    ${PROJECT_SOURCE_DIR}/QtWebApp/httpserver/httpresponse.h
    ${PROJECT_SOURCE_DIR}/QtWebApp/httpserver/httpcookie.h
    ${PROJECT_SOURCE_DIR}/QtWebApp/httpserver/httprequesthandler.h
    ${PROJECT_SOURCE_DIR}/QtWebApp/httpserver/httpsession.h
    ${PROJECT_SOURCE_DIR}/QtWebApp/httpserver/httpsessionstore.h
    ${PROJECT_SOURCE_DIR}/QtWebApp/httpserver/staticfilecontroller.h)

set(QtWebApp_LOGGING_HEADERS
    ${PROJECT_SOURCE_DIR}/QtWebApp/logging/logglobal.h
    ${PROJECT_SOURCE_DIR}/QtWebApp/logging/logmessage.h
    ${PROJECT_SOURCE_DIR}/QtWebApp/logging/logger.h
    ${PROJECT_SOURCE_DIR}/QtWebApp/logging/filelogger.h
    ${PROJECT_SOURCE_DIR}/QtWebApp/logging/dualfilelogger.h)

set(QtWebApp_TEMPLATEENGINE_HEADERS
    ${PROJECT_SOURCE_DIR}/QtWebApp/templateengine/templateglobal.h
    ${PROJECT_SOURCE_DIR}/QtWebApp/templateengine/template.h
    ${PROJECT_SOURCE_DIR}/QtWebApp/templateengine/templateloader.h
    ${PROJECT_SOURCE_DIR}/QtWebApp/templateengine/templatecache.h)

set(QtWebApp_SOURCES
    ${PROJECT_SOURCE_DIR}/QtWebApp/httpserver/httpglobal.cpp
    ${PROJECT_SOURCE_DIR}/QtWebApp/httpserver/httplistener.cpp
    ${PROJECT_SOURCE_DIR}/QtWebApp/httpserver/httpconnectionhandler.cpp
    ${PROJECT_SOURCE_DIR}/QtWebApp/httpserver/httpconnectionhandlerpool.cpp
    ${PROJECT_SOURCE_DIR}/QtWebApp/httpserver/httprequest.cpp
    ${PROJECT_SOURCE_DIR}/QtWebApp/httpserver/httpresponse.cpp
    ${PROJECT_SOURCE_DIR}/QtWebApp/httpserver/httpcookie.cpp
    ${PROJECT_SOURCE_DIR}/QtWebApp/httpserver/httprequesthandler.cpp
    ${PROJECT_SOURCE_DIR}/QtWebApp/httpserver/httpsession.cpp
    ${PROJECT_SOURCE_DIR}/QtWebApp/httpserver/httpsessionstore.cpp
    ${PROJECT_SOURCE_DIR}/QtWebApp/httpserver/staticfilecontroller.cpp

    ${PROJECT_SOURCE_DIR}/QtWebApp/logging/logmessage.cpp
    ${PROJECT_SOURCE_DIR}/QtWebApp/logging/logger.cpp
    ${PROJECT_SOURCE_DIR}/QtWebApp/logging/filelogger.cpp
    ${PROJECT_SOURCE_DIR}/QtWebApp/logging/dualfilelogger.cpp

    ${PROJECT_SOURCE_DIR}/QtWebApp/templateengine/template.cpp
    ${PROJECT_SOURCE_DIR}/QtWebApp/templateengine/templateloader.cpp
    ${PROJECT_SOURCE_DIR}/QtWebApp/templateengine/templatecache.cpp)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
if(QtWebApp_BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME}
        SHARED
        ${QtWebApp_HTTPSERVER_HEADERS}
        ${QtWebApp_LOGGING_HEADERS}
        ${QtWebApp_TEMPLATEENGINE_HEADERS}
        ${QtWebApp_SOURCES})
else()
    add_library(${PROJECT_NAME}
        STATIC
        ${QtWebApp_HTTPSERVER_HEADERS}
        ${QtWebApp_LOGGING_HEADERS}
        ${QtWebApp_TEMPLATEENGINE_HEADERS}
        ${QtWebApp_SOURCES})
endif()
target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/QtWebApp>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/QtWebApp/httpserver>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/QtWebApp/logging>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/QtWebApp/templateengine>)
target_compile_definitions(${PROJECT_NAME} PRIVATE QT_NO_SSL)

if(QtWebApp_QT_VERSION_MAJOR EQUAL 4)
    target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Qt4::QtCore
        Qt4::QtNetwork)
else(QtWebApp_QT_VERSION_MAJOR GREATER 4)
    target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Qt${QtWebApp_QT_VERSION_MAJOR}::Core
        Qt${QtWebApp_QT_VERSION_MAJOR}::Network)
endif()
if(QtWebApp_QT_VERSION_MAJOR EQUAL 6)
    target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Qt${QtWebApp_QT_VERSION_MAJOR}::Compat)
endif()

if(QtWebApp_BUILD_INSTALL)
    include(GNUInstallDirs)
    install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}-target
        FRAMEWORK DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/QtWebApp
        ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR})

    install(FILES ${QtWebApp_HEADERS}
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/QtWebApp)

    install(EXPORT ${PROJECT_NAME}-target
        FILE ${PROJECT_NAME}-targets.cmake
        NAMESPACE QtWebApp::
        DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}/cmake/QtWebApp")

    export(EXPORT ${PROJECT_NAME}-target
        FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-targets.cmake
        NAMESPACE QtWebApp::)

    include(CMakePackageConfigHelpers)
    set(INCLUDE_INSTALL_DIRS "${CMAKE_INSTALL_FULL_INCLUDEDIR}/QtWebApp")
    set(version_config "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake")
    set(project_config "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake")
    write_basic_package_version_file("${version_config}"
        VERSION ${QtWebApp_VERSION}
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
if(QtWebApp_BUILD_EXAMPLES OR QtWebApp_BUILD_ALL)
    set(QtWebApp_EXAMPLE_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
    function(QtWebApp_add_example NAME)
        set(multiValueArgs SOURCES INCLUDE_DIRS LIBRARIES)
        cmake_parse_arguments(arg "" "" "${multiValueArgs}" "${ARGN}")
        add_executable(${NAME} ${arg_SOURCES})
        target_include_directories(${NAME} PRIVATE ${INCLUDE_DIRS})
        target_link_libraries(${NAME} PRIVATE ${PROJECT_NAME} ${LIBRARIES})
        set_target_properties(${NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${QtWebApp_EXAMPLE_OUTPUT_DIR}/${NAME}
            LIBRARY_OUTPUT_DIRECTORY ${QtWebApp_EXAMPLE_OUTPUT_DIR}/${NAME}
            ARCHIVE_OUTPUT_DIRECTORY ${QtWebApp_EXAMPLE_OUTPUT_DIR}/${NAME})
    endfunction()
    QtWebApp_add_example(QtWebAppDemo1
        SOURCES
        Demo1/src/controller/dumpcontroller.cpp
        Demo1/src/controller/dumpcontroller.h
        Demo1/src/controller/fileuploadcontroller.cpp
        Demo1/src/controller/fileuploadcontroller.h
        Demo1/src/controller/formcontroller.cpp
        Demo1/src/controller/formcontroller.h
        Demo1/src/controller/logincontroller.cpp
        Demo1/src/controller/logincontroller.h
        Demo1/src/controller/sessioncontroller.cpp
        Demo1/src/controller/sessioncontroller.h
        Demo1/src/controller/templatecontroller.cpp
        Demo1/src/controller/templatecontroller.h
        Demo1/src/documentcache.h
        Demo1/src/global.cpp
        Demo1/src/global.h
        Demo1/src/main.cpp
        Demo1/src/requestmapper.cpp
        Demo1/src/requestmapper.h
        INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/Demo1/src)
    add_custom_command(
        TARGET QtWebAppDemo1
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Demo1/etc ${QtWebApp_EXAMPLE_OUTPUT_DIR}/QtWebAppDemo1
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Demo1/logs ${QtWebApp_EXAMPLE_OUTPUT_DIR}/QtWebAppDemo1
        COMMENT "copy the QtWebAppDemo1 dep files to the output dir"
        POST_BUILD)

    QtWebApp_add_example(QtWebAppDemo2
        SOURCES
        Demo2/src/main.cpp
        Demo2/src/requesthandler.cpp
        Demo2/src/requesthandler.h
        INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/Demo2/src)
endif()
