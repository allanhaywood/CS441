#include "adminpage.h"
#include "ui_adminpage.h"
#include "accountmanager.h"
#include <QMessageBox>


AdminPage::AdminPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminPage)
{
    ui->setupUi(this);
    ui->Options->hide();
    ui->UserList->setSelectionMode(QAbstractItemView::ExtendedSelection);//allows more than one object to be selected in this list
}

AdminPage::~AdminPage()
{
    delete ui;
}


void AdminPage::on_Users_clicked()
{
     ui->Options->show();
     ui->Options->setCurrentIndex(VIEWUSERS);
     ui->UserList->clear();//opens up the box showing all users

     QList<QString> allUserNames = DatabaseManagerSingleton::Instance().getListOfAllUsers();//gets lists of all usernames

     QList<User> allUsers=QList<User>();//generates a new list of Users

     for(int i=0; i<allUserNames.size(); i++)
     {
        allUsers.append(DatabaseManagerSingleton::Instance().inspectUser(allUserNames[i]));
     }//populates a list of users from the usernames

     ui->UserList->addItem("First\tLast\tEmail\t\tHandle");
     QString UserString;
     for(int i = 0; i<allUsers.size(); i++)//genrates a string to put in the listbox
     {
         UserString.append(allUsers[i].firstName);
         UserString.append("\t");
         UserString.append(allUsers[i].lastName);
         UserString.append("\t");
         UserString.append(allUsers[i].email);
         UserString.append("\t");
         UserString.append(allUsers[i].username);

         ui->UserList->addItem(UserString);
         UserString="";//resets the string to blank for the next string to populate
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
    ui->UserList->clear();//clears the UserLists and hides the options object
    ui->Options->hide();
}

void AdminPage::on_addUser_clicked()
{
    ui->Options->show();//navigates to the addUsers page
    ui->Options->setCurrentIndex(ADDUSER);
}

void AdminPage::on_CreateUser_clicked()
{
  AccountManager *addingUser= AccountManager::getInstance();


  User holdAdmin=addingUser->getCurrentAccount();
  User newUser = User(ui->handleBox->text(),ui->FirstNameBox->text(),ui->LastNameBox->text(),ui->emailBox->text(),ui->PasswordBox1->text(), ui->AdminButton->isChecked());

  selectEnum Choice = addingUser->checkFieldsAndCreate(newUser);
  switch(Choice)//attempts to create the user from the values supplied in the boxes on the UI
  {
  case selectEnum::ALLCLEAR://creates the user
  {
      QMessageBox UserCreated;
      UserCreated.setText("The account was created successfully");
      UserCreated.exec();
      addingUser->checkEmailAndPassword(holdAdmin.email, holdAdmin.passwordHash, holdAdmin);//returns account manager to Admin account settings
  }
      break;

  case selectEnum::BAD_EMAIL://bad email format
  {
      QMessageBox badEmail;
      badEmail.setText(("The email format is not correct"));
      badEmail.exec();
  }
      break;

  case selectEnum::USERNAME_TAKEN://duplicate username
  {
      QMessageBox badHandle;
      badHandle.setText("That handle is already chosen");
      badHandle.exec();
  }
      break;

  case selectEnum::DUPLICATE_EMAIL://duplicate email
  {
      QMessageBox duplicateEmail;
      duplicateEmail.setText("That email address already exists");
      duplicateEmail.exec();
  }
      break;

  case selectEnum::BAD_PASSWORD://bad password, option to override this criteria
  {
        QMessageBox::StandardButton InvalidPwd;
        InvalidPwd = QMessageBox::question(this, "","The password does not meet security critera, override?",QMessageBox::Yes|QMessageBox::No);
        if (InvalidPwd == QMessageBox::Yes)
        {
          addingUser->createAccount(newUser);
          QMessageBox UserCreated;
          UserCreated.setText("The account was created successfully");
          UserCreated.exec();
          addingUser->checkEmailAndPassword(holdAdmin.email, holdAdmin.passwordHash, holdAdmin);//returns account manager to Admin account settings
        }
  }
      break;

  case selectEnum::VALUES_MISSING://name fields may be missing, options to overide
  {
      QMessageBox::StandardButton MissingVals;
      MissingVals = QMessageBox::question(this, "","There are values missing, override?",QMessageBox::Yes|QMessageBox::No);
      if (MissingVals == QMessageBox::Yes)
      {
        addingUser->createAccount(newUser);
        QMessageBox UserCreated;
        UserCreated.setText("The account was created successfully");
        UserCreated.exec();
        addingUser->checkEmailAndPassword(holdAdmin.email, holdAdmin.passwordHash, holdAdmin);//returns account manager to Admin account settings
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

void AdminPage::on_delUser_clicked()//parses vector and string and removes username from the admin selected list
{
   QList<QListWidgetItem *> toDelete = ui->UserList->selectedItems();//gets a list of the entries that are selected by the user

    int count;
    bool EmailExtracted=false;
    QString userName;
    QString hold;

    for(int i=0; i<toDelete.size(); i++)
    {
        count=TABSBEFOREUSERNAME;//how many tabs are present before the username is found
        hold = toDelete[i]->text();
        EmailExtracted=false;

        for(int j=0; ((j<hold.size()) && (EmailExtracted!=true)); j++)//removes username letter by letter
        {
           if(count==0&&hold[j]=='\t')
           {
               EmailExtracted=true;
           }
           else if(count==0&&hold[j]!='\t')
           {
               userName.append(hold[j]);
           }

           else if(hold[j]=='\t')
           {
               count--;
           }
        }

        DatabaseManagerSingleton::Instance().removeUser(userName);
        userName="";//removes the user and the userName string to blank for the next string if needed
    }
}

