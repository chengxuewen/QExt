########################################################################################################################
#
# Library: QExt
#
# Copyright (C) 2024~Present ChengXueWen. Contact: 1398831004@qq.com.
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
# Add lib link libraries
#-----------------------------------------------------------------------------------------------------------------------
set(QEXT_LIB_LINK_LIBRARIES)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui Qt4::QtSvg)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::Svg
        Qt${QEXT_QT_VERSION_MAJOR}::OpenGL
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_LIB_LINK_LIBRARIES QExt::Core)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
qext_add_library(Blueprint
    EXCEPTIONS
    SOURCES
    source/qextBlueprintConstant.h
    source/qextBlueprintGlobal.h
    source/qextBPAbstractGraphModel_p.h
    source/qextBPAbstractGraphModel.h
    source/qextBPAbstractGraphModel.cpp
    source/qextBPAbstractNodeGeometry_p.h
    source/qextBPAbstractNodeGeometry.h
    source/qextBPAbstractNodeGeometry.cpp
    source/qextBPAbstractNodePainter.h
    source/qextBPBasicGraphicsScene_p.h
    source/qextBPBasicGraphicsScene.h
    source/qextBPBasicGraphicsScene.cpp
    source/qextBPConnectionGraphicsObject_p.h
    source/qextBPConnectionGraphicsObject.h
    source/qextBPConnectionGraphicsObject.cpp
    source/qextBPConnectionIdHash.h
    source/qextBPConnectionPainter.h
    source/qextBPConnectionPainter.cpp
    source/qextBPConnectionState_p.h
    source/qextBPConnectionState.h
    source/qextBPConnectionState.cpp
    source/qextBPConnectionStyle.h
    source/qextBPConnectionStyle.cpp
    source/qextBPDataFlowGraphicsScene.h
    source/qextBPDataFlowGraphicsScene.cpp
    source/qextBPDataFlowGraphModel_p.h
    source/qextBPDataFlowGraphModel.h
    source/qextBPDataFlowGraphModel.cpp
    source/qextBPDefaultHorizontalNodeGeometry.h
    source/qextBPDefaultHorizontalNodeGeometry.cpp
    source/qextBPDefaultNodePainter.h
    source/qextBPDefaultNodePainter.cpp
    source/qextBPDefaultVerticalNodeGeometry.h
    source/qextBPDefaultVerticalNodeGeometry.cpp
    source/qextBPGraphicsView_p.h
    source/qextBPGraphicsView.h
    source/qextBPGraphicsView.cpp
    source/qextBPGraphicsViewStyle.h
    source/qextBPGraphicsViewStyle.cpp
    source/qextBPLocateNode.h
    source/qextBPLocateNode.cpp
    source/qextBPNodeConnectionInteraction.h
    source/qextBPNodeConnectionInteraction.cpp
    source/qextBPNodeData.h
    source/qextBPNodeDelegateModel_p.h
    source/qextBPNodeDelegateModel.h
    source/qextBPNodeDelegateModel.cpp
    source/qextBPNodeDelegateModelRegistry.h
    source/qextBPNodeDelegateModelRegistry.cpp
    source/qextBPNodeGraphicsObject_p.h
    source/qextBPNodeGraphicsObject.h
    source/qextBPNodeGraphicsObject.cpp
    source/qextBPNodeState_p.h
    source/qextBPNodeState.h
    source/qextBPNodeState.cpp
    source/qextBPNodeStyle.h
    source/qextBPNodeStyle.cpp
    source/qextBPQStringStdHash.h
    source/qextBPQUuidStdHash.h
    source/qextBPSerializable.h
    source/qextBPStyle.h
    source/qextBPStyleCollection.h
    source/qextBPStyleCollection.cpp
    source/qextBPTypes.h
    source/qextBPTypes.cpp
    source/qextBPUndoCommands.h
    source/qextBPUndoCommands.cpp
    source/qextBPUtils.h
    resource/qextBlueprint.qrc
    PRECOMPILED_HEADER
    source/qextBlueprintPch.h
    PUBLIC_LIBRARIES
    ${QEXT_LIB_LINK_LIBRARIES})


#-----------------------------------------------------------------------------------------------------------------------
# Add lib examples and tests
#-----------------------------------------------------------------------------------------------------------------------
qext_add_subdirectory(examples QEXT_BUILD_EXAMPLES)
qext_add_subdirectory(tests QEXT_BUILD_TESTS)
