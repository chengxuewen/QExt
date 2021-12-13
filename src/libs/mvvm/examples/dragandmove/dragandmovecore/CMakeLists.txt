# library: dragandmovecore
set(library_name dragandmovecore)

set(CMAKE_AUTOMOC ON)

add_library(${library_name} STATIC "")
target_link_libraries(${library_name} PRIVATE Qt5::Gui Qt5::Widgets QEXTMvvm)

target_sources(${library_name} PRIVATE
    containereditorwidget.cpp
    containereditorwidget.h
    dragviewmodel.cpp
    dragviewmodel.h
    mainwindow.cpp
    mainwindow.h
    modeleditorwidget.cpp
    modeleditorwidget.h
    sampleitems.cpp
    sampleitems.h
    samplemodel.cpp
    samplemodel.h
)

