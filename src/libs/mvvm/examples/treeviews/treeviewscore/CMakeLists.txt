set(library_name treeviewscore)

set(CMAKE_AUTOMOC ON)

add_library(${library_name} STATIC "")
target_link_libraries(${library_name} PRIVATE Qt5::Gui Qt5::Widgets QEXTMvvm)

target_sources(${library_name} PRIVATE
    item_constants.h
    mainwindow.cpp
    mainwindow.h
    sampleeditorwidget.cpp
    sampleeditorwidget.h
    sampleitems.cpp
    sampleitems.h
    samplemodel.cpp
    samplemodel.h
)
