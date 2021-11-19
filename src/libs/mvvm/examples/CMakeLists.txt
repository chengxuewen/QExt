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
# Set example output path
#--------------------------------------------------------------------------------
set(EXECUTABLE_OUTPUT_PATH ${QEXT_EXAMPLE_OUTPUT_DIR}/mvvm)
set(LIBRARY_OUTPUT_PATH ${QEXT_EXAMPLE_OUTPUT_DIR}/mvvm)



#--------------------------------------------------------------------------------
# Set example link libraries
#--------------------------------------------------------------------------------
set(qext_example_link_libraries)

if(UNIX)
    list(APPEND qext_example_link_libraries dl pthread)
endif()

if(WIN32)
    list(APPEND qext_example_link_libraries shlwapi.lib)
endif()

if(CMAKE_THREAD_LIBS_INIT)
    list(APPEND qext_example_link_libraries ${CMAKE_THREAD_LIBS_INIT})
endif()

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND qext_example_link_libraries Qt4::QtCore Qt4::QtGui)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND qext_example_link_libraries
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets
        )
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND qext_example_link_libraries QEXTMvvm)



#--------------------------------------------------------------------------------
# define function
#--------------------------------------------------------------------------------
function(qextMvvmAddExample EXAMPLE_NAME)
    set(multiValueArgs EXAMPLE_SOURCE)
    cmake_parse_arguments(MY "" "" "${multiValueArgs}" "${ARGN}")
    add_executable(${EXAMPLE_NAME} ${MY_EXAMPLE_SOURCE})
    add_test(NAME ${EXAMPLE_NAME} COMMAND ${EXAMPLE_NAME})
    target_link_libraries(${EXAMPLE_NAME} PRIVATE ${qext_example_link_libraries})
    target_include_directories(${EXAMPLE_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${qext_example_include_directories})
    if(QEXT_BUILD_SHARED_LIBS AND WIN32)
        qextMacroCopyDependenceLib(${EXAMPLE_NAME} QEXTMvvm ${EXECUTABLE_OUTPUT_PATH})
    endif()
endfunction()



#--------------------------------------------------------------------------------
# Add example
#--------------------------------------------------------------------------------
qextMvvmAddExample(qext_exp_mvvmCelleEitors
    EXAMPLE_SOURCE
    celleditors/item_constants.h
    celleditors/main.cpp
    celleditors/mainwindow.cpp
    celleditors/mainwindow.h
    celleditors/modeleditorwidget.cpp
    celleditors/modeleditorwidget.h
    celleditors/samplemodel.cpp
    celleditors/samplemodel.h
    )
qextMvvmAddExample(qext_exp_mvvmCollidingMice
    EXAMPLE_SOURCE
    collidingmice/main.cpp
    collidingmice/mainwindow.cpp
    collidingmice/mainwindow.h
    collidingmice/mice.qrc
    collidingmice/mouse.cpp
    collidingmice/mouse.h
    collidingmice/mousemodel.cpp
    collidingmice/mousemodel.h
    )
qextMvvmAddExample(qext_exp_mvvmConcurrentPlot
    EXAMPLE_SOURCE
    concurrentplot/graphmodel.cpp
    concurrentplot/graphmodel.h
    concurrentplot/graphpropertywidget.cpp
    concurrentplot/graphpropertywidget.h
    concurrentplot/graphwidget.cpp
    concurrentplot/graphwidget.h
    concurrentplot/graphwidgettoolbar.cpp
    concurrentplot/graphwidgettoolbar.h
    concurrentplot/jobmanager.cpp
    concurrentplot/jobmanager.h
    concurrentplot/main.cpp
    concurrentplot/mainwindow.cpp
    concurrentplot/mainwindow.h
    concurrentplot/toysimulation.cpp
    concurrentplot/toysimulation.h
    )
qextMvvmAddExample(qext_exp_mvvmDragandMove
    EXAMPLE_SOURCE
    dragandmove/containereditorwidget.cpp
    dragandmove/containereditorwidget.h
    dragandmove/dragviewmodel.cpp
    dragandmove/dragviewmodel.h
    dragandmove/main.cpp
    dragandmove/mainwindow.cpp
    dragandmove/mainwindow.h
    dragandmove/modeleditorwidget.cpp
    dragandmove/modeleditorwidget.h
    dragandmove/sampleitems.cpp
    dragandmove/sampleitems.h
    dragandmove/samplemodel.cpp
    dragandmove/samplemodel.h
    )
qextMvvmAddExample(qext_exp_mvvmFlatEditor
    EXAMPLE_SOURCE
    flateditor/demowidget.cpp
    flateditor/demowidget.h
    flateditor/main.cpp
    flateditor/mainwindow.cpp
    flateditor/mainwindow.h
    flateditor/sampleitems.cpp
    flateditor/sampleitems.h
    flateditor/samplemodel.cpp
    flateditor/samplemodel.h
    )
qextMvvmAddExample(qext_exp_mvvmGraphicsProxy
    EXAMPLE_SOURCE
    graphicsproxy/axesrectangleview.cpp
    graphicsproxy/axesrectangleview.h
    graphicsproxy/graphicsscene.cpp
    graphicsproxy/graphicsscene.h
    graphicsproxy/graphicsview.cpp
    graphicsproxy/graphicsview.h
    graphicsproxy/main.cpp
    graphicsproxy/mainwindow.cpp
    graphicsproxy/mainwindow.h
    graphicsproxy/regionofinterestcontroller.cpp
    graphicsproxy/regionofinterestcontroller.h
    graphicsproxy/regionofinterestview.cpp
    graphicsproxy/regionofinterestview.h
    graphicsproxy/sceneitems.cpp
    graphicsproxy/sceneitems.h
    graphicsproxy/scenemodel.cpp
    graphicsproxy/scenemodel.h
    graphicsproxy/scenepropertywidget.cpp
    graphicsproxy/scenepropertywidget.h
    graphicsproxy/scenewidget.cpp
    graphicsproxy/scenewidget.h
    graphicsproxy/sizehandleelement.cpp
    graphicsproxy/sizehandleelement.h
    )
qextMvvmAddExample(qext_exp_mvvmHelloWorld
    EXAMPLE_SOURCE
    helloworld/main.cpp
    )
qextMvvmAddExample(qext_exp_mvvmLayerEditor
    EXAMPLE_SOURCE
    layereditor/applicationmodels.cpp
    layereditor/applicationmodels.h
    layereditor/customeditorfactory.cpp
    layereditor/customeditorfactory.h
    layereditor/customlayerrowstrategy.h
    layereditor/main.cpp
    layereditor/mainwindow.cpp
    layereditor/mainwindow.h
    layereditor/materialmodel.cpp
    layereditor/materialmodel.h
    layereditor/materialpropertycontroller.cpp
    layereditor/materialpropertycontroller.h
    layereditor/materialtablewidget.cpp
    layereditor/materialtablewidget.h
    layereditor/multilayertreeview.cpp
    layereditor/multilayertreeview.h
    layereditor/samplemodel.cpp
    layereditor/samplemodel.h
    layereditor/samplewidget.cpp
    layereditor/samplewidget.h
    )
qextMvvmAddExample(qext_exp_mvvmModelinQml
    EXAMPLE_SOURCE
    modelinqml/app.qrc
    modelinqml/backend.cpp
    modelinqml/backend.h
    modelinqml/main.cpp
    modelinqml/main.qml
    modelinqml/modelinqmlcore.qrc
    modelinqml/particlemodel.cpp
    modelinqml/particlemodel.h
    modelinqml/particleviewmodel.cpp
    modelinqml/particleviewmodel.h
    modelinqml/tablemodel.h
    )
if(QEXT_QT_VERSION_MAJOR GREATER 4)
    target_link_libraries(qext_exp_mvvmModelinQml PUBLIC Qt${QEXT_QT_VERSION_MAJOR}::Qml)
endif()
qextMvvmAddExample(qext_exp_mvvmPlotColorMap
    EXAMPLE_SOURCE
    plotcolormap/colormapmodel.cpp
    plotcolormap/colormapmodel.h
    plotcolormap/colormappropertywidget.cpp
    plotcolormap/colormappropertywidget.h
    plotcolormap/colormapwidget.cpp
    plotcolormap/colormapwidget.h
    plotcolormap/main.cpp
    plotcolormap/mainwindow.cpp
    plotcolormap/mainwindow.h
    )
qextMvvmAddExample(qext_exp_mvvmPlotGraphs
    EXAMPLE_SOURCE
    plotgraphs/graphmodel.cpp
    plotgraphs/graphmodel.h
    plotgraphs/graphpropertywidget.cpp
    plotgraphs/graphpropertywidget.h
    plotgraphs/graphwidget.cpp
    plotgraphs/graphwidget.h
    plotgraphs/main.cpp
    plotgraphs/mainwindow.cpp
    plotgraphs/mainwindow.h
    )
qextMvvmAddExample(qext_exp_mvvmSaveLoadProject
    EXAMPLE_SOURCE
    saveloadproject/actionmanager.cpp
    saveloadproject/actionmanager.h
    saveloadproject/containereditorwidget.cpp
    saveloadproject/containereditorwidget.h
    saveloadproject/main.cpp
    saveloadproject/mainwindow.cpp
    saveloadproject/mainwindow.h
    saveloadproject/projecthandler.cpp
    saveloadproject/projecthandler.h
    saveloadproject/projectpanewidget.cpp
    saveloadproject/projectpanewidget.h
    saveloadproject/recentprojectsettings.cpp
    saveloadproject/recentprojectsettings.h
    saveloadproject/recentprojectwidget.cpp
    saveloadproject/recentprojectwidget.h
    saveloadproject/samplemodel.cpp
    saveloadproject/samplemodel.h
    saveloadproject/userinteractor.cpp
    saveloadproject/userinteractor.h
    )
qextMvvmAddExample(qext_exp_mvvmTreeViews
    EXAMPLE_SOURCE
    treeviews/item_constants.h
    treeviews/main.cpp
    treeviews/mainwindow.cpp
    treeviews/mainwindow.h
    treeviews/sampleeditorwidget.cpp
    treeviews/sampleeditorwidget.h
    treeviews/sampleitems.cpp
    treeviews/sampleitems.h
    treeviews/samplemodel.cpp
    treeviews/samplemodel.h
    )
