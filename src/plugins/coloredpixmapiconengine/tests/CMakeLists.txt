########################################################################################################################
#
# Library: QExt
#
# Copyright (C) 2021~Present ChengXueWen. Contact: 1398831004@qq.com.
#
# License: MIT License
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
# documentation files (the "Software"), to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and
# to permit persons to whom the Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or substantial portions
# of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE  AUTHORS
# OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
########################################################################################################################

#-----------------------------------------------------------------------------------------------------------------------
# Set lib base name and out put path
#-----------------------------------------------------------------------------------------------------------------------
set(EXECUTABLE_OUTPUT_PATH ${QEXT_TEST_OUTPUT_DIR}/widget)
set(LIBRARY_OUTPUT_PATH ${QEXT_TEST_OUTPUT_DIR}/widget)



#-----------------------------------------------------------------------------------------------------------------------
# Add lib link libraries
#-----------------------------------------------------------------------------------------------------------------------
set(_test_link_libraries)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND _test_link_libraries Qt4::QtCore Qt4::QtTest)
elseif(QEXT_QT_VERSION_MAJOR EQUAL 5)
    list(APPEND _test_link_libraries Qt5::Core Qt5::Test)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND _test_link_libraries QEXTWidget)



#-----------------------------------------------------------------------------------------------------------------------
# Add tst_qextnetworkutils example
#-----------------------------------------------------------------------------------------------------------------------
#set(_test_name tst_qextdatatimeutils)
#add_executable(${_test_name} tst_qextdatatimeutils.cpp)
#add_test(NAME ${_test_name} COMMAND ${_test_name})
#target_link_libraries(${_test_name} PRIVATE ${_test_link_libraries})
#target_include_directories(${_test_name} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
#if(WIN32)
#    qextFunctionCopyDependencyInternal(${_test_name} QEXTUtils ${EXECUTABLE_OUTPUT_PATH})
#    qextFunctionCopyDependencyInternal(${_test_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
#endif()
