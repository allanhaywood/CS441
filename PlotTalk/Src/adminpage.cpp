#include "adminpage.h"
#include "ui_adminpage.h"
#include "databasemanager.h"
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
    ui->Options->setCurrentIndex(USERS);
    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;
     QList<User> allUsers = DatabaseManagerSingleton::Instance().getAllUsers();

     ui->UserList->addItem("First\tLast\tEmail\tHandle");
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
