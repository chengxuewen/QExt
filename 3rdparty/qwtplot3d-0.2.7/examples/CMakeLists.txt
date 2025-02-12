#-----------------------------------------------------------------------------------------------------------------------
# Function
#-----------------------------------------------------------------------------------------------------------------------
function(qwtplot3d_add_example NAME)
    set(multiValueArgs SOURCES INCLUDE_DIRS)
    cmake_parse_arguments(arg "" "" "${multiValueArgs}" "${ARGN}")
    add_executable(${NAME} ${arg_SOURCES})
    target_link_libraries(${NAME} PRIVATE QwtPlot3D)
    target_include_directories(${NAME} PRIVATE ${arg_INCLUDE_DIRS})
endfunction()



#-----------------------------------------------------------------------------------------------------------------------
# Examples
#-----------------------------------------------------------------------------------------------------------------------
qwtplot3d_add_example(qwtplot3d_exp_autoswitch
    SOURCES
    autoswitch/autoswitch.cpp
    autoswitch/autoswitch.h)
qwtplot3d_add_example(qwtplot3d_exp_axes
    SOURCES
    axes/src/axes.h
    axes/src/axesmainwindow.cpp
    axes/src/axesmainwindow.h
    axes/src/axesmainwindowbase.ui
    axes/src/main.cpp)
qwtplot3d_add_example(qwtplot3d_exp_curveplot
    SOURCES
    curveplot/curveplot.cpp)
qwtplot3d_add_example(qwtplot3d_exp_dynamicplot
    SOURCES
    dynamicplot/dynamicplot.cpp
    dynamicplot/dynamicplot.h)
qwtplot3d_add_example(qwtplot3d_exp_enrichments
    SOURCES
    enrichments/src/enrichmentmainwindow.cpp
    enrichments/src/enrichmentmainwindow.h
    enrichments/src/enrichmentmainwindowbase.ui
    enrichments/src/enrichments.cpp
    enrichments/src/enrichments.h
    enrichments/src/main.cpp)
qwtplot3d_add_example(qwtplot3d_exp_freemesh
    SOURCES
    freemesh/femreader.h
    freemesh/freemesh.cpp
    freemesh/freemesh.h)
qwtplot3d_add_example(qwtplot3d_exp_graph
    SOURCES
    graph/graph.cpp)
qwtplot3d_add_example(qwtplot3d_exp_mesh
    SOURCES
    mesh/src/colormapreader.cpp
    mesh/src/colormapreader.h
    mesh/src/functions.h
    mesh/src/lightingdialog.cpp
    mesh/src/lightingdialog.h
    mesh/src/lightingdialogbase.ui
    mesh/src/main.cpp
    mesh/src/meshmainwindow.cpp
    mesh/src/meshmainwindow.h
    mesh/src/meshmainwindowbase.ui)
qwtplot3d_add_example(qwtplot3d_exp_plotlets
    SOURCES
    plotlets/src/configframe.cpp
    plotlets/src/configframe.h
    plotlets/src/configframebase.ui
    plotlets/src/functions.h
    plotlets/src/main.cpp
    plotlets/src/mainwindow.cpp
    plotlets/src/mainwindow.h
    plotlets/src/mainwindowbase.ui
    INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/plotlets)
qwtplot3d_add_example(qwtplot3d_exp_simpleplot
    SOURCES
    simpleplot/simpleplot.cpp)
qwtplot3d_add_example(qwtplot3d_exp_volumeplot
    SOURCES
    volumeplot/volumeplot.cpp)
