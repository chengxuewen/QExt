#-----------------------------------------------------------------------------------------------------------------------
# Function
#-----------------------------------------------------------------------------------------------------------------------
function(qwtCopyDependenceLib target dependence)
    add_custom_command(
        TARGET ${target}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${dependence}> $<TARGET_FILE_DIR:${target}>
        COMMENT "copy the qwt lib file to the same folder as the executable"
        POST_BUILD)
endfunction(qwtCopyDependenceLib)

function(qwt_add_example NAME)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(arg "" "" "${multiValueArgs}" "${ARGN}")
    add_executable(${NAME} ${arg_SOURCES})
    target_link_libraries(${NAME} PRIVATE Qwt)
    if (QWT_QT_VERSION_MAJOR EQUAL 4)
        qwtCopyDependenceLib(${NAME} Qt4::QtCore)
        qwtCopyDependenceLib(${NAME} Qt4::QtGui)
        qwtCopyDependenceLib(${NAME} Qwt)
    else(QWT_QT_VERSION_MAJOR GREATER 4)
        qwtCopyDependenceLib(${NAME} Qt${QWT_QT_VERSION_MAJOR}::Core)
        qwtCopyDependenceLib(${NAME} Qt${QWT_QT_VERSION_MAJOR}::Gui)
        qwtCopyDependenceLib(${NAME} Qt${QWT_QT_VERSION_MAJOR}::PrintSupport)
        qwtCopyDependenceLib(${NAME} Qt${QWT_QT_VERSION_MAJOR}::Svg)
        qwtCopyDependenceLib(${NAME} Qt${QWT_QT_VERSION_MAJOR}::Widgets)
        qwtCopyDependenceLib(${NAME} Qwt)
    endif()
    if (QWT_QT_OPENGL_FOUND)
        qwtCopyDependenceLib(${NAME} ${QWT_QT_OPENGL})
    endif()
endfunction(qwt_add_example)



#-----------------------------------------------------------------------------------------------------------------------
# Examples
#-----------------------------------------------------------------------------------------------------------------------
qwt_add_example(qwt_exp_animation
    SOURCES
    animation/main.cpp
    animation/plot.cpp
    animation/plot.h)
qwt_add_example(qwt_exp_barchart
    SOURCES
    barchart/barchart.cpp
    barchart/barchart.h
    barchart/main.cpp)
qwt_add_example(qwt_exp_bode
    SOURCES
    bode/complexnumber.h
    bode/main.cpp
    bode/mainwindow.cpp
    bode/mainwindow.h
    bode/pixmaps.h
    bode/plot.cpp
    bode/plot.h)
qwt_add_example(qwt_exp_controls
    SOURCES
    controls/dialbox.cpp
    controls/dialbox.h
    controls/dialtab.cpp
    controls/dialtab.h
    controls/knobbox.cpp
    controls/knobbox.h
    controls/knobtab.cpp
    controls/knobtab.h
    controls/main.cpp
    controls/sliderbox.cpp
    controls/sliderbox.h
    controls/slidertab.cpp
    controls/slidertab.h
    controls/wheelbox.cpp
    controls/wheelbox.h
    controls/wheeltab.cpp
    controls/wheeltab.h)
qwt_add_example(qwt_exp_cpuplot
    SOURCES
    cpuplot/cpupiemarker.cpp
    cpuplot/cpupiemarker.h
    cpuplot/cpuplot.cpp
    cpuplot/cpuplot.h
    cpuplot/cpustat.cpp
    cpuplot/cpustat.h)
qwt_add_example(qwt_exp_curv
    SOURCES
    curvdemo1/curvdemo1.cpp)
qwt_add_example(qwt_exp_dials
    SOURCES
    dials/attitude_indicator.cpp
    dials/attitude_indicator.h
    dials/cockpit_grid.cpp
    dials/cockpit_grid.h
    dials/compass_grid.cpp
    dials/compass_grid.h
    dials/dials.cpp
    dials/speedo_meter.cpp
    dials/speedo_meter.h)
qwt_add_example(qwt_exp_distrowatch
    SOURCES
    distrowatch/barchart.cpp
    distrowatch/barchart.h
    distrowatch/main.cpp)
