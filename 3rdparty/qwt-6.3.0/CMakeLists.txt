#-----------------------------------------------------------------------------------------------------------------------
# Set cmake min version and policy
#-----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)


#-----------------------------------------------------------------------------------------------------------------------
# Set project name and version
#-----------------------------------------------------------------------------------------------------------------------
message(STATUS "================================================Qwt===================================================")
project(Qwt VERSION 6.3.0 LANGUAGES CXX)
set(QWT_VERSION_NAME ${PROJECT_VERSION})
set(QWT_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(QWT_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(QWT_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(QWT_VERSION_TWEAK ${PROJECT_VERSION_TWEAK})
set(QWT_VERSION ${QWT_VERSION_MAJOR}.${QWT_VERSION_MINOR}.${QWT_VERSION_PATCH})
set(QWT_SO_VERSION ${QWT_VERSION_MAJOR}.${QWT_VERSION_MINOR})
set(QWT_DEBUG_POSTFIX "d")
set(QWT_VERSION_STR "${QWT_VERSION_MAJOR}.${QWT_VERSION_MINOR}.${QWT_VERSION_PATCH}")
set(QWT_LICENSE "Qwt License")
set(QWT_PRODUCT_NAME "Qwt")
set(QWT_CXX_STANDARD 98)
math(EXPR QWT_VERSION_CALC "${QWT_VERSION_MAJOR}*1000 + ${QWT_VERSION_MINOR}*100 + ${QWT_VERSION_PATCH}")
message(STATUS "Project version: Qwt ${QWT_VERSION}")
message(STATUS "Project license: ${QWT_LICENSE}")


#-----------------------------------------------------------------------------------------------------------------------
# find qt and include path, set cmake moc uic rcc on
#-----------------------------------------------------------------------------------------------------------------------
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt4 QUIET COMPONENTS QtCore QUIET)
if(NOT QT_FOUND)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core QUIET)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core QUIET)
endif()
set(QWT_QT_VERSION_MAJOR ${QT_VERSION_MAJOR})
set(QWT_QT_VERSION_MINOR ${QT_VERSION_MINOR})
set(QWT_QT_VERSION_PATCH ${QT_VERSION_PATCH})
set(QWT_QT_VERSION "${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")
set(QWT_QT_OPENGL_FOUND OFF)
set(QWT_QT_OPENGL)

if(QWT_QT_VERSION_MAJOR EQUAL 4)
    if(QWT_QT_VERSION_MINOR LESS 5)
        message(FATAL_ERROR "Expected Qt4 version must greater than or equal to Qt4.5")
    endif()
    message(STATUS "Expected Qt version is Qt4")
    set(QWT_QT_DEP_COMPONENTS QtCore QtGui QtSvg)
    find_package(Qt4 COMPONENTS ${QWT_QT_DEP_COMPONENTS} REQUIRED)
    find_package(Qt4 COMPONENTS QtOpenGL QUIET)
    set(QWT_QT_OPENGL_FOUND QtOpenGL_FOUND)
    if(QWT_QT_OPENGL_FOUND)
        list(APPEND QWT_QT_DEP_COMPONENTS QtOpenGL)
        set(QWT_QT_OPENGL QtOpenGL)
    endif()
    list(APPEND QWT_QT_DEP_LIBRARIES
        Qt4::QtCore
        Qt4::QtGui
        Qt4::QtSvg
        ${QWT_QT_OPENGL})
    include(${QT_USE_FILE})
    add_definitions(${QT_DEFINITIONS})
elseif(QWT_QT_VERSION_MAJOR EQUAL 5)
    message(STATUS "Expected Qt version is Qt${QWT_QT_VERSION}")
    set(QWT_QT_DEP_COMPONENTS Core Gui Widgets Concurrent PrintSupport Svg)
    find_package(Qt${QWT_QT_VERSION_MAJOR} COMPONENTS ${QWT_QT_DEP_COMPONENTS} REQUIRED)
    find_package(Qt${QWT_QT_VERSION_MAJOR} COMPONENTS OpenGL QUIET)
    set(QWT_QT_OPENGL_FOUND ${Qt${QWT_QT_VERSION_MAJOR}OpenGL_FOUND})
    if(QWT_QT_OPENGL_FOUND)
        list(APPEND QWT_QT_DEP_COMPONENTS OpenGL)
        set(QWT_QT_OPENGL Qt${QWT_QT_VERSION_MAJOR}::OpenGL)
    endif()
    list(APPEND QWT_QT_DEP_LIBRARIES
        Qt${QWT_QT_VERSION_MAJOR}::Core
        Qt${QWT_QT_VERSION_MAJOR}::Gui
        Qt${QWT_QT_VERSION_MAJOR}::Widgets
        Qt${QWT_QT_VERSION_MAJOR}::Concurrent
        Qt${QWT_QT_VERSION_MAJOR}::PrintSupport
        Qt${QWT_QT_VERSION_MAJOR}::Svg
        ${QWT_QT_OPENGL})
