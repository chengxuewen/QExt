#----------------------------------------------------------------
# Function
#----------------------------------------------------------------
function(qwtCopyDependenceLib target dependence)
    add_custom_command(
        TARGET ${target}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${dependence}> $<TARGET_FILE_DIR:${target}>
        COMMENT "copy the lib file to the same folder as the executable"
        POST_BUILD
        )
endfunction(qwtCopyDependenceLib)

function(qwtAddExample EXAMPLE_NAME)
    set(multiValueArgs EXAMPLE_SOURCE)
    cmake_parse_arguments(MY "" "" "${multiValueArgs}" "${ARGN}")
    add_executable(${EXAMPLE_NAME} ${MY_EXAMPLE_SOURCE})
    target_link_libraries(${EXAMPLE_NAME} PRIVATE Qwt)
    if (QWT_QT_VERSION_MAJOR EQUAL 4)
        qwtCopyDependenceLib(${EXAMPLE_NAME} Qt4::QtCore)
        qwtCopyDependenceLib(${EXAMPLE_NAME} Qt4::QtGui)
        qwtCopyDependenceLib(${EXAMPLE_NAME} Qt4::QtOpenGL)
        qwtCopyDependenceLib(${EXAMPLE_NAME} Qwt)
    else(QWT_QT_VERSION_MAJOR GREATER 4)
        qwtCopyDependenceLib(${EXAMPLE_NAME} Qt${QWT_QT_VERSION_MAJOR}::Core)
        qwtCopyDependenceLib(${EXAMPLE_NAME} Qt${QWT_QT_VERSION_MAJOR}::Gui)
        qwtCopyDependenceLib(${EXAMPLE_NAME} Qt${QWT_QT_VERSION_MAJOR}::OpenGL)
        qwtCopyDependenceLib(${EXAMPLE_NAME} Qt${QWT_QT_VERSION_MAJOR}::PrintSupport)
        qwtCopyDependenceLib(${EXAMPLE_NAME} Qt${QWT_QT_VERSION_MAJOR}::Svg)
        qwtCopyDependenceLib(${EXAMPLE_NAME} Qt${QWT_QT_VERSION_MAJOR}::Widgets)
        qwtCopyDependenceLib(${EXAMPLE_NAME} Qwt)
    endif()
endfunction(qwtAddExample)

#----------------------------------------------------------------
# Examples
#----------------------------------------------------------------
qwtAddExample(qwt_exp_animation EXAMPLE_SOURCE
    animation/main.cpp
    animation/plot.cpp
    animation/plot.h
    )
qwtAddExample(qwt_exp_barchart EXAMPLE_SOURCE
    barchart/barchart.cpp
    barchart/barchart.h
    barchart/main.cpp
    )
qwtAddExample(qwt_exp_bode EXAMPLE_SOURCE
    bode/complexnumber.h
    bode/main.cpp
    bode/mainwindow.cpp
    bode/mainwindow.h
    bode/pixmaps.h
    bode/plot.cpp
    bode/plot.h
    )
qwtAddExample(qwt_exp_controls EXAMPLE_SOURCE
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
    controls/wheeltab.h
    )
qwtAddExample(qwt_exp_cpuplot EXAMPLE_SOURCE
    cpuplot/cpupiemarker.cpp
    cpuplot/cpupiemarker.h
    cpuplot/cpuplot.cpp
    cpuplot/cpuplot.h
    cpuplot/cpustat.cpp
    cpuplot/cpustat.h
    )
qwtAddExample(qwt_exp_curv EXAMPLE_SOURCE
    curvdemo1/curvdemo1.cpp
    )
qwtAddExample(qwt_exp_dials EXAMPLE_SOURCE
    dials/attitude_indicator.cpp
    dials/attitude_indicator.h
    dials/cockpit_grid.cpp
    dials/cockpit_grid.h
    dials/compass_grid.cpp
    dials/compass_grid.h
    dials/dials.cpp
    dials/speedo_meter.cpp
    dials/speedo_meter.h
    )