qwt_add_example(qwt_exp_eventfilter
    SOURCES
    event_filter/canvaspicker.cpp
    event_filter/canvaspicker.h
    event_filter/colorbar.cpp
    event_filter/colorbar.h
    event_filter/event_filter.cpp
    event_filter/plot.cpp
    event_filter/plot.h
    event_filter/scalepicker.cpp
    event_filter/scalepicker.h)
qwt_add_example(qwt_exp_friedberg
    SOURCES
    friedberg/friedberg2007.cpp
    friedberg/friedberg2007.h
    friedberg/main.cpp
    friedberg/plot.cpp
    friedberg/plot.h)
qwt_add_example(qwt_exp_itemeditor
    SOURCES
    itemeditor/editor.cpp
    itemeditor/editor.h
    itemeditor/main.cpp
    itemeditor/plot.cpp
    itemeditor/plot.h
    itemeditor/shapefactory.cpp
    itemeditor/shapefactory.h)
qwt_add_example(qwt_exp_legends
    SOURCES
    legends/main.cpp
    legends/mainwindow.cpp
    legends/mainwindow.h
    legends/panel.cpp
    legends/panel.h
    legends/plot.cpp
    legends/plot.h
    legends/settings.h)
qwt_add_example(qwt_exp_oscilloscope
    SOURCES
    oscilloscope/curvedata.cpp
    oscilloscope/curvedata.h
    oscilloscope/knob.cpp
    oscilloscope/knob.h
    oscilloscope/main.cpp
    oscilloscope/mainwindow.cpp
    oscilloscope/mainwindow.h
    oscilloscope/plot.cpp
    oscilloscope/plot.h
    oscilloscope/samplingthread.cpp
    oscilloscope/samplingthread.h
    oscilloscope/signaldata.cpp
    oscilloscope/signaldata.h
    oscilloscope/wheelbox.cpp
    oscilloscope/wheelbox.h)
qwt_add_example(qwt_exp_radio
    SOURCES
    radio/ampfrm.cpp
    radio/ampfrm.h
    radio/mainwindow.cpp
    radio/mainwindow.h
    radio/radio.cpp
    radio/tunerfrm.cpp
    radio/tunerfrm.h)
qwt_add_example(qwt_exp_rasterview
    SOURCES
    rasterview/main.cpp
    rasterview/plot.cpp
    rasterview/plot.h)
qwt_add_example(qwt_exp_realtime
    SOURCES
    realtime/incrementalplot.cpp
    realtime/incrementalplot.h
    realtime/main.cpp
    realtime/mainwindow.cpp
    realtime/mainwindow.h
    realtime/randomplot.cpp
    realtime/randomplot.h
    realtime/scrollbar.cpp
    realtime/scrollbar.h
    realtime/scrollzoomer.cpp
    realtime/scrollzoomer.h)
qwt_add_example(qwt_exp_refreshtest
    SOURCES
    refreshtest/circularbuffer.cpp
    refreshtest/circularbuffer.h
    refreshtest/main.cpp
    refreshtest/mainwindow.cpp
    refreshtest/mainwindow.h
    refreshtest/panel.cpp
    refreshtest/panel.h
    refreshtest/plot.cpp
    refreshtest/plot.h
    refreshtest/settings.h)
qwt_add_example(qwt_exp_scatterplot
    SOURCES
    scatterplot/main.cpp
    scatterplot/mainwindow.cpp
    scatterplot/mainwindow.h
    scatterplot/plot.cpp
    scatterplot/plot.h)
qwt_add_example(qwt_exp_simpleplot
    SOURCES
    simpleplot/simpleplot.cpp)
qwt_add_example(qwt_exp_sinusplot
    SOURCES
    sinusplot/sinusplot.cpp)
qwt_add_example(qwt_exp_spectrogram
    SOURCES
    spectrogram/main.cpp
    spectrogram/plot.cpp
    spectrogram/plot.h)
qwt_add_example(qwt_exp_stockchart
    SOURCES
    stockchart/griditem.cpp
    stockchart/griditem.h
    stockchart/legend.cpp
    stockchart/legend.h
    stockchart/main.cpp
    stockchart/plot.cpp
    stockchart/plot.h
    stockchart/quotefactory.cpp
    stockchart/quotefactory.h)
qwt_add_example(qwt_exp_sysinfo
    SOURCES
    sysinfo/sysinfo.cpp)
qwt_add_example(qwt_exp_tvplot
    SOURCES
    tvplot/main.cpp
    tvplot/tvplot.cpp
    tvplot/tvplot.h)
