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
    accountdetails.cpp \
<<<<<<< HEAD
    accountmanager.cpp \
    accountcheckandstore.cpp
=======
    addnewmedia.cpp
>>>>>>> 214a5d689a6088c4f6a30398f645deb162d47dce

HEADERS  += mainwindow.h \
    createacctpage.h \
    dashboard.h \
    forgotpassword.h \
    accountdetails.h \
<<<<<<< HEAD
    accountmanager.h \
    accountcheckandstore.h
=======
    addnewmedia.h
>>>>>>> 214a5d689a6088c4f6a30398f645deb162d47dce

FORMS    += mainwindow.ui \
    createacctpage.ui \
    dashboard.ui \
    forgotpassword.ui \
    accountdetails.ui \
    addnewmedia.ui

DISTFILES += \
    creatingNewAcct.qmodel

