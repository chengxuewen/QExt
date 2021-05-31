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
set(EXECUTABLE_OUTPUT_PATH ${QEXT_EXAMPLE_OUTPUT_DIR}/thirdparty/qnanopainter)
set(LIBRARY_OUTPUT_PATH ${QEXT_LIB_OUTPUT_DIR}/thirdparty/qnanopainter)



#--------------------------------------------------------------------------------
# Set example link libraries
#--------------------------------------------------------------------------------
set(_example_link_libraries)

if(UNIX)
    list(APPEND _example_link_libraries dl)
endif()

if(WIN32)
    list(APPEND _example_link_libraries shlwapi.lib)
endif()

if(CMAKE_THREAD_LIBS_INIT)
    list(APPEND _example_link_libraries ${CMAKE_THREAD_LIBS_INIT})
endif()

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND _example_link_libraries Qt4::QtCore Qt4::QtGui)
elseif(QEXT_QT_VERSION_MAJOR EQUAL 5)
    list(APPEND _example_link_libraries Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Quick)
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND _example_link_libraries QNanoPainter)



#--------------------------------------------------------------------------------
# Add QNanoPainterGallery example
#--------------------------------------------------------------------------------
set(_example_name QNanoPainterGallery)
set(_example_headers

    )
set(_example_sources
    gallery/main.cpp

    gallery/qnanopainter_features/src/galleryitem.cpp
    gallery/qnanopainter_features/src/galleryitempainter.cpp
    gallery/qnanopainter_features/src/galleryitem.h
    gallery/qnanopainter_features/src/galleryitempainter.h

    gallery/painting/src/paintingitem.cpp
    gallery/painting/src/paintingitempainter.cpp
    gallery/painting/src/paintingitem.h
    gallery/painting/src/paintingitempainter.h

    gallery/mouse_events/src/eventitem.cpp
    gallery/mouse_events/src/eventitempainter.cpp
    gallery/mouse_events/src/eventitem.h
    gallery/mouse_events/src/eventitempainter.h
    )
set(_example_forms

    )
set(_example_resource
    gallery/qml.qrc
    gallery/qnanopainter_features/qnanopainter_features.qrc
    gallery/painting/painting.qrc
    gallery/mouse_events/mouse_events.qrc
    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    ${_example_resource}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_include_directories(${_example_name} PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/gallery
    ${CMAKE_CURRENT_SOURCE_DIR}/qnanopainter_features
    ${CMAKE_CURRENT_SOURCE_DIR}/mouse_events
    ${CMAKE_CURRENT_SOURCE_DIR}/painting
    )
set_property(TARGET ${_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)



#--------------------------------------------------------------------------------
# Add QNanoPainterHelloitem example
#--------------------------------------------------------------------------------
set(_example_name QNanoPainterHelloitem)
set(_example_headers

    )
set(_example_sources
    helloitem/main.cpp
    helloitem/helloitem.h

    shared/painthelper.h
    )
set(_example_forms

    )
set(_example_resource
    helloitem/qml.qrc
    shared/shareddata.qrc
    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    ${_example_resource}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_include_directories(${_example_name} PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/helloitem
    ${CMAKE_CURRENT_SOURCE_DIR}/shared
    )
set_property(TARGET ${_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)



#--------------------------------------------------------------------------------
# Add QNanoPainterHellowidget example
#--------------------------------------------------------------------------------
set(_example_name QNanoPainterHellowidget)
set(_example_headers

    )
set(_example_sources
    hellowidget/main.cpp
    hellowidget/hellowidget.h

    shared/painthelper.h
    )
set(_example_forms

    )
set(_example_resource
    shared/shareddata.qrc
    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    ${_example_resource}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_include_directories(${_example_name} PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/hellowidget
    ${CMAKE_CURRENT_SOURCE_DIR}/shared
    )
set_property(TARGET ${_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)



#--------------------------------------------------------------------------------
# Add QNanoPainterHellowindow example
#--------------------------------------------------------------------------------
set(_example_name QNanoPainterHellowindow)
set(_example_headers

    )
set(_example_sources
    hellowindow/main.cpp
    hellowindow/hellowindow.h

    shared/painthelper.h
    )
set(_example_forms

    )
set(_example_resource
    shared/shareddata.qrc
    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    ${_example_resource}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_include_directories(${_example_name} PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/hellowidget
    ${CMAKE_CURRENT_SOURCE_DIR}/shared
    )
set_property(TARGET ${_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)



#--------------------------------------------------------------------------------
# Add QNanoPainterTestDemo example
#--------------------------------------------------------------------------------
set(_example_name QNanoPainterTestDemo)
set(_example_headers
    qnanopainter_vs_qpainter_demo/src/demoqpitem.h
    qnanopainter_vs_qpainter_demo/src/demoqnanoitem.h
    qnanopainter_vs_qpainter_demo/src/demoqnanoitempainter.h
    )
set(_example_sources
    qnanopainter_vs_qpainter_demo/main.cpp

    qnanopainter_vs_qpainter_demo/src/demoqpitem.cpp
    qnanopainter_vs_qpainter_demo/src/demoqnanoitem.cpp
    qnanopainter_vs_qpainter_demo/src/demoqnanoitempainter.cpp
    )
set(_example_forms

    )
set(_example_resource
    qnanopainter_vs_qpainter_demo/qml.qrc
    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    ${_example_resource}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_include_directories(${_example_name} PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/qnanopainter_vs_qpainter_demo
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    )
set_property(TARGET ${_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
