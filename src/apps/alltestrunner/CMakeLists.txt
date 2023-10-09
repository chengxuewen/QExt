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
# Set example output path
#-----------------------------------------------------------------------------------------------------------------------
set(QEXT_APP_BASE_NAME qext_tool_alltestrunner)
set(EXECUTABLE_OUTPUT_PATH ${QEXT_OUTPUT_APP_DIR})



#-----------------------------------------------------------------------------------------------------------------------
# Set app link libraries
#-----------------------------------------------------------------------------------------------------------------------
if(UNIX)
    list(APPEND QEXT_APP_LINK_LIBRARIES ${CMAKE_DL_LIBS})
endif()

if(WIN32)
    list(APPEND QEXT_APP_LINK_LIBRARIES shlwapi.lib)
endif()

if(CMAKE_THREAD_LIBS_INIT)
    list(APPEND QEXT_APP_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
endif()

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_APP_LINK_LIBRARIES Qt4::QtCore)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_APP_LINK_LIBRARIES Qt${QEXT_QT_VERSION_MAJOR}::Core)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()



#-----------------------------------------------------------------------------------------------------------------------
# Configure a header file to pass some of the CMake settings to the source code
#-----------------------------------------------------------------------------------------------------------------------
set(QEXT_ALL_TEST_RUNNER_CONFIG_FILE_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(QEXT_ALL_TEST_RUNNER_CONFIG_FILE_PATH ${QEXT_ALL_TEST_RUNNER_CONFIG_FILE_DIR}/qextAllTestRunnerConfig.h)
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/qextAllTestRunnerConfig.h.in"
    "${QEXT_ALL_TEST_RUNNER_CONFIG_FILE_PATH}"
    )



#-----------------------------------------------------------------------------------------------------------------------
# Add app target
#-----------------------------------------------------------------------------------------------------------------------
add_executable(${QEXT_APP_BASE_NAME}_all
    ${QEXT_ALL_TEST_RUNNER_CONFIG_FILE_PATH}
    qextTestRunner.h
    qextTestOutputAll.cpp
    )
target_link_libraries(${QEXT_APP_BASE_NAME}_all PUBLIC ${QEXT_APP_LINK_LIBRARIES})
target_include_directories(${QEXT_APP_BASE_NAME}_all PUBLIC
    ${QEXT_ALL_TEST_RUNNER_CONFIG_FILE_DIR}
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )

# set target properties
set_target_properties(${QEXT_APP_BASE_NAME}_all PROPERTIES
    CXX_STANDARD ${QEXT_CXX_STANDARD}
    )


#-----------------------------------------------------------------------------------------------------------------------
# Add app target
#-----------------------------------------------------------------------------------------------------------------------
add_executable(${QEXT_APP_BASE_NAME}_failure
    ${QEXT_ALL_TEST_RUNNER_CONFIG_FILE_PATH}
    qextTestRunner.h
    qextTestOutputFailure.cpp
    )
target_link_libraries(${QEXT_APP_BASE_NAME}_failure PUBLIC ${QEXT_APP_LINK_LIBRARIES})
target_include_directories(${QEXT_APP_BASE_NAME}_failure PUBLIC
    ${QEXT_ALL_TEST_RUNNER_CONFIG_FILE_DIR}
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )


# set target properties
set_target_properties(${QEXT_APP_BASE_NAME}_failure PROPERTIES
    CXX_STANDARD ${QEXT_CXX_STANDARD}
    )
