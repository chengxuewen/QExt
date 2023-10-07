#################################################################################
#
# Library: QExt
#
# Copyright (c) ChengXueWen. Contact: 1398831004@qq.com
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0.txt
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#################################################################################

#--------------------------------------------------------------------------------
# Set lib base name and out put path
#--------------------------------------------------------------------------------
set(EXECUTABLE_OUTPUT_PATH ${QEXT_TEST_OUTPUT_DIR}/qml/vlc)
set(LIBRARY_OUTPUT_PATH ${QEXT_TEST_OUTPUT_DIR}/qml/vlc)
set(TEST_SOURCE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/player)
set(QEXT_TEST_CONFIG_FILE_DIR ${QEXT_TEST_OUTPUT_DIR}/qml/vlc)
set(QEXT_TEST_CONFIG_FILE_PATH ${QEXT_TEST_CONFIG_FILE_DIR}/qextQmlVLCTestConfig.h)
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/qextQmlVLCTestConfig.h.in"
    "${QEXT_TEST_CONFIG_FILE_PATH}"
    )
set(QEXT_QML_IMPORT_PATH ${QML_IMPORT_PATH} ${QEXT_QML_OUTPUT_DIR} ${QEXT_QML_SOURCE_DIR})
set(QML_IMPORT_PATH "${QEXT_QML_IMPORT_PATH}" CACHE STRING "Qt Creator extra qml import paths" FORCE)



#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(QEXT_TEST_LINK_LIBRARIES)
set(QEXT_TEST_INCLUDE_DIRECTORIES)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_TEST_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui Qt4::QtTest)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_TEST_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Qml
        Qt${QEXT_QT_VERSION_MAJOR}::Quick
        Qt${QEXT_QT_VERSION_MAJOR}::Test
        )
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_TEST_LINK_LIBRARIES QEXTCore QEXTQmlVLC)

ADD_DEFINITIONS(-DQUICK_TEST_SOURCE_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/player/\")



#--------------------------------------------------------------------------------
# define function
#--------------------------------------------------------------------------------
function(qextFunctionAddQmlVLCTest TEST_NAME)
    set(multiValueArgs TEST_SOURCE TEST_INCLUDE_DIRS TEST_SOURCE_DIRS)
    cmake_parse_arguments(MY "" "" "${multiValueArgs}" "${ARGN}")
    add_executable(${TEST_NAME} ${MY_TEST_SOURCE} ${QEXT_TEST_CONFIG_FILE_PATH})
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    target_link_libraries(${TEST_NAME} PRIVATE ${QEXT_TEST_LINK_LIBRARIES})
    target_include_directories(${TEST_NAME} PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${MY_TEST_INCLUDE_DIRS}
        ${QEXT_TEST_INCLUDE_DIRECTORIES}
        ${QEXT_TEST_CONFIG_FILE_DIR}
        )
#    add_custom_target(${TEST_NAME}_env
#        COMMAND ${CMAKE_COMMAND} -E env "QUICK_TEST_SOURCE_DIR=${MY_TEST_SOURCE_DIRS}"
#    )
#    add_custom_command(
#        TARGET ${TEST_NAME}
#        COMMAND ${CMAKE_COMMAND} -E env "QUICK_TEST_SOURCE_DIR=${MY_TEST_SOURCE_DIRS}"
#        PRE_BUILD
#    )
    if(QEXT_BUILD_SHARED_LIBS AND WIN32)
        qextFunctionCopyDependencyInternal(${TEST_NAME}
            QEXTCore
            QEXTQmlVLC
            ${EXECUTABLE_OUTPUT_PATH}
            )
    endif()
endfunction()


##--------------------------------------------------------------------------------
## Add test
##--------------------------------------------------------------------------------
qextFunctionAddQmlVLCTest(qext_tst_qmlVLCPlayer
    TEST_SOURCE
    player/TestQml.cpp
    TEST_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/player
    TEST_SOURCE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/player
    )