elseif(QWT_QT_VERSION_MAJOR EQUAL 6)
    message(STATUS "Expected Qt version is Qt${QWT_QT_VERSION}")
    set(QWT_QT_DEP_COMPONENTS Core Gui Widgets Concurrent PrintSupport Svg)
    find_package(Qt${QWT_QT_VERSION_MAJOR} COMPONENTS ${QWT_QT_DEP_COMPONENTS} REQUIRED)
    find_package(Qt${QWT_QT_VERSION_MAJOR} COMPONENTS OpenGL QUIET)
    set(QWT_QT_OPENGL_FOUND ${Qt${QWT_QT_VERSION_MAJOR}OpenGL_FOUND})
    if(QWT_QT_OPENGL_FOUND)
        list(APPEND QWT_QT_DEP_COMPONENTS OpenGL)
        set(QWT_QT_OPENGL Qt${QWT_QT_VERSION_MAJOR}::OpenGL)
    endif()
    list(APPEND QWT_QT_DEP_LIBRARIES
        Qt${QWT_QT_VERSION_MAJOR}::Core
        Qt${QWT_QT_VERSION_MAJOR}::Gui
        Qt${QWT_QT_VERSION_MAJOR}::Widgets
        Qt${QWT_QT_VERSION_MAJOR}::Concurrent
        Qt${QWT_QT_VERSION_MAJOR}::PrintSupport
        Qt${QWT_QT_VERSION_MAJOR}::Svg
        ${QWT_QT_OPENGL})
else()
    message(FATAL_ERROR "Not find Qt package")
endif()
set(QWT_QT_FINDPKG_CMD Qt${QWT_QT_VERSION_MAJOR} COMPONENTS ${QWT_QT_DEP_COMPONENTS} REQUIRED)
string(REPLACE ";" " " QWT_QT_FINDPKG_CMDSTR "${QWT_QT_FINDPKG_CMD}")

if(QWT_QT_OPENGL_FOUND)
    message(STATUS "Qt${QWT_QT_VERSION_MAJOR} OpenGL found")
endif()

