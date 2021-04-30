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
set(EXECUTABLE_OUTPUT_PATH ${QEXT_TEST_OUTPUT_DIR}/core/gtest)
set(LIBRARY_OUTPUT_PATH ${QEXT_TEST_OUTPUT_DIR}/core/gtest)
enable_testing()



#--------------------------------------------------------------------------------
# include_directories
#--------------------------------------------------------------------------------
include_directories(
    ${gtest_SOURCE_DIR}/include
    ${gmock_SOURCE_DIR}/include
)



#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(_test_link_libraries)

list(APPEND _test_link_libraries gtest_main QEXTCore)


#--------------------------------------------------------------------------------
# Add QEXTObjectGTest example
#--------------------------------------------------------------------------------
set(_test_name QEXTObjectGTest)
set(_test_headers
    ../qextsimpleobject.h
    )
set(_test_sources
    qextobjectgtest.cpp
    ../qextsimpleobject.cpp
    )
set(_test_forms
    )
add_executable(${_test_name}
                ${_test_headers}
                ${_test_sources}
                ${_test_forms}
                )
target_link_libraries(${_test_name} PRIVATE ${_test_link_libraries})
target_include_directories(${_test_name} PRIVATE
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/../"
    )
