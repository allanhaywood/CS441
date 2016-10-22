#ifndef CREATEACCTPAGE_C
#define CREATEACCTPAGE_C

#include "createacctpage.h"
#include "ui_createacctpage.h"
#include "mainwindow.h"
#include "accountmanager.h"

const int SIZE=6;//minimum password length

CreateAcctPage::CreateAcctPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateAcctPage)
{
    ui->setupUi(this);//system generated to show box
    ui->incorrectPasswordLabel->hide();//hides the "incorrect password" field
    ui->pwdMatch->hide();//hides the passwords match field
    ui->PasswordBox1->setEchoMode(QLineEdit::Password);//hides password box entries
    ui->PasswordBox2->setEchoMode(QLineEdit::Password);//hides password box entries
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

       if(ui->PasswordBox1->text()==ui->PasswordBox2->text())//must also check to see if password matches requirements
       {
         Person hold;

         password=ui->PasswordBox1->text();//the password in a string
         if(password.size()>=SIZE)
         {
           AccountManager *addNew= AccountManager::getInstance();
           if(!addNew->findPersonByEmail(hold,email))
           {
               if(!addNew->findPersonByHandle(hold,handle))
               {
                   if(email.contains('@')&&email.contains('.'))
                   {
                        addNew->createAccount(firstName,lastName,email,handle,password);
                        this->close();
                        QMessageBox congrats;
                        congrats.setText("Thank you for joining PlotTalk! "+firstName + "! \n Try out your new account by logging in!");
                        congrats.exec();
                        MainWindow *openAgain=new MainWindow();
                        openAgain->show();
                   }
                   else
                   {
                        QMessageBox badEmail;
                        badEmail.setText(("The email format is not correct"));
                        badEmail.exec();
                   }
               }
               else
               {
                   QMessageBox badHandle;
                   badHandle.setText("That handle is already chosen, please try another");
                   badHandle.exec();
                   ui->handleBox->clear();
               }
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
             QMessageBox InvalidPwd;
             InvalidPwd.setText("The password must be more than 6 characters");
             InvalidPwd.exec();
             ui->PasswordBox1->clear();
             ui->PasswordBox2->clear();
         }

       }
       else
       {
           ui->incorrectPasswordLabel->show();
       }

}

#endif

void CreateAcctPage::on_PasswordBox2_textChanged(const QString &arg1)
{
    QString why=arg1;
    QString password=ui->PasswordBox1->text();
    if(password.size()>=SIZE)
    {
        if(ui->PasswordBox1->text()==ui->PasswordBox2->text())
        {
             ui->pwdMatch->show();
        }
        else
        {
             ui->pwdMatch->hide();
        }
    }
}