get_filename_component(QWT_QT_BIN_DIR "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
get_filename_component(QWT_QT_KIT_DIR "${QWT_QT_BIN_DIR}" DIRECTORY)
set(QWT_QT_LIB_DIR ${QWT_QT_KIT_DIR}/lib)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


#-----------------------------------------------------------------------------------------------------------------------
# Set option
#-----------------------------------------------------------------------------------------------------------------------
option(QWT_BUILD_SHARED_LIBS "Build shared library" ON)
option(QWT_BUILD_TESTS "Build tests" OFF)
option(QWT_BUILD_EXAMPLES "Build examples" OFF)
option(QWT_BUILD_PLAYGROUND "Build playground" OFF)
option(QWT_BUILD_COMPILER_WARNING "Build target with compiler warnings" OFF)
option(QWT_BUILD_INSTALL "Build with install" OFF)
option(QWT_BUILD_ALL "Build all artifacts" OFF)

if(QWT_BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ON CACHE BOOL "Build as shared libraries")
    message(STATUS "Build as shared libraries")
else()
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build as static libraries")
    message(STATUS "Build as static libraries")
endif()

if(QWT_BUILD_TESTS OR QWT_BUILD_ALL)
    enable_testing()
endif()

if(CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Qwt CMAKE_CONFIGURATION_TYPES was set to: '${CMAKE_BUILD_TYPE}'")
    set(CMAKE_CONFIGURATION_TYPES "${CMAKE_BUILD_TYPE}" CACHE INTERNAL "Force disable CMAKE_CONFIGURATION_TYPES." FORCE)
endif()


#-----------------------------------------------------------------------------------------------------------------------
# Sources
#-----------------------------------------------------------------------------------------------------------------------
set(QWT_HEADERS
    ${PROJECT_SOURCE_DIR}/src/qwt.h
    ${PROJECT_SOURCE_DIR}/src/qwt_abstract_legend.h
    ${PROJECT_SOURCE_DIR}/src/qwt_abstract_scale.h
    ${PROJECT_SOURCE_DIR}/src/qwt_abstract_scale_draw.h
    ${PROJECT_SOURCE_DIR}/src/qwt_abstract_slider.h
    ${PROJECT_SOURCE_DIR}/src/qwt_analog_clock.h
    ${PROJECT_SOURCE_DIR}/src/qwt_arrow_button.h
    ${PROJECT_SOURCE_DIR}/src/qwt_axis.h
    ${PROJECT_SOURCE_DIR}/src/qwt_axis_id.h
    ${PROJECT_SOURCE_DIR}/src/qwt_bezier.h
    ${PROJECT_SOURCE_DIR}/src/qwt_clipper.h
    ${PROJECT_SOURCE_DIR}/src/qwt_color_map.h
    ${PROJECT_SOURCE_DIR}/src/qwt_column_symbol.h
    ${PROJECT_SOURCE_DIR}/src/qwt_compass.h
    ${PROJECT_SOURCE_DIR}/src/qwt_compass_rose.h
    ${PROJECT_SOURCE_DIR}/src/qwt_compat.h
    ${PROJECT_SOURCE_DIR}/src/qwt_counter.h
    ${PROJECT_SOURCE_DIR}/src/qwt_curve_fitter.h
    ${PROJECT_SOURCE_DIR}/src/qwt_date.h
    ${PROJECT_SOURCE_DIR}/src/qwt_date_scale_draw.h
    ${PROJECT_SOURCE_DIR}/src/qwt_date_scale_engine.h
    ${PROJECT_SOURCE_DIR}/src/qwt_dial.h
    ${PROJECT_SOURCE_DIR}/src/qwt_dial_needle.h
    ${PROJECT_SOURCE_DIR}/src/qwt_dyngrid_layout.h
    ${PROJECT_SOURCE_DIR}/src/qwt_event_pattern.h
    ${PROJECT_SOURCE_DIR}/src/qwt_global.h
    ${PROJECT_SOURCE_DIR}/src/qwt_graphic.h
    ${PROJECT_SOURCE_DIR}/src/qwt_interval.h
    ${PROJECT_SOURCE_DIR}/src/qwt_interval_symbol.h
    ${PROJECT_SOURCE_DIR}/src/qwt_knob.h
    ${PROJECT_SOURCE_DIR}/src/qwt_legend.h
    ${PROJECT_SOURCE_DIR}/src/qwt_legend_data.h
    ${PROJECT_SOURCE_DIR}/src/qwt_legend_label.h
    ${PROJECT_SOURCE_DIR}/src/qwt_magnifier.h
    ${PROJECT_SOURCE_DIR}/src/qwt_math.h
    ${PROJECT_SOURCE_DIR}/src/qwt_matrix_raster_data.h
    ${PROJECT_SOURCE_DIR}/src/qwt_null_paintdevice.h
    ${PROJECT_SOURCE_DIR}/src/qwt_painter.h
    ${PROJECT_SOURCE_DIR}/src/qwt_painter_command.h
    ${PROJECT_SOURCE_DIR}/src/qwt_panner.h
    ${PROJECT_SOURCE_DIR}/src/qwt_picker.h
    ${PROJECT_SOURCE_DIR}/src/qwt_picker_machine.h
    ${PROJECT_SOURCE_DIR}/src/qwt_pixel_matrix.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_abstract_barchart.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_abstract_canvas.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_barchart.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_canvas.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_curve.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_dict.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_directpainter.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_graphicitem.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_grid.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_histogram.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_intervalcurve.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_item.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_layout.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_legenditem.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_magnifier.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_marker.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_multi_barchart.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_opengl_canvas.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_panner.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_picker.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_rasteritem.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_renderer.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_rescaler.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_scaleitem.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_seriesitem.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_shapeitem.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_spectrocurve.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_spectrogram.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_svgitem.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_textlabel.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_tradingcurve.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_vectorfield.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_zoneitem.h
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_zoomer.h
    ${PROJECT_SOURCE_DIR}/src/qwt_point_3d.h
    ${PROJECT_SOURCE_DIR}/src/qwt_point_data.h
    ${PROJECT_SOURCE_DIR}/src/qwt_point_mapper.h
    ${PROJECT_SOURCE_DIR}/src/qwt_point_polar.h
    ${PROJECT_SOURCE_DIR}/src/qwt_polar.h
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_canvas.h
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_curve.h
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_fitter.h
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_grid.h
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_item.h
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_itemdict.h
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_layout.h
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_magnifier.h
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_marker.h
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_panner.h
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_picker.h
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_plot.h
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_renderer.h
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_spectrogram.h
    ${PROJECT_SOURCE_DIR}/src/qwt_raster_data.h
    ${PROJECT_SOURCE_DIR}/src/qwt_round_scale_draw.h
    ${PROJECT_SOURCE_DIR}/src/qwt_samples.h
    ${PROJECT_SOURCE_DIR}/src/qwt_sampling_thread.h
    ${PROJECT_SOURCE_DIR}/src/qwt_scale_div.h
    ${PROJECT_SOURCE_DIR}/src/qwt_scale_draw.h
    ${PROJECT_SOURCE_DIR}/src/qwt_scale_engine.h
    ${PROJECT_SOURCE_DIR}/src/qwt_scale_map.h
    ${PROJECT_SOURCE_DIR}/src/qwt_scale_widget.h
    ${PROJECT_SOURCE_DIR}/src/qwt_series_data.h
    ${PROJECT_SOURCE_DIR}/src/qwt_series_store.h
    ${PROJECT_SOURCE_DIR}/src/qwt_slider.h
    ${PROJECT_SOURCE_DIR}/src/qwt_spline.h
    ${PROJECT_SOURCE_DIR}/src/qwt_spline_basis.h
    ${PROJECT_SOURCE_DIR}/src/qwt_spline_cubic.h
    ${PROJECT_SOURCE_DIR}/src/qwt_spline_curve_fitter.h
    ${PROJECT_SOURCE_DIR}/src/qwt_spline_local.h
    ${PROJECT_SOURCE_DIR}/src/qwt_spline_parametrization.h
    ${PROJECT_SOURCE_DIR}/src/qwt_spline_pleasing.h
    ${PROJECT_SOURCE_DIR}/src/qwt_spline_polynomial.h
    ${PROJECT_SOURCE_DIR}/src/qwt_symbol.h
    ${PROJECT_SOURCE_DIR}/src/qwt_system_clock.h
    ${PROJECT_SOURCE_DIR}/src/qwt_text.h
    ${PROJECT_SOURCE_DIR}/src/qwt_text_engine.h
    ${PROJECT_SOURCE_DIR}/src/qwt_text_label.h
    ${PROJECT_SOURCE_DIR}/src/qwt_thermo.h
    ${PROJECT_SOURCE_DIR}/src/qwt_transform.h
    ${PROJECT_SOURCE_DIR}/src/qwt_vectorfield_symbol.h
    ${PROJECT_SOURCE_DIR}/src/qwt_weeding_curve_fitter.h
    ${PROJECT_SOURCE_DIR}/src/qwt_wheel.h
    ${PROJECT_SOURCE_DIR}/src/qwt_widget_overlay.h)

set(QWT_SOURCES
    ${PROJECT_SOURCE_DIR}/src/qwt.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_abstract_legend.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_abstract_scale.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_abstract_scale_draw.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_abstract_slider.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_analog_clock.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_arrow_button.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_bezier.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_clipper.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_color_map.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_column_symbol.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_compass.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_compass_rose.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_counter.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_curve_fitter.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_date.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_date_scale_draw.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_date_scale_engine.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_dial.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_dial_needle.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_dyngrid_layout.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_event_pattern.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_graphic.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_interval.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_interval_symbol.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_knob.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_legend.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_legend_data.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_legend_label.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_magnifier.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_math.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_matrix_raster_data.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_null_paintdevice.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_painter.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_painter_command.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_panner.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_picker.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_picker_machine.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_pixel_matrix.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_abstract_barchart.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_abstract_canvas.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_axis.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_barchart.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_canvas.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_curve.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_dict.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_directpainter.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_graphicitem.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_grid.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_histogram.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_intervalcurve.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_item.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_layout.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_legenditem.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_magnifier.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_marker.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_multi_barchart.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_opengl_canvas.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_panner.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_picker.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_rasteritem.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_renderer.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_rescaler.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_scaleitem.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_seriesitem.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_shapeitem.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_spectrocurve.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_spectrogram.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_svgitem.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_textlabel.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_tradingcurve.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_vectorfield.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_zoneitem.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_plot_zoomer.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_point_3d.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_point_data.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_point_mapper.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_point_polar.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_canvas.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_curve.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_fitter.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_grid.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_item.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_itemdict.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_layout.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_magnifier.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_marker.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_panner.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_picker.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_plot.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_renderer.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_polar_spectrogram.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_raster_data.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_round_scale_draw.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_sampling_thread.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_scale_div.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_scale_draw.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_scale_engine.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_scale_map.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_scale_widget.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_series_data.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_slider.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_spline.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_spline_basis.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_spline_cubic.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_spline_curve_fitter.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_spline_local.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_spline_parametrization.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_spline_pleasing.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_spline_polynomial.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_symbol.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_system_clock.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_text.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_text_engine.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_text_label.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_thermo.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_transform.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_vectorfield_symbol.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_weeding_curve_fitter.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_wheel.cpp
    ${PROJECT_SOURCE_DIR}/src/qwt_widget_overlay.cpp)

if(QWT_QT_OPENGL_FOUND)
    list(APPEND QWT_HEADERS ${PROJECT_SOURCE_DIR}/src/qwt_plot_glcanvas.h)
    list(APPEND QWT_SOURCES ${PROJECT_SOURCE_DIR}/src/qwt_plot_glcanvas.cpp)
endif()


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
if(QWT_BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED ${QWT_HEADERS} ${QWT_SOURCES})
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC
        $<$<BOOL:MSVC>:QWT_DLL>
        PRIVATE
        $<$<BOOL:MSVC>:QWT_MAKEDLL>)
else()
    add_library(${PROJECT_NAME} STATIC ${QWT_HEADERS} ${QWT_SOURCES})
endif()

if(NOT QWT_QT_OPENGL_FOUND)
    target_compile_definitions(${PROJECT_NAME} PUBLIC QWT_NO_OPENGL)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/classincludes>)

