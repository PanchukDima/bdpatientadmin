#-------------------------------------------------
#
# Project created by QtCreator 2015-10-19T18:13:58
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BDPatientAdmin
TEMPLATE = app
CONFIG += CONSOLE

SOURCES += main.cpp\
        mainwindow.cpp \
    dialog_login.cpp \
    dialog_control_user.cpp \
    dialog_delete_user.cpp \
    dialog_control_user_right.cpp \
    dialog_delete_user_right.cpp \
    dialog_view_tasks.cpp

HEADERS  += mainwindow.h \
    dialog_login.h \
    dialog_control_user.h \
    dialog_delete_user.h \
    dialog_control_user_right.h \
    dialog_delete_user_right.h \
    dialog_view_tasks.h

FORMS    += mainwindow.ui \
    dialog_login.ui \
    dialog_control_user.ui \
    dialog_delete_user.ui \
    dialog_control_user_right.ui \
    dialog_delete_user_right.ui \
    dialog_view_tasks.ui
