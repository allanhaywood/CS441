#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_CreateAcctButton_clicked();

    void on_SignInButton_clicked();

    void on_ForgotPassButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