target_link_libraries(${PROJECT_NAME} PUBLIC ${QWT_QT_DEP_LIBRARIES})
message(--"${PROJECT_BINARY_DIR}/lib")
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/lib")
foreach(library ${QWT_QT_DEP_LIBRARIES})
    if (TARGET ${library})
        string(FIND "${library}" "Qt" prefix_pos)
        if (prefix_pos EQUAL 0)
            string(LENGTH "${library}" len)
            string(LENGTH "Private" private_len)
            string(FIND "${library}" "Private" suffix_pos)
            math(EXPR suffix_start "${len} - ${private_len}")
            if(NOT suffix_pos EQUAL suffix_start)
#                message(library="${library}")
                add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_SONAME_FILE:${library}>* "${PROJECT_BINARY_DIR}/lib/")
            endif()
        endif()
    endif()
endforeach()

set_target_properties(${PROJECT_NAME} PROPERTIES
    INSTALL_RPATH "\$ORIGIN"
    BUILD_WITH_INSTALL_RPATH TRUE)

if(QWT_BUILD_INSTALL)
    include(GNUInstallDirs)
    install(DIRECTORY ${PROJECT_BINARY_DIR}/lib
        DESTINATION ${CMAKE_INSTALL_PREFIX})

    install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}-target
        FRAMEWORK DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/Qwt
        ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR})

    file(GLOB QWT_CLASS_INCLUDES "${PROJECT_SOURCE_DIR}/classincludes/*")
    install(FILES ${QWT_CLASS_INCLUDES}
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/Qwt)

    install(FILES ${QWT_HEADERS}
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/Qwt)

    install(EXPORT ${PROJECT_NAME}-target
        FILE ${PROJECT_NAME}-targets.cmake
        NAMESPACE Qwt::
        DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}/cmake/Qwt")

    export(EXPORT ${PROJECT_NAME}-target
        FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-targets.cmake
        NAMESPACE Qwt::)

    include(CMakePackageConfigHelpers)
    set(INCLUDE_INSTALL_DIRS "${CMAKE_INSTALL_FULL_INCLUDEDIR}/Qwt")
    set(version_config "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake")
    set(project_config "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake")
    write_basic_package_version_file("${version_config}"
        VERSION ${QWT_VERSION}
        COMPATIBILITY SameMajorVersion)
    configure_package_config_file(${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in "${project_config}"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
        PATH_VARS INCLUDE_INSTALL_DIRS)
    install(FILES "${project_config}" "${version_config}"
        DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}/cmake/${PROJECT_NAME}")
endif()


#-----------------------------------------------------------------------------------------------------------------------
# Add subdirectory
#-----------------------------------------------------------------------------------------------------------------------
if(QWT_BUILD_EXAMPLES OR QWT_BUILD_ALL)
    add_subdirectory(examples)
endif()
if(QWT_BUILD_PLAYGROUND OR QWT_BUILD_ALL)
    add_subdirectory(playground)
endif()
message(STATUS "Qwt Configuring Generating Done")
