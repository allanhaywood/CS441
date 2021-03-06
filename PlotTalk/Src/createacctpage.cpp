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
       password=ui->PasswordBox1->text();


         // enum select {ALLCLEAR, BAD_EMAIL, DUPLICATE_EMAIL, BAD_USERNAME, USERNAME_TAKEN, VALUES_MISSING};
       AccountManager *check= AccountManager::getInstance();
       if(ui->PasswordBox1->text()==ui->PasswordBox2->text())//must also check to see if password matches requirements
       {
           User createdUser = User(handle, firstName, lastName, email, password, false);
           //QString message; //To do what was done on dashboard.
           switch(check->checkFieldsAndCreate(createdUser))
           {
           case selectEnum::ALLCLEAR:
           {
               this->close();
               QMessageBox congrats;
               congrats.setText("Thank you for joining PlotTalk! "+firstName + "! \n Try out your new account by logging in!");
               congrats.exec();
               MainWindow *openAgain=new MainWindow();
               openAgain->show();
           }
               break;

           case selectEnum::BAD_EMAIL:
           {
               QMessageBox badEmail;
               badEmail.setText(("The email format is not correct"));
               badEmail.exec();
           }
               break;

           case selectEnum::USERNAME_TAKEN:
           {
               QMessageBox badHandle;
               badHandle.setText("That handle is already chosen, please try another");
               badHandle.exec();
               ui->handleBox->clear();
           }
               break;

           case selectEnum::DUPLICATE_EMAIL:
           {
               QMessageBox duplicateEmail;
               duplicateEmail.setText("That email address already exists in our system.\n Did you loose your password?");
               duplicateEmail.exec();
               ui->emailBox->clear();
           }
               break;

           case selectEnum::BAD_PASSWORD:
           {
               QMessageBox InvalidPwd;
               InvalidPwd.setText("The password must have the following characteristics:\nIt must be more than 8 characters\nIt must contain both capital and lowercase letters\nIt must include at least one special symbol");
               InvalidPwd.exec();
               ui->PasswordBox1->clear();
               ui->PasswordBox2->clear();
               ui->pwdMatch->hide();
           }
               break;

           case selectEnum::VALUES_MISSING:
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

void CreateAcctPage::on_PasswordBox2_textChanged()
{
    ui->incorrectPasswordLabel->hide();
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

void CreateAcctPage::on_GoBack_clicked()
{
    this->close();
    MainWindow *openAgain=new MainWindow();
    openAgain->show();
}
