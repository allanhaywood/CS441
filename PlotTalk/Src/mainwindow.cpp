#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createacctpage.h"
#include "dashboard.h"
#include "forgotpassword.h"
#include "accountmanager.h"
#include "user.h"
#include <string>
#include <vector>
#include <QFont>
#include <QFontDatabase>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setting up Fonts
    int fontId1 = QFontDatabase::addApplicationFont(":/fonts/Fonts/Bikinis_Personal_Use.ttf");
    if (fontId1 == -1)
    {
        qDebug() << "Could not load first font file.";
    }
    int fontId2 = QFontDatabase::addApplicationFont(":/fonts/Fonts/Comix_Loud.ttf");
    if (fontId2 == -1)
    {
        qDebug() << "Could not load second font file.";
    }

    QFont comixLoud("Comix Loud", 28, QFont::Normal, false);
    ui->LoginTitle->setFont(comixLoud);

    QFont bikinis("Bikinis Personal Use", 16, QFont::Normal, false);
    ui->LoginTag->setFont(bikinis);
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
    QString password=ui->PasswordEnter->text();
    QString email=ui->EmailEnter->text();

    User toPass;
    AccountManager *account= AccountManager::getInstance();

    if(account->checkEmailAndPassword(email,password,toPass))
    {
        Dashboard *dash = new Dashboard();//needs to accept user object
        dash->setWindowState(Qt::WindowMaximized);

        bool isAdmin = account->getCurrentAccount().isAdmin();

        // If the account is not an admin, hide the admin button.
        if (! isAdmin)
        {
            qDebug() << "Hiding admin button.";
            dash->hideAdminButton();
        }
        else
        {
            qDebug() << "Not hiding admin button.";
        }

        dash->show();
        this->close();
    }
    else
    {
        QMessageBox incorrect;
        incorrect.setText("Incorrect email or password");
        incorrect.exec();
        ui->PasswordEnter->clear();
    }
}

void MainWindow::on_ForgotPassButton_clicked()
{
    ForgotPassword *forgotPass = new ForgotPassword();
    forgotPass->show();
    this->close();
}
