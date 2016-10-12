#include "createacctpage.h"
#include "ui_createacctpage.h"
#include "mainwindow.h"
#include <QMessageBox>

CreateAcctPage::CreateAcctPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateAcctPage)
{
    ui->setupUi(this);
    ui->incorrectPasswordLabel->hide();
    ui->PasswordBox1->setEchoMode(QLineEdit::Password);
    ui->PasswordBox2->setEchoMode(QLineEdit::Password);
}

CreateAcctPage::~CreateAcctPage()
{

    delete ui;
}

void CreateAcctPage::on_CreateAcctButton_clicked()
{
       QString firstName;
       QString lastName;
       QString handle;
       QString email;
       QString password;



       firstName=ui->FirstNameBox->toPlainText();
       lastName=ui->LastNameBox->toPlainText();
       handle=ui->handleBox->toPlainText();
       email=ui->emailBox->toPlainText();


       ui->LastNameBox->insertPlainText(firstName);//how to display a string in a box (probably works for a label too)
       //must check email to ensure it is not already used

       if(ui->PasswordBox1->text()==ui->PasswordBox2->text())//must also check to see if password matches requirements
       {
           password=ui->PasswordBox1->text();
           this->close();
           QMessageBox congrats;
           congrats.setText("Thank you for joining PlotTalk! "+firstName + "! \n Try out your new account by logging in!");
           congrats.exec();
           MainWindow *openAgain=new MainWindow();
           openAgain->show();

       }
       else
       {
           ui->incorrectPasswordLabel->show();
       }

}
