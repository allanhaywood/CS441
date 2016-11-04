#include "createacctpage.h"
#include "ui_createacctpage.h"
#include "mainwindow.h"
#include "accountmanager.h"
#include <QMessageBox>

CreateAcctPage::CreateAcctPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateAcctPage)
{
    ui->setupUi(this);//system generated to show box
    ui->incorrectPasswordLabel->hide();//hides the "incorrect password" field
    ui->PasswordBox1->setEchoMode(QLineEdit::Password);//hides password box entries
    ui->PasswordBox2->setEchoMode(QLineEdit::Password);//hides password box entries

    // set font for title
    QFont comixLoud("Comix Loud", 28, QFont::Normal, false);
    ui->CreateAcctHeader->setFont(comixLoud);
}

CreateAcctPage::~CreateAcctPage()
{

    delete ui;//when destroyed destroys
}

void CreateAcctPage::on_CreateAcctButton_clicked()
{
       QString firstName;
       QString lastName;
       QString handle;
       QString email;
       QString password;//strings to hold the info for account



       firstName=ui->FirstNameBox->text();
       lastName=ui->LastNameBox->text();
       handle=ui->handleBox->text();
       email=ui->emailBox->text();


       //AccountManager *addNew= AccountManager::getInstance();
       //if(addNew->createAccount(firstName,lastName,email,handle,password))


       //ui->LastNameBox->insertPlainText(firstName);//how to display a string in a box (probably works for a label too)
       //must check email to ensure it is not already used

       if(ui->PasswordBox1->text()==ui->PasswordBox2->text())//must also check to see if password matches requirements
       {
           password=ui->PasswordBox1->text();
           AccountManager *addNew= AccountManager::getInstance();
           if(addNew->createAccount(firstName,lastName,email,handle,password))
           {
               this->close();
               QMessageBox congrats;
               congrats.setText("Thank you for joining PlotTalk! "+firstName + "! \n Try out your new account by logging in!");
               congrats.exec();
               MainWindow *openAgain=new MainWindow();
               openAgain->show();
           }
           else
           {
               QMessageBox duplicateEmail;
               duplicateEmail.setText("That email address already exists in our system.\n Did you loose your password?");
               duplicateEmail.exec();
               ui->emailBox->clear();
           }

       }
       else
       {
           ui->incorrectPasswordLabel->show();
       }

}
