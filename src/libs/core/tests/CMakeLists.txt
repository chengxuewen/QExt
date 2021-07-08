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
set(EXECUTABLE_OUTPUT_PATH ${QEXT_TEST_OUTPUT_DIR})
set(LIBRARY_OUTPUT_PATH ${QEXT_TEST_OUTPUT_DIR})



#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(_test_link_libraries)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND _test_link_libraries Qt4::QtCore Qt4::QtTest)
elseif(QEXT_QT_VERSION_MAJOR EQUAL 5)
    list(APPEND _test_link_libraries Qt5::Core Qt5::Test)
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND _test_link_libraries QEXTCore)



#--------------------------------------------------------------------------------
# Add tst_qextobject test
#--------------------------------------------------------------------------------
set(_test_name tst_qextobject)
add_executable(${_test_name}
    qextsimpleobject.h
    tst_qextobject.cpp
    qextsimpleobject.cpp
    )
add_test(NAME ${_test_name} COMMAND ${_test_name})
target_link_libraries(${_test_name} PRIVATE ${_test_link_libraries})
target_include_directories(${_test_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

