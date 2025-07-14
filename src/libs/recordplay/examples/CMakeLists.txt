########################################################################################################################
#
# Library: QExt
#
# Copyright (C) 2025~Present ChengXueWen. Contact: 1398831004@qq.com.
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
set(EXECUTABLE_OUTPUT_PATH "${QEXT_BUILD_DIR}/${QEXT_INSTALL_EXAMPLESDIR}")


#-----------------------------------------------------------------------------------------------------------------------
# Set example link libraries
#-----------------------------------------------------------------------------------------------------------------------
set(QEXT_EXAMPLE_LINK_LIBRARIES)
if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES
    QExt3rdparty::WrapMicroCDR
    QExt3rdparty::Wrapmcap
    QExt::RecordPlay)


#-----------------------------------------------------------------------------------------------------------------------
# Add examples
#-----------------------------------------------------------------------------------------------------------------------
qext_add_executable(QExtExpRecordPlayMCapAttachment
    SOURCES
    mcap/exp_mcap_attachment.cpp
    LIBRARIES
    ${QEXT_EXAMPLE_LINK_LIBRARIES}
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/mcap
    OUTPUT_DIRECTORY
    ${EXECUTABLE_OUTPUT_PATH}
    DEFINES
    EXECUTABLE_OUTPUT_PATH="${EXECUTABLE_OUTPUT_PATH}")
qext_add_executable(QExtExpRecordPlayMicroCDRBasic
    SOURCES
    microcdr/exp_ucdr_basic.cpp
    LIBRARIES
    ${QEXT_EXAMPLE_LINK_LIBRARIES}
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/microcdr
    OUTPUT_DIRECTORY
    ${EXECUTABLE_OUTPUT_PATH}
    DEFINES
    EXECUTABLE_OUTPUT_PATH="${EXECUTABLE_OUTPUT_PATH}")
qext_add_executable(QExtExpRecordPlayMicroCDRFragmentation
    SOURCES
    microcdr/exp_ucdr_fragmentation.cpp
    LIBRARIES
    ${QEXT_EXAMPLE_LINK_LIBRARIES}
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/microcdr
    OUTPUT_DIRECTORY
    ${EXECUTABLE_OUTPUT_PATH}
    DEFINES
    EXECUTABLE_OUTPUT_PATH="${EXECUTABLE_OUTPUT_PATH}")
