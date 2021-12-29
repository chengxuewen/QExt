#--------------------------------------------------------------------------------
# Set example output path
#--------------------------------------------------------------------------------
set(EXECUTABLE_OUTPUT_PATH ${QWTPLOT3DEXT_EXAMPLE_OUTPUT_DIR})
set(LIBRARY_OUTPUT_PATH ${QWTPLOT3DEXT_EXAMPLE_OUTPUT_DIR})



#--------------------------------------------------------------------------------
# Set example link libraries
#--------------------------------------------------------------------------------
set(QWTPLOT3DEXT_EXAMPLE_LINK_LIBRARIES)

if(UNIX)
    list(APPEND QWTPLOT3DEXT_EXAMPLE_LINK_LIBRARIES dl)
endif()

if(WIN32)
    list(APPEND QWTPLOT3DEXT_EXAMPLE_LINK_LIBRARIES shlwapi.lib)
endif()

if(CMAKE_THREAD_LIBS_INIT)
    list(APPEND QWTPLOT3DEXT_EXAMPLE_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
endif()

if(QWTPLOT3DEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QWTPLOT3DEXT_EXAMPLE_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui)
elseif(QWTPLOT3DEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QWTPLOT3DEXT_EXAMPLE_LINK_LIBRARIES
        Qt${QWTPLOT3DEXT_QT_VERSION_MAJOR}::Core
        Qt${QWTPLOT3DEXT_QT_VERSION_MAJOR}::Gui
        Qt${QWTPLOT3DEXT_QT_VERSION_MAJOR}::Widgets)
else()
    message(FATAL_ERROR "----QwtPlot3DExt---- Not find Qt package")
endif()

list(APPEND QWTPLOT3DEXT_EXAMPLE_LINK_LIBRARIES QwtPlot3DExt)



#--------------------------------------------------------------------------------
# define function
#--------------------------------------------------------------------------------
function(qwtPlot3DExtCopyDependenceLib target dependence)
    add_custom_command(
        TARGET ${target}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${dependence}> $<TARGET_FILE_DIR:${target}>
        COMMENT "copy the qwtPlot3DExt lib file to the same folder as the executable"
        POST_BUILD
        )
endfunction(qwtPlot3DExtCopyDependenceLib)

function(qwtPlot3DExtFunctionAddExample EXAMPLE_NAME)
    set(multiValueArgs EXAMPLE_SOURCE EXAMPLE_INCLUDE_DIRS)
    cmake_parse_arguments(MY "" "" "${multiValueArgs}" "${ARGN}")
    add_executable(${EXAMPLE_NAME} ${MY_EXAMPLE_SOURCE})
    target_link_libraries(${EXAMPLE_NAME} PRIVATE ${QWTPLOT3DEXT_EXAMPLE_LINK_LIBRARIES})
    target_include_directories(${EXAMPLE_NAME} PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${MY_EXAMPLE_INCLUDE_DIRS}
        ${QWTPLOT3DEXT_EXAMPLE_INCLUDE_DIRECTORIES}
        )
    set_property(TARGET ${EXAMPLE_NAME} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
    if(QWTPLOT3DEXT_BUILD_SHARED_LIBS AND WIN32)
        if (QWTPLOT3DEXT_QT_VERSION_MAJOR EQUAL 4)
            qwtPlot3DExtCopyDependenceLib(${EXAMPLE_NAME} Qt4::QtCore)
            qwtPlot3DExtCopyDependenceLib(${EXAMPLE_NAME} Qt4::QtGui)
            qwtPlot3DExtCopyDependenceLib(${EXAMPLE_NAME} QwtPlot3DExt)
        else(QWTPLOT3DEXT_QT_VERSION_MAJOR GREATER 4)
            qwtPlot3DExtCopyDependenceLib(${EXAMPLE_NAME} Qt${QWT_QT_VERSION_MAJOR}::Core)
            qwtPlot3DExtCopyDependenceLib(${EXAMPLE_NAME} Qt${QWT_QT_VERSION_MAJOR}::Gui)
            qwtPlot3DExtCopyDependenceLib(${EXAMPLE_NAME} Qt${QWT_QT_VERSION_MAJOR}::Widgets)
            qwtPlot3DExtCopyDependenceLib(${EXAMPLE_NAME} QwtPlot3DExt)
        endif()
    endif()
endfunction()



#--------------------------------------------------------------------------------
# Add example
#--------------------------------------------------------------------------------
qwtPlot3DExtFunctionAddExample(qwtPlot3DExt_exp_autoSwitch
    EXAMPLE_SOURCE
    autoswitch/autoswitch.cpp
    autoswitch/autoswitch.h
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/autoswitch
    )
qwtPlot3DExtFunctionAddExample(qwtPlot3DExt_exp_axes
    EXAMPLE_SOURCE
    axes/src/axes.h
    axes/src/axesmainwindow.cpp
    axes/src/axesmainwindow.h
    axes/src/axesmainwindowbase.ui
    axes/src/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/axes/src
    )
qwtPlot3DExtFunctionAddExample(qwtPlot3DExt_exp_curveplot
    EXAMPLE_SOURCE
    curveplot/curveplot.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/curveplot
    )
qwtPlot3DExtFunctionAddExample(qwtPlot3DExt_exp_dynamicplot
    EXAMPLE_SOURCE
    dynamicplot/dynamicplot.cpp
    dynamicplot/dynamicplot.h
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/dynamicplot
    )
qwtPlot3DExtFunctionAddExample(qwtPlot3DExt_exp_enrichments
    EXAMPLE_SOURCE
    enrichments/src/enrichmentmainwindow.cpp
    enrichments/src/enrichmentmainwindow.h
    enrichments/src/enrichmentmainwindowbase.ui
    enrichments/src/enrichments.cpp
    enrichments/src/enrichments.h
    enrichments/src/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/enrichments
    )
qwtPlot3DExtFunctionAddExample(qwtPlot3DExt_exp_freemesh
    EXAMPLE_SOURCE
    freemesh/femreader.h
    freemesh/freemesh.cpp
    freemesh/freemesh.h
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/freemesh
    )
qwtPlot3DExtFunctionAddExample(qwtPlot3DExt_exp_graph
    EXAMPLE_SOURCE
    graph/graph.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/graph
    )
qwtPlot3DExtFunctionAddExample(qwtPlot3DExt_exp_mesh
    EXAMPLE_SOURCE
    mesh/src/colormapreader.cpp
    mesh/src/colormapreader.h
    mesh/src/functions.h
    mesh/src/lightingdialog.cpp
    mesh/src/lightingdialog.h
    mesh/src/lightingdialogbase.ui
    mesh/src/main.cpp
    mesh/src/meshmainwindow.cpp
    mesh/src/meshmainwindow.h
    mesh/src/meshmainwindowbase.ui
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/mesh
    )
qwtPlot3DExtFunctionAddExample(qwtPlot3DExt_exp_plotlets
    EXAMPLE_SOURCE
    plotlets/src/configframe.cpp
    plotlets/src/configframe.h
    plotlets/src/configframebase.ui
    plotlets/src/functions.h
    plotlets/src/main.cpp
    plotlets/src/mainwindow.cpp
    plotlets/src/mainwindow.h
    plotlets/src/mainwindowbase.ui
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/plotlets
    )
qwtPlot3DExtFunctionAddExample(qwtPlot3DExt_exp_simpleplot
    EXAMPLE_SOURCE
    simpleplot/simpleplot.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/simpleplot
    )
qwtPlot3DExtFunctionAddExample(qwtPlot3DExt_exp_volumeplot
    EXAMPLE_SOURCE
    volumeplot/volumeplot.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/volumeplot
    )
