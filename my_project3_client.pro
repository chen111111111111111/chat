#-------------------------------------------------
#
# Project created by QtCreator 2023-10-28T15:12:38
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = my_project3_client
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    all_dialog.cpp \
    chirld_dialog.cpp \
    chat_win.cpp \
    message_record.cpp \
    register_win.cpp

HEADERS += \
        mainwindow.h \
    all_dialog.h \
    chirld_dialog.h \
    chat_win.h \
    message_record.h \
    register_win.h

FORMS += \
        mainwindow.ui \
    all_dialog.ui \
    chirld_dialog.ui \
    chat_win.ui \
    message_record.ui \
    register_win.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pic.qrc


