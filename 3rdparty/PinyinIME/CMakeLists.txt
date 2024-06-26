#-----------------------------------------------------------------------------------------------------------------------
# Set cmake min version and policy
#-----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)


#-----------------------------------------------------------------------------------------------------------------------
# Set project name and version
#-----------------------------------------------------------------------------------------------------------------------
project(PinyinIME VERSION 0.1.1.1 LANGUAGES CXX)
set(PinyinIME_VERSION_NAME ${PROJECT_VERSION})
set(PinyinIME_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(PinyinIME_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(PinyinIME_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(PinyinIME_VERSION_TWEAK ${PROJECT_VERSION_TWEAK})
set(PinyinIME_VERSION ${PinyinIME_VERSION_MAJOR}.${PinyinIME_VERSION_MINOR}.${PinyinIME_VERSION_PATCH})
set(PinyinIME_SO_VERSION ${PinyinIME_VERSION_MAJOR}.${PinyinIME_VERSION_MINOR})
set(PinyinIME_DEBUG_POSTFIX "d")
set(PinyinIME_VERSION_STR "${PinyinIME_VERSION_MAJOR}.${PinyinIME_VERSION_MINOR}.${PinyinIME_VERSION_PATCH}")
set(PinyinIME_LICENSE "Apache License")
set(PinyinIME_PRODUCT_NAME "PinyinIME")
set(PinyinIME_CXX_STANDARD 98)
math(EXPR PinyinIME_VERSION_CALC "${PinyinIME_VERSION_MAJOR}*1000 + ${PinyinIME_VERSION_MINOR}*100 + ${PinyinIME_VERSION_PATCH}")
message(STATUS "Project version: PinyinIME ${PinyinIME_VERSION}")
message(STATUS "Project license: ${PinyinIME_LICENSE}")


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
set(PinyinIME_QT_VERSION_MAJOR ${QT_VERSION_MAJOR})
set(PinyinIME_QT_VERSION_MINOR ${QT_VERSION_MINOR})
set(PinyinIME_QT_VERSION_PATCH ${QT_VERSION_PATCH})
set(PinyinIME_QT_VERSION "${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")
if(PinyinIME_QT_VERSION_MAJOR EQUAL 4)
    if(PinyinIME_QT_VERSION_MINOR LESS 5)
        message(FATAL_ERROR "Expected Qt4 version must greater than or equal to Qt4.5")
    endif()
    message(STATUS "Expected Qt version is Qt4")
    set(PinyinIME_QT_DEP_COMPONENTS QtCore)
    find_package(Qt4 COMPONENTS ${PinyinIME_QT_DEP_COMPONENTS} REQUIRED)
    INCLUDE(${QT_USE_FILE})
    ADD_DEFINITIONS(${QT_DEFINITIONS})
elseif(PinyinIME_QT_VERSION_MAJOR EQUAL 5)
    message(STATUS "Expected Qt version is Qt${PinyinIME_QT_VERSION}")
    set(PinyinIME_QT_DEP_COMPONENTS Core)
    find_package(Qt${PinyinIME_QT_VERSION_MAJOR} COMPONENTS ${PinyinIME_QT_DEP_COMPONENTS} REQUIRED)
elseif(PinyinIME_QT_VERSION_MAJOR EQUAL 6)
    message(STATUS "Expected Qt version is Qt${PinyinIME_QT_VERSION}")
    set(PinyinIME_QT_DEP_COMPONENTS Core)
    find_package(Qt${PinyinIME_QT_VERSION_MAJOR} COMPONENTS ${PinyinIME_QT_DEP_COMPONENTS} REQUIRED)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()
set(PinyinIME_QT_FINDPKG_CMD Qt${PinyinIME_QT_VERSION_MAJOR} COMPONENTS ${PinyinIME_QT_DEP_COMPONENTS} REQUIRED)
string(REPLACE ";" " " PinyinIME_QT_FINDPKG_CMDSTR "${PinyinIME_QT_FINDPKG_CMD}")

get_filename_component(PinyinIME_QT_BIN_DIR "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
get_filename_component(PinyinIME_QT_KIT_DIR "${PinyinIME_QT_BIN_DIR}" DIRECTORY)
set(PinyinIME_QT_LIB_DIR ${PinyinIME_QT_KIT_DIR}/lib)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


#-----------------------------------------------------------------------------------------------------------------------
# Set option
#-----------------------------------------------------------------------------------------------------------------------
option(PinyinIME_BUILD_SHARED_LIBS "Build shared library" OFF)
option(PinyinIME_BUILD_TESTS "Build tests" OFF)
option(PinyinIME_BUILD_EXAMPLES "Build examples" OFF)
option(PinyinIME_BUILD_COMPILER_WARNING "Build target with compiler warnings" OFF)
option(PinyinIME_BUILD_INSTALL "Build with install" OFF)
option(PinyinIME_BUILD_ALL "Build all artifacts" OFF)

if(PinyinIME_BUILD_TESTS OR PinyinIME_BUILD_ALL)
    enable_testing()
endif()


#-----------------------------------------------------------------------------------------------------------------------
# Sources
#-----------------------------------------------------------------------------------------------------------------------
set(PinyinIME_HEADERS
    ${PROJECT_SOURCE_DIR}/include/atomdictbase.h
    ${PROJECT_SOURCE_DIR}/include/dictbuilder.h
    ${PROJECT_SOURCE_DIR}/include/dictdef.h
    ${PROJECT_SOURCE_DIR}/include/dictlist.h
    ${PROJECT_SOURCE_DIR}/include/dicttrie.h
    ${PROJECT_SOURCE_DIR}/include/lpicache.h
    ${PROJECT_SOURCE_DIR}/include/matrixsearch.h
    ${PROJECT_SOURCE_DIR}/include/mystdlib.h
    ${PROJECT_SOURCE_DIR}/include/ngram.h
    ${PROJECT_SOURCE_DIR}/include/pinyinime.h
    ${PROJECT_SOURCE_DIR}/include/searchutility.h
    ${PROJECT_SOURCE_DIR}/include/spellingtable.h
    ${PROJECT_SOURCE_DIR}/include/spellingtrie.h
    ${PROJECT_SOURCE_DIR}/include/splparser.h
    ${PROJECT_SOURCE_DIR}/include/sync.h
    ${PROJECT_SOURCE_DIR}/include/userdict.h
    ${PROJECT_SOURCE_DIR}/include/utf16char.h
    ${PROJECT_SOURCE_DIR}/include/utf16reader.h)

set(PinyinIME_SOURCES
    ${PROJECT_SOURCE_DIR}/share/dictbuilder.cpp
    ${PROJECT_SOURCE_DIR}/share/dictlist.cpp
    ${PROJECT_SOURCE_DIR}/share/dicttrie.cpp
    ${PROJECT_SOURCE_DIR}/share/lpicache.cpp
    ${PROJECT_SOURCE_DIR}/share/matrixsearch.cpp
    ${PROJECT_SOURCE_DIR}/share/mystdlib.cpp
    ${PROJECT_SOURCE_DIR}/share/ngram.cpp
    ${PROJECT_SOURCE_DIR}/share/pinyinime.cpp
    ${PROJECT_SOURCE_DIR}/share/searchutility.cpp
    ${PROJECT_SOURCE_DIR}/share/spellingtable.cpp
    ${PROJECT_SOURCE_DIR}/share/spellingtrie.cpp
    ${PROJECT_SOURCE_DIR}/share/splparser.cpp
    ${PROJECT_SOURCE_DIR}/share/sync.cpp
    ${PROJECT_SOURCE_DIR}/share/userdict.cpp
    ${PROJECT_SOURCE_DIR}/share/utf16char.cpp
    ${PROJECT_SOURCE_DIR}/share/utf16reader.cpp)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
if(PinyinIME_BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED ${PinyinIME_HEADERS} ${PinyinIME_SOURCES})
else()
    add_library(${PROJECT_NAME} STATIC ${PinyinIME_HEADERS} ${PinyinIME_SOURCES})
endif()
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    QT_NO_CAST_TO_ASCII
    QT_ASCII_CAST_WARNINGS
    QT_NO_CAST_FROM_ASCII
    QT_NO_CAST_FROM_BYTEARRAY)
if(PinyinIME_QT_VERSION_MAJOR EQUAL 4)
    target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Qt4::QtCore)
else(PinyinIME_QT_VERSION_MAJOR GREATER 4)
    target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Qt${PinyinIME_QT_VERSION_MAJOR}::Core)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(WARNINGS "-w")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(WARNINGS "-w")
elseif(MSVC)
    string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    set(WARNINGS "${WARNINGS} /W0")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNINGS}")

if(PinyinIME_BUILD_INSTALL)
    include(GNUInstallDirs)
    install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}-target
        FRAMEWORK DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/PinyinIME
        ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR})

    install(FILES ${PinyinIME_HEADERS}
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/PinyinIME)

    install(EXPORT ${PROJECT_NAME}-target
        FILE ${PROJECT_NAME}-targets.cmake
        NAMESPACE PinyinIME::
        DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}/cmake/PinyinIME")

    export(EXPORT ${PROJECT_NAME}-target
        FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-targets.cmake
        NAMESPACE PinyinIME::)

    include(CMakePackageConfigHelpers)
    set(INCLUDE_INSTALL_DIRS "${CMAKE_INSTALL_FULL_INCLUDEDIR}/PinyinIME")
    set(version_config "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake")
    set(project_config "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake")
    write_basic_package_version_file("${version_config}"
        VERSION ${PinyinIME_VERSION}
        COMPATIBILITY SameMajorVersion)
    configure_package_config_file(${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in "${project_config}"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
        PATH_VARS INCLUDE_INSTALL_DIRS)
    install(FILES "${project_config}" "${version_config}"
        DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}/cmake/${PROJECT_NAME}")
endif()
