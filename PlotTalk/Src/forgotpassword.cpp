#include "forgotpassword.h"
#include "ui_forgotpassword.h"
#include "mainwindow.h"

ForgotPassword::ForgotPassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForgotPassword)
{
    ui->setupUi(this);
}

ForgotPassword::~ForgotPassword()
{
    delete ui;
}

void ForgotPassword::on_PassResetButton_clicked()
{
    // TODO: Check if the username or email entered is valid
    bool emailValid = true; // hardcoded to true for now

    if (emailValid)
    {
        ui->ResetPassOutputLabel->setText("The reset password has been emailed to you.");
        // TODO: Create functionality to email the password to the user.
        ui->UsernameInput->clear();
    }
    else
    {
        ui->ResetPassOutputLabel->setText("Enter a valid username or email.");
        ui->UsernameInput->clear(); // clear out username/password field to try again
    }
}

void ForgotPassword::on_BackButton_clicked()
{
    MainWindow* newLogin = new MainWindow();
    newLogin->show();
    this->close();
}
