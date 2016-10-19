#-------------------------------------------------
#
# Project created by QtCreator 2016-09-19T12:22:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    createacctpage.cpp \
    dashboard.cpp \
    forgotpassword.cpp \
    accountmanager.cpp \
    addnewmedia.cpp\


HEADERS  += mainwindow.h \
    createacctpage.h \
    dashboard.h \
    forgotpassword.h \
    accountmanager.h \
    addnewmedia.h\


FORMS    += mainwindow.ui \
    createacctpage.ui \
    dashboard.ui \
    forgotpassword.ui \
    addnewmedia.ui\

DISTFILES += \
    creatingNewAcct.qmodel

