#--------------------------------------------------------------------------------
# Set example output path
#--------------------------------------------------------------------------------
set(EXECUTABLE_OUTPUT_PATH ${QWTPLOT3D_EXAMPLE_OUTPUT_DIR})
set(LIBRARY_OUTPUT_PATH ${QWTPLOT3D_EXAMPLE_OUTPUT_DIR})



#--------------------------------------------------------------------------------
# Set example link libraries
#--------------------------------------------------------------------------------
set(QWTPLOT3D_EXAMPLE_LINK_LIBRARIES)

if(UNIX)
    list(APPEND QWTPLOT3D_EXAMPLE_LINK_LIBRARIES dl)
endif()

if(WIN32)
    list(APPEND QWTPLOT3D_EXAMPLE_LINK_LIBRARIES shlwapi.lib)
endif()

if(CMAKE_THREAD_LIBS_INIT)
    list(APPEND QWTPLOT3D_EXAMPLE_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
endif()

if(QWTPLOT3D_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QWTPLOT3D_EXAMPLE_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui)
elseif(QWTPLOT3D_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QWTPLOT3D_EXAMPLE_LINK_LIBRARIES
        Qt${QWTPLOT3D_QT_VERSION_MAJOR}::Core
        Qt${QWTPLOT3D_QT_VERSION_MAJOR}::Gui
        Qt${QWTPLOT3D_QT_VERSION_MAJOR}::Widgets)
else()
    message(FATAL_ERROR "----QwtPlot3D---- Not find Qt package")
endif()

list(APPEND QWTPLOT3D_EXAMPLE_LINK_LIBRARIES QwtPlot3D)



#--------------------------------------------------------------------------------
# define function
#--------------------------------------------------------------------------------
function(qwtPlot3DCopyDependenceLib target dependence)
    add_custom_command(
        TARGET ${target}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${dependence}> $<TARGET_FILE_DIR:${target}>
        COMMENT "copy the qwtPlot3D lib file to the same folder as the executable"
        POST_BUILD
        )
endfunction(qwtPlot3DCopyDependenceLib)

function(qwtPlot3DFunctionAddExample EXAMPLE_NAME)
    set(multiValueArgs EXAMPLE_SOURCE EXAMPLE_INCLUDE_DIRS)
    cmake_parse_arguments(MY "" "" "${multiValueArgs}" "${ARGN}")
    add_executable(${EXAMPLE_NAME} ${MY_EXAMPLE_SOURCE})
    target_link_libraries(${EXAMPLE_NAME} PRIVATE ${QWTPLOT3D_EXAMPLE_LINK_LIBRARIES})
    target_include_directories(${EXAMPLE_NAME} PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${MY_EXAMPLE_INCLUDE_DIRS}
        ${QWTPLOT3D_EXAMPLE_INCLUDE_DIRECTORIES}
        )
    set_property(TARGET ${EXAMPLE_NAME} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
    if(QWTPLOT3D_BUILD_SHARED_LIBS AND WIN32)
        if (QWTPLOT3D_QT_VERSION_MAJOR EQUAL 4)
            qwtPlot3DCopyDependenceLib(${EXAMPLE_NAME} Qt4::QtCore)
            qwtPlot3DCopyDependenceLib(${EXAMPLE_NAME} Qt4::QtGui)
            qwtPlot3DCopyDependenceLib(${EXAMPLE_NAME} QwtPlot3D)
        else(QWTPLOT3D_QT_VERSION_MAJOR GREATER 4)
            qwtPlot3DCopyDependenceLib(${EXAMPLE_NAME} Qt${QWT_QT_VERSION_MAJOR}::Core)
            qwtPlot3DCopyDependenceLib(${EXAMPLE_NAME} Qt${QWT_QT_VERSION_MAJOR}::Gui)
            qwtPlot3DCopyDependenceLib(${EXAMPLE_NAME} Qt${QWT_QT_VERSION_MAJOR}::Widgets)
            qwtPlot3DCopyDependenceLib(${EXAMPLE_NAME} QwtPlot3D)
        endif()
    endif()
endfunction()



#--------------------------------------------------------------------------------
# Add example
#--------------------------------------------------------------------------------
qwtPlot3DFunctionAddExample(qwtPlot3D_exp_autoSwitch
    EXAMPLE_SOURCE
    autoswitch/autoswitch.cpp
    autoswitch/autoswitch.h
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/autoswitch
    )
qwtPlot3DFunctionAddExample(qwtPlot3D_exp_axes
    EXAMPLE_SOURCE
    axes/src/axes.h
    axes/src/axesmainwindow.cpp
    axes/src/axesmainwindow.h
    axes/src/axesmainwindowbase.ui
    axes/src/axesmainwindowbase4.ui
    axes/src/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/axes/src
    )
qwtPlot3DFunctionAddExample(qwtPlot3D_exp_enrichments
    EXAMPLE_SOURCE
    enrichments/src/enrichmentmainwindow.cpp
    enrichments/src/enrichmentmainwindow.h
    enrichments/src/enrichmentmainwindowbase.ui
    enrichments/src/enrichmentmainwindowbase4.ui
    enrichments/src/enrichments.cpp
    enrichments/src/enrichments.h
    enrichments/src/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/enrichments
    )
#qwtPlot3DFunctionAddExample(qwtPlot3D_exp_mesh2
#    EXAMPLE_SOURCE
#    mesh2/src/colormapreader.cpp
#    mesh2/src/colormapreader.h
#    mesh2/src/designerworkaround.cpp
#    mesh2/src/designerworkaround.h
#    mesh2/src/femreader.h
#    mesh2/src/functions.h
#    mesh2/src/lightingdlg.cpp
#    mesh2/src/lightingdlg.h
##    mesh2/src/lightingdlgbase.ui
#    mesh2/src/lightingdlgbase4.ui
#    mesh2/src/lightingdlgbaseimpl.cpp
#    mesh2/src/lightingdlgbaseimpl.h
#    mesh2/src/main.cpp
#    mesh2/src/mesh.cpp
#    mesh2/src/mesh2mainwindow.cpp
#    mesh2/src/mesh2mainwindow.h
##    mesh2/src/mesh2mainwindowbase.ui
#    mesh2/src/mesh2mainwindowbase4.ui
#    EXAMPLE_INCLUDE_DIRS
#    ${CMAKE_CURRENT_SOURCE_DIR}/mesh2/src
#    )
qwtPlot3DFunctionAddExample(qwtPlot3D_exp_simpleplot
    EXAMPLE_SOURCE
    simpleplot/simpleplot.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/simpleplot
    )
