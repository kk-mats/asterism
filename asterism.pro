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

HEADERS += \
    clone_format/format_tags.hpp \
    clone_format/jcln.hpp \
    core/logger.hpp \
    core/utility.hpp \
    gui/mainwindow.hpp \
    layer/clone_pair_grid_layer.hpp \
    layer/file_separated_grid_layer.hpp \
    model/clone_pair.hpp \
    model/detection_result.hpp \
    model/file.hpp \
    model/fragment.hpp \
    model/object_id_t.hpp \
    model/result_environment.hpp \
    gui/scatter_plot_view.hpp \
    gui/scatter_plot_model.hpp \
    layer/heatmap_layer.hpp \
    gui/color_selector.hpp \
    clone_format/clone_io.hpp \
    core/results_operator.hpp \
    core/matching_table.hpp

SOURCES += \
    clone_format/jcln.cpp \
    core/logger.cpp \
    core/utility.cpp \
    gui/mainwindow.cpp \
    layer/clone_pair_grid_layer.cpp \
    layer/file_separated_grid_layer.cpp \
    model/clone_pair.cpp \
    model/detection_result.cpp \
    model/file.cpp \
    model/fragment.cpp \
    model/result_environment.cpp \
    main.cpp \
    gui/scatter_plot_view.cpp \
    gui/scatter_plot_model.cpp \
    layer/heatmap_layer.cpp \
    gui/color_selector.cpp \
    clone_format/clone_io.cpp \
    core/results_operator.cpp \
    core/matching_table.cpp
