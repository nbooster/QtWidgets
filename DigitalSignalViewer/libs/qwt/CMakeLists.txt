cmake_minimum_required(VERSION 3.16)

project(Qwt
        LANGUAGES CXX
        VERSION 6.1.6)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

option(QWT_SUPPRESS_WARNINGS "Qwt: enable warnings suppression for whole qwt project" OFF)

if(QWT_SUPPRESS_WARNINGS)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        string(REPLACE "/W3" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W0")
    endif()
    message("Qwt: warnings suppressed")
endif()

find_package(Qt5 COMPONENTS
    Core
    Gui
    Widgets
    Svg
    PrintSupport
    Concurrent
    OpenGL
    REQUIRED)

set(QWT_HEADERS
    "src/qwt.h"
    "src/qwt_abstract_scale_draw.h"
    "src/qwt_clipper.h"
    "src/qwt_color_map.h"
    "src/qwt_compat.h"
    "src/qwt_column_symbol.h"
    "src/qwt_date.h"
    "src/qwt_date_scale_draw.h"
    "src/qwt_date_scale_engine.h"
    "src/qwt_dyngrid_layout.h"
    "src/qwt_global.h"
    "src/qwt_graphic.h"
    "src/qwt_interval.h"
    "src/qwt_interval_symbol.h"
    "src/qwt_math.h"
    "src/qwt_magnifier.h"
    "src/qwt_null_paintdevice.h"
    "src/qwt_painter.h"
    "src/qwt_painter_command.h"
    "src/qwt_panner.h"
    "src/qwt_picker.h"
    "src/qwt_picker_machine.h"
    "src/qwt_pixel_matrix.h"
    "src/qwt_point_3d.h"
    "src/qwt_point_polar.h"
    "src/qwt_round_scale_draw.h"
    "src/qwt_scale_div.h"
    "src/qwt_scale_draw.h"
    "src/qwt_scale_engine.h"
    "src/qwt_scale_map.h"
    "src/qwt_spline.h"
    "src/qwt_symbol.h"
    "src/qwt_system_clock.h"
    "src/qwt_text_engine.h"
    "src/qwt_text_label.h"
    "src/qwt_text.h"
    "src/qwt_transform.h"
    "src/qwt_widget_overlay.h"
    # QwtPlot
    "src/qwt_curve_fitter.h"
    "src/qwt_event_pattern.h"
    "src/qwt_abstract_legend.h"
    "src/qwt_legend.h"
    "src/qwt_legend_data.h"
    "src/qwt_legend_label.h"
    "src/qwt_plot.h"
    "src/qwt_plot_renderer.h"
    "src/qwt_plot_curve.h"
    "src/qwt_plot_dict.h"
    "src/qwt_plot_directpainter.h"
    "src/qwt_plot_grid.h"
    "src/qwt_plot_histogram.h"
    "src/qwt_plot_item.h"
    "src/qwt_plot_abstract_barchart.h"
    "src/qwt_plot_barchart.h"
    "src/qwt_plot_multi_barchart.h"
    "src/qwt_plot_intervalcurve.h"
    "src/qwt_plot_tradingcurve.h"
    "src/qwt_plot_layout.h"
    "src/qwt_plot_marker.h"
    "src/qwt_plot_zoneitem.h"
    "src/qwt_plot_textlabel.h"
    "src/qwt_plot_rasteritem.h"
    "src/qwt_plot_spectrogram.h"
    "src/qwt_plot_spectrocurve.h"
    "src/qwt_plot_scaleitem.h"
    "src/qwt_plot_legenditem.h"
    "src/qwt_plot_seriesitem.h"
    "src/qwt_plot_shapeitem.h"
    "src/qwt_plot_canvas.h"
    "src/qwt_plot_panner.h"
    "src/qwt_plot_picker.h"
    "src/qwt_plot_zoomer.h"
    "src/qwt_plot_magnifier.h"
    "src/qwt_plot_rescaler.h"
    "src/qwt_point_mapper.h"
    "src/qwt_raster_data.h"
    "src/qwt_matrix_raster_data.h"
    "src/qwt_sampling_thread.h"
    "src/qwt_samples.h"
    "src/qwt_series_data.h"
    "src/qwt_series_store.h"
    "src/qwt_point_data.h"
    "src/qwt_scale_widget.h"
    # OpenGL
    "src/qwt_plot_glcanvas.h"
    # QwtSvg
    "src/qwt_plot_svgitem.h"
    # QwtWidgets
    "src/qwt_abstract_slider.h"
    "src/qwt_abstract_scale.h"
    "src/qwt_arrow_button.h"
    "src/qwt_analog_clock.h"
    "src/qwt_compass.h"
    "src/qwt_compass_rose.h"
    "src/qwt_counter.h"
    "src/qwt_dial.h"
    "src/qwt_dial_needle.h"
    "src/qwt_knob.h"
    "src/qwt_slider.h"
    "src/qwt_thermo.h"
    "src/qwt_wheel.h"
    )
set(QWT_SOURCES
    "src/qwt_abstract_scale_draw.cpp"
    "src/qwt_clipper.cpp"
    "src/qwt_color_map.cpp"
    "src/qwt_column_symbol.cpp"
    "src/qwt_date.cpp"
    "src/qwt_date_scale_draw.cpp"
    "src/qwt_date_scale_engine.cpp"
    "src/qwt_dyngrid_layout.cpp"
    "src/qwt_event_pattern.cpp"
    "src/qwt_graphic.cpp"
    "src/qwt_interval.cpp"
    "src/qwt_interval_symbol.cpp"
    "src/qwt_math.cpp"
    "src/qwt_magnifier.cpp"
    "src/qwt_null_paintdevice.cpp"
    "src/qwt_painter.cpp"
    "src/qwt_painter_command.cpp"
    "src/qwt_panner.cpp"
    "src/qwt_picker.cpp"
    "src/qwt_picker_machine.cpp"
    "src/qwt_pixel_matrix.cpp"
    "src/qwt_point_3d.cpp"
    "src/qwt_point_polar.cpp"
    "src/qwt_round_scale_draw.cpp"
    "src/qwt_scale_div.cpp"
    "src/qwt_scale_draw.cpp"
    "src/qwt_scale_map.cpp"
    "src/qwt_spline.cpp"
    "src/qwt_scale_engine.cpp"
    "src/qwt_symbol.cpp"
    "src/qwt_system_clock.cpp"
    "src/qwt_text_engine.cpp"
    "src/qwt_text_label.cpp"
    "src/qwt_text.cpp"
    "src/qwt_transform.cpp"
    "src/qwt_widget_overlay.cpp"
    # QwtPlot
    "src/qwt_curve_fitter.cpp"
    "src/qwt_abstract_legend.cpp"
    "src/qwt_legend.cpp"
    "src/qwt_legend_data.cpp"
    "src/qwt_legend_label.cpp"
    "src/qwt_plot.cpp"
    "src/qwt_plot_renderer.cpp"
    "src/qwt_plot_xml.cpp"
    "src/qwt_plot_axis.cpp"
    "src/qwt_plot_curve.cpp"
    "src/qwt_plot_dict.cpp"
    "src/qwt_plot_directpainter.cpp"
    "src/qwt_plot_grid.cpp"
    "src/qwt_plot_histogram.cpp"
    "src/qwt_plot_item.cpp"
    "src/qwt_plot_abstract_barchart.cpp"
    "src/qwt_plot_barchart.cpp"
    "src/qwt_plot_multi_barchart.cpp"
    "src/qwt_plot_intervalcurve.cpp"
    "src/qwt_plot_zoneitem.cpp"
    "src/qwt_plot_tradingcurve.cpp"
    "src/qwt_plot_spectrogram.cpp"
    "src/qwt_plot_spectrocurve.cpp"
    "src/qwt_plot_scaleitem.cpp"
    "src/qwt_plot_legenditem.cpp"
    "src/qwt_plot_seriesitem.cpp"
    "src/qwt_plot_shapeitem.cpp"
    "src/qwt_plot_marker.cpp"
    "src/qwt_plot_textlabel.cpp"
    "src/qwt_plot_layout.cpp"
    "src/qwt_plot_canvas.cpp"
    "src/qwt_plot_panner.cpp"
    "src/qwt_plot_rasteritem.cpp"
    "src/qwt_plot_picker.cpp"
    "src/qwt_plot_zoomer.cpp"
    "src/qwt_plot_magnifier.cpp"
    "src/qwt_plot_rescaler.cpp"
    "src/qwt_point_mapper.cpp"
    "src/qwt_raster_data.cpp"
    "src/qwt_matrix_raster_data.cpp"
    "src/qwt_sampling_thread.cpp"
    "src/qwt_series_data.cpp"
    "src/qwt_point_data.cpp"
    "src/qwt_scale_widget.cpp"
    # OpenGL
    "src/qwt_plot_glcanvas.cpp"
    # QwtSvg
    "src/qwt_plot_svgitem.cpp"
    # QwtWidgets
    "src/qwt_abstract_slider.cpp"
    "src/qwt_abstract_scale.cpp"
    "src/qwt_arrow_button.cpp"
    "src/qwt_analog_clock.cpp"
    "src/qwt_compass.cpp"
    "src/qwt_compass_rose.cpp"
    "src/qwt_counter.cpp"
    "src/qwt_dial.cpp"
    "src/qwt_dial_needle.cpp"
    "src/qwt_knob.cpp"
    "src/qwt_slider.cpp"
    "src/qwt_thermo.cpp"
    "src/qwt_wheel.cpp"
    )

add_library(qwt SHARED
    ${QWT_HEADERS}
    ${QWT_SOURCES}
    )

add_library(Qwt::qwt ALIAS qwt)

set_target_properties(
    qwt PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 6
    )

# TODO: Temporary suppression of deprecated-declarations.
# Will be removed in the future when all obsolete methods are removed in qwt.
target_compile_definitions(qwt PRIVATE QT_NO_DEPRECATED_WARNINGS=1)

target_include_directories(qwt
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../qwt_no_warnings> # TODO: temporary. Will be removed in the future
)

target_link_libraries(qwt PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Svg
    Qt5::PrintSupport
    Qt5::OpenGL
    Qt5::Concurrent
)

target_compile_definitions(
    qwt
    PRIVATE
    QWT_MAKEDLL
    PUBLIC
    QWT_DLL
    )

# Installation
include(GNUInstallDirs)
set(QWT_INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/qwt)

install(TARGETS qwt
    EXPORT qwt-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT   qwt_Development
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT   qwt_Runtime
            NAMELINK_COMPONENT qwt_Development
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT   qwt_Runtime
)

# create config and version file for easier integration with external projects
# for prebuilt library
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_BINARY_DIR}/cmake/qwt-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/qwt-config.cmake.in
    ${CMAKE_BINARY_DIR}/cmake/qwt-config.cmake
    INSTALL_DESTINATION ${QWT_INSTALL_CONFIGDIR}
)

install(FILES ${QWT_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qwt
    COMPONENT   qwt_Development
)

install(
    FILES
        ${CMAKE_BINARY_DIR}/cmake/qwt-config.cmake
        ${CMAKE_BINARY_DIR}/cmake/qwt-config-version.cmake
    DESTINATION ${QWT_INSTALL_CONFIGDIR}
    COMPONENT   qwt_Development
)

install(EXPORT qwt-targets
    FILE qwt-targets.cmake
    NAMESPACE Qwt::
    DESTINATION ${QWT_INSTALL_CONFIGDIR}
)
export(EXPORT qwt-targets
    FILE ${CMAKE_BINARY_DIR}/cmake/qwt-targets.cmake
    NAMESPACE Qwt::
)

export(PACKAGE qwt)
