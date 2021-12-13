#################################################################################
#
# Library: QEXT
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
set(EXECUTABLE_OUTPUT_PATH ${QEXT_TEST_OUTPUT_DIR}/vlc)
set(LIBRARY_OUTPUT_PATH ${QEXT_TEST_OUTPUT_DIR}/vlc)



#--------------------------------------------------------------------------------
# Configure a header file to pass some of the CMake settings to the source code
#--------------------------------------------------------------------------------
set(QEXT_TEST_SAMPLES_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(QEXT_TEST_CONFIG_HPP_FILE_DIR ${EXECUTABLE_OUTPUT_PATH})
set(QEXT_TEST_CONFIG_HPP_FILE_PATH ${QEXT_TEST_CONFIG_HPP_FILE_DIR}/TestsConfig.h)
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/TestsConfig.h.in"
    "${QEXT_TEST_CONFIG_HPP_FILE_PATH}"
    )



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
        Qt${QEXT_QT_VERSION_MAJOR}::Test
        )
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND QEXT_TEST_LINK_LIBRARIES QEXTCore QEXTVLC)
list(APPEND QEXT_TEST_INCLUDE_DIRECTORIES ${QEXT_TEST_CONFIG_HPP_FILE_DIR})



#--------------------------------------------------------------------------------
# define function
#--------------------------------------------------------------------------------
function(qextFunctionAddVLCTest TEST_NAME)
    set(multiValueArgs TEST_SOURCE)
    cmake_parse_arguments(MY "" "" "${multiValueArgs}" "${ARGN}")
    add_executable(${TEST_NAME} ${MY_TEST_SOURCE} ${QEXT_TEST_CONFIG_HPP_FILE_PATH})
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    target_link_libraries(${TEST_NAME} PRIVATE ${QEXT_TEST_LINK_LIBRARIES})
    target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${QEXT_TEST_INCLUDE_DIRECTORIES})
    if(QEXT_BUILD_SHARED_LIBS AND WIN32)
        qextFunctionCopyDependencyInternal(${TEST_NAME}
            QEXTCore QEXTVLC
            ${EXECUTABLE_OUTPUT_PATH}
            )
    endif()
endfunction()


##--------------------------------------------------------------------------------
## Add test
##--------------------------------------------------------------------------------
qextFunctionAddVLCTest(qext_tst_vlcInstance
    TEST_SOURCE
    TestInstance.cpp
    TestsCommon.cpp
    TestsCommon.h
    )
qextFunctionAddVLCTest(qext_tst_vlcMedia
    TEST_SOURCE
    tst_qextMedia.cpp
    TestsCommon.cpp
    TestsCommon.h
    )
qextFunctionAddVLCTest(qext_tst_vlcMediaList
    TEST_SOURCE
    tst_qextMediaList.cpp
    TestsCommon.cpp
    TestsCommon.h
    )
qextFunctionAddVLCTest(qext_tst_vlcMetaManager
    TEST_SOURCE
    tst_qextMetaManager.cpp
    TestsCommon.cpp
    TestsCommon.h
    )

