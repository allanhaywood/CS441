######################################################################
# Automatically generated by qmake (3.0) Mon Oct 17 14:15:44 2016
######################################################################
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = PlotTalk
#INCLUDEPATH += .

HEADERS += \
    Src/mainwindow.h \
    Src/tvshow.h

SOURCES += \
    Src/main.cpp \
    Src/mainwindow.cpp \
    Src/tvshow.cpp \
           
FORMS += \
    Src/mainwindow.ui

test {
    message(Test build)

    QT += testlib
    TARGET = PlotTalkTest

    SOURCES -= Src/main.cpp

    HEADERS += \
        Test/testtvshow.h

    SOURCES += \
        Test/testmain.cpp \
        Test/testtvshow.cpp
} else {
    message(Normal build)
}
