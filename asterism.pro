#-------------------------------------------------
#
# Project created by QtCreator 2019-02-27T12:29:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = asterism
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++1z


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ref.jcln \
    test/f0.txt \
    test/f1.txt \
    test/f2.txt \
    test/rs.jcln

HEADERS += \
    clone_format/ccfindersw.hpp \
    clone_format/clone_io.hpp \
    clone_format/csv.hpp \
    clone_format/format_tags.hpp \
    clone_format/jcln.hpp \
    clone_format/json.hpp \
    clone_format/nicad.hpp \
    core/bk.hpp \
    core/detection_results.hpp \
    core/logger.hpp \
    core/matching_table.hpp \
    core/utility.hpp \
    gui/central.hpp \
    gui/central/color_bar_widget.hpp \
    gui/central/current_grid_detail_widget.hpp \
    gui/central/layer_widget.hpp \
    gui/central/matched_clone_pair_list_widget.hpp \
    gui/central/scatter_plot_widget.hpp \
    gui/docks.hpp \
    gui/docks/layer_detail_widget.hpp \
    gui/docks/layer_list_widget.hpp \
    gui/mainwindow.hpp \
    gui/tools.hpp \
    gui/tools/external_tools_settings_dialog.hpp \
    gui/tools/invoke_clone_detector_dialog.hpp \
    layer/clone_pair_grid_layer.hpp \
    layer/color_selector.hpp \
    layer/file_separated_grid_layer.hpp \
    layer/heatmap_layer.hpp \
    model/clone_pair.hpp \
    model/detection_result.hpp \
    model/file.hpp \
    model/fragment.hpp \
    model/object_id_t.hpp \
    model/result_environment.hpp

SOURCES += \
    clone_format/ccfindersw.cpp \
    clone_format/clone_io.cpp \
    clone_format/csv.cpp \
    clone_format/jcln.cpp \
    clone_format/nicad.cpp \
    core/bk.cpp \
    core/detection_results.cpp \
    core/logger.cpp \
    core/matching_table.cpp \
    core/utility.cpp \
    gui/central/color_bar_widget.cpp \
    gui/central/current_grid_detail_widget.cpp \
    gui/central/layer_widget.cpp \
    gui/central/matched_clone_pair_list_widget.cpp \
    gui/central/scatter_plot_widget.cpp \
    gui/docks/layer_detail_widget.cpp \
    gui/docks/layer_list_widget.cpp \
    gui/mainwindow.cpp \
    gui/tools/external_tools_settings_dialog.cpp \
    gui/tools/invoke_clone_detector_dialog.cpp \
    layer/clone_pair_grid_layer.cpp \
    layer/color_selector.cpp \
    layer/file_separated_grid_layer.cpp \
    layer/heatmap_layer.cpp \
    main.cpp \
    model/clone_pair.cpp \
    model/detection_result.cpp \
    model/file.cpp \
    model/fragment.cpp \
    model/result_environment.cpp
