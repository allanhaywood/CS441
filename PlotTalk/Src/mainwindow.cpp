#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createacctpage.h"
#include "dashboard.h"
#include "forgotpassword.h"
#include "databasemanager.h"
#include "user.h"
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
    QString password=ui->PasswordEnter->toPlainText();
    QString email=ui->EmailEnter->toPlainText();

/*
   DatabaseManager access;
    try
    {
   User client=access.HaveYouSignedUpYet?------------------------needs to be created
*/
    Dashboard *dash = new Dashboard();
    dash->setWindowState(Qt::WindowMaximized);
    dash->show();
    this->close();
/*
}
    catch//the user doesn't exist-------------------------------------throws an error
    {

    }
    */
}

void MainWindow::on_ForgotPassButton_clicked()
{
    ForgotPassword *forgotPass = new ForgotPassword();
    forgotPass->show();
    this->close();
}
