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
set(EXECUTABLE_OUTPUT_PATH ${QEXT_OUTPUT_TEST_DIR}/widget)
set(LIBRARY_OUTPUT_PATH ${QEXT_OUTPUT_TEST_DIR}/widget)



#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(QEXT_TEST_LINK_LIBRARIES)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_TEST_LINK_LIBRARIES Qt4::QtCore Qt4::QtTest)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_TEST_LINK_LIBRARIES Qt${QEXT_QT_VERSION_MAJOR}::Core Qt${QEXT_QT_VERSION_MAJOR}::Test)
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND QEXT_TEST_LINK_LIBRARIES QEXTWidgets)



#--------------------------------------------------------------------------------
# Add tst_qextnetworkutils example
#--------------------------------------------------------------------------------
#set(qext_test_name tst_qextdatatimeutils)
#add_executable(${qext_test_name} tst_qextdatatimeutils.cpp)
#add_test(NAME ${qext_test_name} COMMAND ${qext_test_name})
#target_link_libraries(${qext_test_name} PRIVATE ${QEXT_TEST_LINK_LIBRARIES})
#target_include_directories(${qext_test_name} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
#if(WIN32)
#    qextFunctionCopyDependencyInternal(${qext_test_name} QEXTUtils ${EXECUTABLE_OUTPUT_PATH})
#    qextFunctionCopyDependencyInternal(${qext_test_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
#endif()
