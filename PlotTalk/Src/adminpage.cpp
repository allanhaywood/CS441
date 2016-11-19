#include "adminpage.h"
#include "ui_adminpage.h"
#include "databasemanager.h"
#include "accountmanager.h"
#include <QMessageBox>


AdminPage::AdminPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminPage)
{
    ui->setupUi(this);
    ui->Options->hide();
}

AdminPage::~AdminPage()
{
    delete ui;
}


void AdminPage::on_Users_clicked()
{
    ui->Options->show();
    ui->Options->setCurrentIndex(VIEWUSERS);
    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;
     QList<User> allUsers = DatabaseManagerSingleton::Instance().getAllUsers();

     ui->UserList->addItem("First\tLast\tEmail\t\tHandle");
     QString UserString;
     for(int i = 0; i<allUsers.size(); i++)
     {
         UserString.append(allUsers[i].firstName);
         UserString.append("\t");
         UserString.append(allUsers[i].lastName);
         UserString.append("\t");
         UserString.append(allUsers[i].email);
         UserString.append("\t");
         UserString.append(allUsers[i].username);

         ui->UserList->addItem(UserString);
     }



}

void AdminPage::on_media_clicked()
{

}

void AdminPage::on_edit_clicked()
{

}

void AdminPage::on_GoBack_clicked()
{
    ui->UserList->clear();
    ui->Options->hide();
}

void AdminPage::on_addUser_clicked()
{
    ui->Options->show();
    ui->Options->setCurrentIndex(ADDUSER);
}

void AdminPage::on_CreateUser_clicked()
{
  AccountManager *addingUser= AccountManager::getInstance();
  User holdAdmin=addingUser->getCurrentAccount();


  selectEnum Choice= addingUser->checkFieldsAndCreate(ui->FirstNameBox->text(),ui->LastNameBox->text(),ui->handleBox->text(),ui->emailBox->text(),ui->PasswordBox1->text());
  switch(Choice)
  {
  case selectEnum::ALLCLEAR:
  {
      QMessageBox UserCreated;
      UserCreated.setText("The account was created successfully");
      UserCreated.exec();
      addingUser->checkEmailAndPassword(holdAdmin.email, holdAdmin.passwordHash, holdAdmin);//returns account manager to Admin account settings
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
      badHandle.setText("That handle is already chosen");
      badHandle.exec();
  }
      break;

  case selectEnum::DUPLICATE_EMAIL:
  {
      QMessageBox duplicateEmail;
      duplicateEmail.setText("That email address already exists");
      duplicateEmail.exec();
  }
      break;

  case selectEnum::BAD_PASSWORD:
  {
        QMessageBox::StandardButton InvalidPwd;
        InvalidPwd = QMessageBox::question(this, "","The password does not meet security critera, override?",QMessageBox::Yes|QMessageBox::No);
        if (InvalidPwd == QMessageBox::Yes)
        {
          addingUser->createAccount(ui->FirstNameBox->text(),ui->LastNameBox->text(),ui->handleBox->text(),ui->emailBox->text(),ui->PasswordBox1->text());
          QMessageBox UserCreated;
          UserCreated.setText("The account was created successfully");
          UserCreated.exec();
        }
  }
      break;

  case selectEnum::VALUES_MISSING:
  {
      QMessageBox::StandardButton MissingVals;
      MissingVals = QMessageBox::question(this, "","There are values missing, override?",QMessageBox::Yes|QMessageBox::No);
      if (MissingVals == QMessageBox::Yes)
      {
        addingUser->createAccount(ui->FirstNameBox->text(),ui->LastNameBox->text(),ui->handleBox->text(),ui->emailBox->text(),ui->PasswordBox1->text());
        QMessageBox UserCreated;
        UserCreated.setText("The account was created successfully");
        UserCreated.exec();
      }
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

void AdminPage::on_goBack2_clicked()
{
    ui->FirstNameBox->clear();
    ui->LastNameBox->clear();
    ui->emailBox->clear();
    ui->PasswordBox1->clear();
    ui->handleBox->clear();

    ui->Options->hide();
}
