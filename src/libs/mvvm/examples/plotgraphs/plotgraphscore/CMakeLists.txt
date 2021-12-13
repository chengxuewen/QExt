set(library_name plotgraphscore)

set(CMAKE_AUTOMOC ON)

add_library(${library_name} STATIC "")
target_link_libraries(${library_name} PRIVATE Qt5::Gui Qt5::Widgets QEXTMvvm)

target_sources(${library_name} PRIVATE
    graphmodel.cpp
    graphmodel.h
    graphpropertywidget.cpp
    graphpropertywidget.h
    graphwidget.cpp
    graphwidget.h
    mainwindow.cpp
    mainwindow.h
)