qwtAddExample(qwt_exp_distrowatch EXAMPLE_SOURCE
    distrowatch/barchart.cpp
    distrowatch/barchart.h
    distrowatch/main.cpp
    )
qwtAddExample(qwt_exp_eventfilter EXAMPLE_SOURCE
    event_filter/canvaspicker.cpp
    event_filter/canvaspicker.h
    event_filter/colorbar.cpp
    event_filter/colorbar.h
    event_filter/event_filter.cpp
    event_filter/plot.cpp
    event_filter/plot.h
    event_filter/scalepicker.cpp
    event_filter/scalepicker.h
    )
qwtAddExample(qwt_exp_friedberg EXAMPLE_SOURCE
    friedberg/friedberg2007.cpp
    friedberg/friedberg2007.h
    friedberg/main.cpp
    friedberg/plot.cpp
    friedberg/plot.h
    )
qwtAddExample(qwt_exp_itemeditor EXAMPLE_SOURCE
    itemeditor/editor.cpp
    itemeditor/editor.h
    itemeditor/main.cpp
    itemeditor/plot.cpp
    itemeditor/plot.h
    itemeditor/shapefactory.cpp
    itemeditor/shapefactory.h
    )
qwtAddExample(qwt_exp_legends EXAMPLE_SOURCE
    legends/main.cpp
    legends/mainwindow.cpp
    legends/mainwindow.h
    legends/panel.cpp
    legends/panel.h
    legends/plot.cpp
    legends/plot.h
    legends/settings.h
    )
qwtAddExample(qwt_exp_oscilloscope EXAMPLE_SOURCE
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
    oscilloscope/wheelbox.h
    )
qwtAddExample(qwt_exp_radio EXAMPLE_SOURCE
    radio/ampfrm.cpp
    radio/ampfrm.h
    radio/mainwindow.cpp
    radio/mainwindow.h
    radio/radio.cpp
    radio/tunerfrm.cpp
    radio/tunerfrm.h
    )
qwtAddExample(qwt_exp_rasterview EXAMPLE_SOURCE
    rasterview/main.cpp
    rasterview/plot.cpp
    rasterview/plot.h
    )
qwtAddExample(qwt_exp_realtime EXAMPLE_SOURCE
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
    realtime/scrollzoomer.h
    )
qwtAddExample(qwt_exp_refreshtest EXAMPLE_SOURCE
    refreshtest/circularbuffer.cpp
    refreshtest/circularbuffer.h
    refreshtest/main.cpp
    refreshtest/mainwindow.cpp
    refreshtest/mainwindow.h
    refreshtest/panel.cpp
    refreshtest/panel.h
    refreshtest/plot.cpp
    refreshtest/plot.h
    refreshtest/settings.h
    )
qwtAddExample(qwt_exp_scatterplot EXAMPLE_SOURCE
    scatterplot/main.cpp
    scatterplot/mainwindow.cpp
    scatterplot/mainwindow.h
    scatterplot/plot.cpp
    scatterplot/plot.h
    )
qwtAddExample(qwt_exp_simpleplot EXAMPLE_SOURCE
    simpleplot/simpleplot.cpp
    )
qwtAddExample(qwt_exp_sinusplot EXAMPLE_SOURCE
    sinusplot/sinusplot.cpp
    )
qwtAddExample(qwt_exp_spectrogram EXAMPLE_SOURCE
    spectrogram/main.cpp
    spectrogram/plot.cpp
    spectrogram/plot.h
    )
qwtAddExample(qwt_exp_stockchart EXAMPLE_SOURCE
    stockchart/griditem.cpp
    stockchart/griditem.h
    stockchart/legend.cpp
    stockchart/legend.h
    stockchart/main.cpp
    stockchart/plot.cpp
    stockchart/plot.h
    stockchart/quotefactory.cpp
    stockchart/quotefactory.h
    )
qwtAddExample(qwt_exp_sysinfo EXAMPLE_SOURCE
    sysinfo/sysinfo.cpp
    )
qwtAddExample(qwt_exp_tvplot EXAMPLE_SOURCE
    tvplot/main.cpp
    tvplot/tvplot.cpp
    tvplot/tvplot.h
    )
