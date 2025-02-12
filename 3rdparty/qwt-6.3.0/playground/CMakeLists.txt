#-----------------------------------------------------------------------------------------------------------------------
# Function
#-----------------------------------------------------------------------------------------------------------------------
function(qwt_add_playground NAME)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(arg "" "" "${multiValueArgs}" "${ARGN}")
    add_executable(${NAME} ${arg_SOURCES})
    target_link_libraries(${NAME} PRIVATE Qwt)
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
# Playgrounds
#-----------------------------------------------------------------------------------------------------------------------
qwt_add_playground(qwt_playground_curvetracker
    SOURCES
    curvetracker/CurveTracker.cpp
    curvetracker/CurveTracker.h
    curvetracker/main.cpp
    curvetracker/Plot.cpp
    curvetracker/Plot.h)
qwt_add_playground(qwt_playground_graphicscale
    SOURCES
    graphicscale/Canvas.cpp
    graphicscale/Canvas.h
    graphicscale/main.cpp
    graphicscale/MainWindow.cpp
    graphicscale/MainWindow.cpp)
qwt_add_playground(qwt_playground_plotmatrix
    SOURCES
    plotmatrix/main.cpp
    plotmatrix/PlotMatrix.cpp
    plotmatrix/PlotMatrix.h)
qwt_add_playground(qwt_playground_rescaler
    SOURCES
    rescaler/main.cpp
    rescaler/MainWindow.cpp
    rescaler/MainWindow.h
    rescaler/Plot.cpp
    rescaler/Plot.h)
qwt_add_playground(qwt_playground_scaleengine
    SOURCES
    scaleengine/main.cpp
    scaleengine/MainWindow.cpp
    scaleengine/MainWindow.h
    scaleengine/Plot.cpp
    scaleengine/Plot.h
    scaleengine/TransformPlot.cpp
    scaleengine/TransformPlot.h)
qwt_add_playground(qwt_playground_shapes
    SOURCES
    shapes/main.cpp)
qwt_add_playground(qwt_playground_svgmap
    SOURCES
    svgmap/main.cpp
    svgmap/Plot.cpp
    svgmap/Plot.h
    svgmap/svgmap.qrc)
qwt_add_playground(qwt_playground_symbols
    SOURCES
    symbols/main.cpp)
qwt_add_playground(qwt_playground_timescale
    SOURCES
    timescale/main.cpp
    timescale/MainWindow.cpp
    timescale/MainWindow.h
    timescale/Panel.cpp
    timescale/Panel.h
    timescale/Plot.cpp
    timescale/Plot.h
    timescale/Settings.h)
qwt_add_playground(qwt_playground_vectorfield
    SOURCES
    vectorfield/main.cpp)
