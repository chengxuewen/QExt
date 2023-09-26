############################################################################
# CMakeLists.txt file for building qcustomplot static library
############################################################################
set(library_name qcustomplot)


find_package(Qt4 QUIET COMPONENTS QtCore QUIET)
if (NOT QT_FOUND)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core QUIET)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core QUIET)
endif()
set(QCP_QT_VERSION_MAJOR ${QT_VERSION_MAJOR})
set(QCP_QT_VERSION_MINOR ${QT_VERSION_MINOR})
set(QCP_QT_VERSION_PATCH ${QT_VERSION_PATCH})
set(QCP_QT_VERSION "${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")
set(QCP_QT_OPENGL_FOUND OFF)
set(QCP_QT_OPENGL)
if (QCP_QT_VERSION_MAJOR EQUAL 4)
    if (QCP_QT_VERSION_MINOR LESS 5)
        message(FATAL_ERROR "----qcustomplot---- Expected Qt4 version must greater than or equal to Qt4.5")
    endif()
    message(STATUS "----qcustomplot---- Expected Qt version is Qt${QCP_QT_VERSION}")
    find_package(Qt4 REQUIRED QtCore QtGui)
    INCLUDE(${QT_USE_FILE})
    ADD_DEFINITIONS(${QT_DEFINITIONS})
elseif(QCP_QT_VERSION_MAJOR GREATER 4)
    message(STATUS "----qcustomplot---- Expected Qt version is Qt${QCP_QT_VERSION}")
    find_package(Qt${QCP_QT_VERSION_MAJOR} COMPONENTS Core Widgets PrintSupport REQUIRED)
else()
    message(FATAL_ERROR "----qcustomplot---- Not find Qt package")
endif()

get_filename_component(QCP_QT_BIN_DIR "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
get_filename_component(QCP_QT_KIT_DIR "${QCP_QT_BIN_DIR}" DIRECTORY)
set(QCP_QT_LIB_DIR ${QCP_QT_KIT_DIR}/lib)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


if(QCP_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QCP_LIB_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui Qt4::QtPrintSupport)
elseif(QCP_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QCP_LIB_LINK_LIBRARIES
        Qt${QCP_QT_VERSION_MAJOR}::Core
        Qt${QCP_QT_VERSION_MAJOR}::Widgets
        Qt${QCP_QT_VERSION_MAJOR}::PrintSupport
        )
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

add_library(${library_name} STATIC qcustomplot.h qcustomplot.cpp)
target_link_libraries(${library_name} PUBLIC ${QCP_LIB_LINK_LIBRARIES})
target_include_directories(${library_name} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
