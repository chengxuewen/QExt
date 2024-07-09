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
    source/QtNodes/AbstractGraphModel.hpp
    source/QtNodes/AbstractNodeGeometry.hpp
    source/QtNodes/AbstractNodePainter.hpp
    source/QtNodes/BasicGraphicsScene.hpp
#    source/QtNodes/Compiler.hpp
    source/QtNodes/ConnectionGraphicsObject.hpp
    source/QtNodes/ConnectionIdHash.hpp
    source/QtNodes/ConnectionIdUtils.hpp
    source/QtNodes/ConnectionState.hpp
    source/QtNodes/ConnectionStyle.hpp
    source/QtNodes/DataFlowGraphicsScene.hpp
    source/QtNodes/DataFlowGraphModel.hpp
    source/QtNodes/DefaultNodePainter.hpp
#    source/QtNodes/qextBPTypes.h
#    source/QtNodes/Export.hpp
    source/QtNodes/GraphicsView.hpp
    source/QtNodes/GraphicsViewStyle.hpp
    source/QtNodes/locateNode.hpp
    source/QtNodes/NodeData.hpp
    source/QtNodes/NodeDelegateModel.hpp
    source/QtNodes/NodeDelegateModelRegistry.hpp
    source/QtNodes/NodeGraphicsObject.hpp
    source/QtNodes/NodeState.hpp
    source/QtNodes/NodeStyle.hpp
#    source/QtNodes/OperatingSystem.hpp
    source/QtNodes/QStringStdHash.hpp
    source/QtNodes/QUuidStdHash.hpp
    source/QtNodes/Serializable.hpp
    source/QtNodes/Style.hpp
    source/QtNodes/StyleCollection.hpp
    source/QtNodes/AbstractGraphModel.cpp
    source/QtNodes/AbstractNodeGeometry.cpp
    source/QtNodes/BasicGraphicsScene.cpp
    source/QtNodes/ConnectionGraphicsObject.cpp
    source/QtNodes/ConnectionPainter.cpp
    source/QtNodes/ConnectionPainter.hpp
    source/QtNodes/ConnectionState.cpp
    source/QtNodes/ConnectionStyle.cpp
    source/QtNodes/DataFlowGraphicsScene.cpp
    source/QtNodes/DataFlowGraphModel.cpp
    source/QtNodes/DefaultHorizontalNodeGeometry.cpp
    source/QtNodes/DefaultHorizontalNodeGeometry.hpp
    source/QtNodes/DefaultNodePainter.cpp
    source/QtNodes/DefaultVerticalNodeGeometry.cpp
    source/QtNodes/DefaultVerticalNodeGeometry.hpp
#    source/QtNodes/Definitions.cpp
    source/QtNodes/GraphicsView.cpp
    source/QtNodes/GraphicsViewStyle.cpp
    source/QtNodes/locateNode.cpp
    source/QtNodes/NodeConnectionInteraction.cpp
    source/QtNodes/NodeConnectionInteraction.hpp
    source/QtNodes/NodeDelegateModel.cpp
    source/QtNodes/NodeDelegateModelRegistry.cpp
    source/QtNodes/NodeGraphicsObject.cpp
    source/QtNodes/NodeState.cpp
    source/QtNodes/NodeStyle.cpp
    source/QtNodes/StyleCollection.cpp
    source/QtNodes/UndoCommands.cpp
    source/QtNodes/UndoCommands.hpp
    source/qextBlueprintConstant.h
    source/qextBlueprintGlobal.h
#    source/qextBlueprintModelBase.cpp
#    source/qextBlueprintModelBase.h
    source/qextBlueprintScene.cpp
    source/qextBlueprintScene_p.h
    source/qextBlueprintScene.h
    source/qextBPTypes.cpp
    source/qextBPTypes.h
    source/qextBlueprintView.h
    source/qextBlueprintView_p.h
    source/qextBlueprintView.cpp
    resource/qextBlueprint.qrc
    resource/resources.qrc
    PRECOMPILED_HEADER
    source/qextBlueprintPch.h
    PUBLIC_LIBRARIES
    ${QEXT_LIB_LINK_LIBRARIES})


#-----------------------------------------------------------------------------------------------------------------------
# Add lib examples and tests
#-----------------------------------------------------------------------------------------------------------------------
qext_add_subdirectory(examples QEXT_BUILD_EXAMPLES)
qext_add_subdirectory(tests QEXT_BUILD_TESTS)
