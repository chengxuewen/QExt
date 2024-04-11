cmake_minimum_required(VERSION 3.12.0)

project(SingleApplication VERSION 3.5.1 LANGUAGES CXX DESCRIPTION "Replacement for QtSingleApplication")
set(SINGLEAPPLICATION_VERSION_NAME ${PROJECT_VERSION})
set(SINGLEAPPLICATION_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(SINGLEAPPLICATION_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(SINGLEAPPLICATION_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(SINGLEAPPLICATION_VERSION_TWEAK ${PROJECT_VERSION_TWEAK})
set(SINGLEAPPLICATION_VERSION ${SINGLEAPPLICATION_VERSION_MAJOR}.${SINGLEAPPLICATION_VERSION_MINOR}.${SINGLEAPPLICATION_VERSION_PATCH})

set(CMAKE_AUTOMOC ON)

configure_file("singleapplication_config.h.in" "${CMAKE_CURRENT_BINARY_DIR}/singleapplication_config.h")
add_library(${PROJECT_NAME} STATIC
    singleapplication.cpp
    singleapplication.h
    singleapplication_p.cpp
    singleapplication_p.h
    ${CMAKE_CURRENT_BINARY_DIR}/singleapplication_config.h)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
set(SINGLEAPPLICATION_HEADERS singleapplication.h ${CMAKE_CURRENT_BINARY_DIR}/singleapplication_config.h)

if(NOT QT_DEFAULT_MAJOR_VERSION)
    set(QT_DEFAULT_MAJOR_VERSION 5 CACHE STRING "Qt version to use (5 or 6), defaults to 5")
endif()

# Find dependencies
set(QT_COMPONENTS Core Network)
set(QT_LIBRARIES Qt${QT_DEFAULT_MAJOR_VERSION}::Core Qt${QT_DEFAULT_MAJOR_VERSION}::Network)

if(NOT "${USER_QAPPLICATION_CLASS}" STREQUAL "")
    set(QAPPLICATION_CLASS ${USER_QAPPLICATION_CLASS})
endif()
if(QAPPLICATION_CLASS STREQUAL QApplication)
    list(APPEND QT_COMPONENTS Widgets)
    list(APPEND QT_LIBRARIES Qt${QT_DEFAULT_MAJOR_VERSION}::Widgets)
elseif(QAPPLICATION_CLASS STREQUAL QGuiApplication)
    list(APPEND QT_COMPONENTS Gui)
    list(APPEND QT_LIBRARIES Qt${QT_DEFAULT_MAJOR_VERSION}::Gui)
else()
    set(QAPPLICATION_CLASS QCoreApplication)
endif()
find_package(Qt${QT_DEFAULT_MAJOR_VERSION} COMPONENTS ${QT_COMPONENTS} REQUIRED)
set(SINGLEAPPLICATION_QT_FINDPKG_CMD Qt${QT_DEFAULT_MAJOR_VERSION} COMPONENTS ${QT_COMPONENTS} REQUIRED)
string(REPLACE ";" " " SINGLEAPPLICATION_QT_FINDPKG_CMDSTR "${SINGLEAPPLICATION_QT_FINDPKG_CMD}")


target_link_libraries(${PROJECT_NAME} PUBLIC ${QT_LIBRARIES})
if(WIN32)
    find_library(advapi32_LIBRARY advapi32 REQUIRED)
    mark_as_advanced(advapi32_LIBRARY)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${advapi32_LIBRARY})
endif()
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)
target_compile_definitions(${PROJECT_NAME} PUBLIC QAPPLICATION_CLASS=${QAPPLICATION_CLASS})
target_compile_definitions(${PROJECT_NAME} PRIVATE
    QT_NO_CAST_TO_ASCII
    QT_NO_CAST_FROM_ASCII
    QT_NO_URL_CAST_FROM_STRING
    QT_NO_CAST_FROM_BYTEARRAY
    QT_USE_QSTRINGBUILDER
    QT_NO_NARROWING_CONVERSIONS_IN_CONNECT
    QT_NO_KEYWORDS
    QT_NO_FOREACH)


option(SINGLEAPPLICATION_DOCUMENTATION "Generate Doxygen documentation" OFF)
if(SINGLEAPPLICATION_DOCUMENTATION)
    find_package(Doxygen)
endif()
if(DOXYGEN_FOUND)
    # Doxygen theme
    include(FetchContent)
    FetchContent_Declare(DoxygenAwesome # 2.0.3
        GIT_REPOSITORY https://github.com/jothepro/doxygen-awesome-css
        GIT_TAG 4cd62308d825fe0396d2f66ffbab45d0e247724c)
    FetchContent_MakeAvailable(DoxygenAwesome)
    FetchContent_GetProperties(DoxygenAwesome SOURCE_DIR DoxygenAwesome_SOURCE_DIR)

    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)
    set(DOXYGEN_GENERATE_TREEVIEW YES)
    set(DOXYGEN_HTML_HEADER ${DoxygenAwesome_SOURCE_DIR}/doxygen-custom/header.html)
    set(DOXYGEN_HTML_EXTRA_STYLESHEET ${DoxygenAwesome_SOURCE_DIR}/doxygen-awesome.css)
    set(DOXYGEN_HTML_EXTRA_FILES
        ${DoxygenAwesome_SOURCE_DIR}/doxygen-awesome-fragment-copy-button.js
        ${DoxygenAwesome_SOURCE_DIR}/doxygen-awesome-paragraph-link.js
        ${DoxygenAwesome_SOURCE_DIR}/doxygen-awesome-darkmode-toggle.js)

    doxygen_add_docs(${PROJECT_NAME}Documentation
        singleapplication.h
        CHANGELOG.md
        Windows.md
        README.md)
endif()

option(SINGLEAPPLICATION_BUILD_INSTALL "Build with install" OFF)
if(SINGLEAPPLICATION_BUILD_INSTALL)
    include(GNUInstallDirs)
    install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}-target
        FRAMEWORK DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR})

    install(FILES ${SINGLEAPPLICATION_HEADERS}
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR})

    install(EXPORT ${PROJECT_NAME}-target
        FILE ${PROJECT_NAME}-targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}/cmake/${PROJECT_NAME}")

    export(EXPORT ${PROJECT_NAME}-target
        FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-targets.cmake
        NAMESPACE ${PROJECT_NAME}::)

    include(CMakePackageConfigHelpers)
    set(INCLUDE_INSTALL_DIRS "${CMAKE_INSTALL_FULL_INCLUDEDIR}")
    set(version_config "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake")
    set(project_config "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake")
    write_basic_package_version_file("${version_config}"
        VERSION ${SINGLEAPPLICATION_VERSION}
        COMPATIBILITY SameMajorVersion)
    configure_package_config_file(${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in "${project_config}"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
        PATH_VARS INCLUDE_INSTALL_DIRS)
    install(FILES "${project_config}" "${version_config}"
        DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}/cmake/${PROJECT_NAME}")
endif()
