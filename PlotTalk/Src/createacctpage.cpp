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
    QRegularExpression checkEmail("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+.[a-zA-Z]{2,4}");
    QRegularExpression checkPassword("(?=^.{6,10}$)(?=.*\\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[!@#$%^&amp;*()_+}{&quot;:;'?/&gt;.&lt;,])(?!.*s).*$");//patterntitle retrived from http://regexlib.com/Search.aspx?k=password&c=-1&m=5&ps=20


       /*

This regular expression match can be used for validating strong password.
It expects atleast 1 small-case letter, 1 Capital letter, 1 digit,
1 special character and the length should be between 6-10 characters.
The sequence of the characters is not important. This expression follows the
above 4 norms specified by microsoft for a strong password.
//(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=.*[!@#$%^&amp;*()_+}{&quot;:;'?&gt;.&lt;,])(?!.*\s).*$

*/

       QString firstName;
       QString lastName;
       QString handle;
       QString email;
       QString password;//strings to hold the info for account

       QValidator *validEmail=new QRegularExpressionValidator(checkEmail, 0);
       QValidator *validPwd = new QRegularExpressionValidator(checkPassword,0);

       int num=0;
       firstName=ui->FirstNameBox->text();
       lastName=ui->LastNameBox->text();
       handle=ui->handleBox->text();
       email=ui->emailBox->text();
       password=ui->PasswordBox1->text();

       if((ui->PasswordBox1->text()==ui->PasswordBox2->text()) && (validPwd->validate(password,num)==2))//must also check to see if password matches requirements
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
                   if(validEmail->validate(email,num)==2) //email.contains('@')&&email.contains('.'))
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
           if(!(validPwd->validate(password,num)==2))
           {
               QMessageBox InvalidPwd2;
               InvalidPwd2.setText("Incorrect Password Format");
               InvalidPwd2.exec();
               ui->PasswordBox1->clear();
               ui->PasswordBox2->clear();
           }
           else
           {
           ui->incorrectPasswordLabel->show();  
           }
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
