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

       int num=0;
       firstName=ui->FirstNameBox->text();
       lastName=ui->LastNameBox->text();
       handle=ui->handleBox->text();
       email=ui->emailBox->text();
       password=ui->PasswordBox1->text();

       AccountManager *check= AccountManager::getInstance();
       if(ui->PasswordBox1->text()==ui->PasswordBox2->text())//must also check to see if password matches requirements
       {
           switch(check->checkFields(firstName, lastName, handle, email, password))
           {
           case 1:
           {

               this->close();
               QMessageBox congrats;
               congrats.setText("Thank you for joining PlotTalk! "+firstName + "! \n Try out your new account by logging in!");
               congrats.exec();
               MainWindow *openAgain=new MainWindow();
               openAgain->show();
           }
               break;

           case 2:
           {
               QMessageBox badEmail;
               badEmail.setText(("The email format is not correct"));
               badEmail.exec();
           }
               break;

           case 3:
           {
               QMessageBox badHandle;
               badHandle.setText("That handle is already chosen, please try another");
               badHandle.exec();
               ui->handleBox->clear();
           }
               break;

           case 4:
           {
               QMessageBox duplicateEmail;
               duplicateEmail.setText("That email address already exists in our system.\n Did you loose your password?");
               duplicateEmail.exec();
               ui->emailBox->clear();
           }
               break;

           case 5:
           {
               QMessageBox InvalidPwd;
               InvalidPwd.setText("The password must have the following characteristics:\nIt must be more than 6 characters\nIt must not contain a space\nIt must contain both capital and lowercase letters\nIt must include at least one special symbol");
               InvalidPwd.exec();
               ui->PasswordBox1->clear();
               ui->PasswordBox2->clear();
               ui->pwdMatch->hide();
           }
               break;

           case 6:
           {
               QMessageBox BadName;
               BadName.setText("You must provide a first and last name.");
               BadName.exec();
           }
               break;

           default:
           {
               QMessageBox Something;
               Something.setText("You should never see this message");
               Something.exec();
           }
               break;

           }
       }
       else
       {
       ui->incorrectPasswordLabel->show();
       }

}

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
