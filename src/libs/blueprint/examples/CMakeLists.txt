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

list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES QExt::Blueprint)


set(OUTPUT_DIR ${QEXT_OUTPUT_EXAMPLE_DIR}/blueprint)
#-----------------------------------------------------------------------------------------------------------------------
# Add examples
#-----------------------------------------------------------------------------------------------------------------------
qext_add_executable(QExtExpBlueprintSimple
    SOURCES
    simple/main.cpp
    LIBRARIES
    ${QEXT_EXAMPLE_LINK_LIBRARIES}
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/simple
    OUTPUT_DIRECTORY
    ${OUTPUT_DIR}/
    DEFINES
    EXECUTABLE_OUTPUT_PATH="${OUTPUT_DIR}")
qext_add_executable(QExtExpBlueprintCalculator
    SOURCES
    calculator/main.cpp
    calculator/MathOperationDataModel.cpp
    calculator/NumberDisplayDataModel.cpp
    calculator/NumberSourceDataModel.cpp
    calculator/AdditionModel.hpp
    calculator/DivisionModel.hpp
    calculator/DecimalData.hpp
    calculator/MathOperationDataModel.hpp
    calculator/NumberDisplayDataModel.hpp
    calculator/NumberSourceDataModel.hpp
    calculator/SubtractionModel.hpp
    LIBRARIES
    ${QEXT_EXAMPLE_LINK_LIBRARIES}
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/calculator
    OUTPUT_DIRECTORY
    ${OUTPUT_DIR}/
    DEFINES
    EXECUTABLE_OUTPUT_PATH="${OUTPUT_DIR}")
qext_add_executable(QExtExpBlueprintHeadlessCalculator
    SOURCES
    calculator/AdditionModel.hpp
    calculator/DivisionModel.hpp
    calculator/DecimalData.hpp
    calculator/MathOperationDataModel.hpp
    calculator/NumberDisplayDataModel.hpp
    calculator/NumberSourceDataModel.hpp
    calculator/SubtractionModel.hpp
    calculator/headless_main.cpp
    calculator/MathOperationDataModel.cpp
    calculator/NumberDisplayDataModel.cpp
    calculator/NumberSourceDataModel.cpp
    LIBRARIES
    ${QEXT_EXAMPLE_LINK_LIBRARIES}
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/calculator
    OUTPUT_DIRECTORY
    ${OUTPUT_DIR}/
    DEFINES
    EXECUTABLE_OUTPUT_PATH="${OUTPUT_DIR}")
qext_add_executable(QExtExpBlueprintConnectionColors
    SOURCES
    connection_colors/main.cpp
    connection_colors/models.cpp
    connection_colors/models.hpp
    LIBRARIES
    ${QEXT_EXAMPLE_LINK_LIBRARIES}
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/connection_colors
    OUTPUT_DIRECTORY
    ${OUTPUT_DIR}/
    DEFINES
    EXECUTABLE_OUTPUT_PATH="${OUTPUT_DIR}")
qext_add_executable(QExtExpBlueprintDynamicPorts
    SOURCES
    dynamic_ports/DynamicPortsModel.cpp
    dynamic_ports/DynamicPortsModel.hpp
    dynamic_ports/main.cpp
    dynamic_ports/PortAddRemoveWidget.cpp
    dynamic_ports/PortAddRemoveWidget.hpp
    LIBRARIES
    ${QEXT_EXAMPLE_LINK_LIBRARIES}
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/dynamic_ports
    OUTPUT_DIRECTORY
    ${OUTPUT_DIR}/
    DEFINES
    EXECUTABLE_OUTPUT_PATH="${OUTPUT_DIR}")
qext_add_executable(QExtExpBlueprintLockNodesAndConnections
    SOURCES
    lock_nodes_and_connections/DataFlowModel.hpp
    lock_nodes_and_connections/DelegateNodeModel.cpp
    lock_nodes_and_connections/DelegateNodeModel.hpp
    lock_nodes_and_connections/main.cpp
    LIBRARIES
    ${QEXT_EXAMPLE_LINK_LIBRARIES}
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/lock_nodes_and_connections
    OUTPUT_DIRECTORY
    ${OUTPUT_DIR}/
    DEFINES
    EXECUTABLE_OUTPUT_PATH="${OUTPUT_DIR}")
qext_add_executable(QExtExpBlueprintResizableImages
    SOURCES
    resizable_images/ImageLoaderModel.cpp
    resizable_images/ImageLoaderModel.hpp
    resizable_images/ImageShowModel.cpp
    resizable_images/ImageShowModel.hpp
    resizable_images/main.cpp
    resizable_images/PixmapData.hpp
    LIBRARIES
    ${QEXT_EXAMPLE_LINK_LIBRARIES}
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/resizable_images
    OUTPUT_DIRECTORY
    ${OUTPUT_DIR}/
    DEFINES
    EXECUTABLE_OUTPUT_PATH="${OUTPUT_DIR}")
qext_add_executable(QExtExpBlueprintSimpleGraphModel
    SOURCES
    simple_graph_model/main.cpp
    simple_graph_model/SimpleGraphModel.cpp
    simple_graph_model/SimpleGraphModel.hpp
    LIBRARIES
    ${QEXT_EXAMPLE_LINK_LIBRARIES}
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/simple_graph_model
    OUTPUT_DIRECTORY
    ${OUTPUT_DIR}/
    DEFINES
    EXECUTABLE_OUTPUT_PATH="${OUTPUT_DIR}")
qext_add_executable(QExtExpBlueprintStyles
    SOURCES
    styles/main.cpp
    styles/models.cpp
    styles/models.hpp
    LIBRARIES
    ${QEXT_EXAMPLE_LINK_LIBRARIES}
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/styles
    OUTPUT_DIRECTORY
    ${OUTPUT_DIR}/
    DEFINES
    EXECUTABLE_OUTPUT_PATH="${OUTPUT_DIR}")
qext_add_executable(QExtExpBlueprintText
    SOURCES
    text/main.cpp
    text/TextData.hpp
    text/TextDisplayDataModel.cpp
    text/TextDisplayDataModel.hpp
    text/TextSourceDataModel.cpp
    text/TextSourceDataModel.hpp
    LIBRARIES
    ${QEXT_EXAMPLE_LINK_LIBRARIES}
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/text
    OUTPUT_DIRECTORY
    ${OUTPUT_DIR}/
    DEFINES
    EXECUTABLE_OUTPUT_PATH="${OUTPUT_DIR}")
qext_add_executable(QExtExpBlueprintVerticalLayout
    SOURCES
    vertical_layout/main.cpp
    vertical_layout/SimpleGraphModel.cpp
    vertical_layout/SimpleGraphModel.hpp
    LIBRARIES
    ${QEXT_EXAMPLE_LINK_LIBRARIES}
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/vertical_layout
    OUTPUT_DIRECTORY
    ${OUTPUT_DIR}/
    DEFINES
    EXECUTABLE_OUTPUT_PATH="${OUTPUT_DIR}")
