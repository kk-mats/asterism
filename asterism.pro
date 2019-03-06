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

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    model/clone_pair.cpp \
    model/fragment.cpp \
    main.cpp \
    mainwindow.cpp \
    model/clone_pair.cpp \
    model/fragment.cpp \
    main.cpp \
    mainwindow.cpp \
    model/clone_pair.cpp \
    model/fragment.cpp \
    main.cpp \
    mainwindow.cpp \
    layer/file_separated_grid_layer.cpp \
    model/result_context.cpp \
    model/detection_result.cpp \
    model/file.cpp \
    reader/jcln.cpp \
    clone_format/jcln.cpp \
    layer/file_separated_grid_layer.cpp \
    model/clone_pair.cpp \
    model/detection_result.cpp \
    model/file.cpp \
    model/fragment.cpp \
    model/result_context.cpp \
    main.cpp \
    mainwindow.cpp \
    core/utility.cpp \
    layer/clone_pair_grid_layer.cpp \
    core/log.cpp

HEADERS += \
        mainwindow.hpp \
    model/clone_pair.hpp \
    model/fragment.hpp \
    mainwindow.hpp \
    model/clone_pair.hpp \
    model/fragment.hpp \
    mainwindow.hpp \
    model/clone_pair.hpp \
    model/fragment.hpp \
    mainwindow.hpp \
    model/result_context.hpp \
    layer/file_separated_grid_layer.hpp \
    model/object_id_t.hpp \
    model/detection_result.hpp \
    model/file.hpp \
    reader/jcln.hpp \
    clone_format/jcln.hpp \
    layer/file_separated_grid_layer.hpp \
    model/clone_pair.hpp \
    model/detection_result.hpp \
    model/file.hpp \
    model/fragment.hpp \
    model/object_id_t.hpp \
    model/result_context.hpp \
    mainwindow.hpp \
    core/utility.hpp \
    layer/clone_pair_grid_layer.hpp \
    core/log.hpp

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
