#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createacctpage.h"
#include "dashboard.h"
#include "forgotpassword.h"
#include <string>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_CreateAcctButton_clicked()
{
    CreateAcctPage *creatingAcct =new CreateAcctPage();//creates a pointer for the create account page
    creatingAcct->show();//shows that page
    this->close();//closes the mainWindow to avoid confusion
}

void MainWindow::on_SignInButton_clicked()
{
    //TODO: add authentication logic
    Dashboard *dash = new Dashboard();
    dash->setWindowState(Qt::WindowMaximized);
    dash->show();
    this->close();
}

void MainWindow::on_ForgotPassButton_clicked()
{
    ForgotPassword *forgotPass = new ForgotPassword();
    forgotPass->show();
    this->close();
}
