#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "plottalkexceptions.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    int status;
    try {
        status = a.exec();
    } catch (PlotTalkException e) {
        QMessageBox exceptionBox;
        exceptionBox.setText("Unhandled exception in program:\n" + e.message);
        exceptionBox.exec();
    }

    return status;
}
