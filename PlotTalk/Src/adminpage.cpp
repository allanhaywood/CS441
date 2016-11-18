#include "adminpage.h"
#include "ui_adminpage.h"
#include "databasemanager.h"
#include <QMessageBox>


AdminPage::AdminPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminPage)
{
    ui->setupUi(this);
}

AdminPage::~AdminPage()
{
    delete ui;
}


void AdminPage::on_Users_clicked()
{
     typedef Singleton<DatabaseManager> DatabaseManagerSingleton;
     QList<User> allUsers = DatabaseManagerSingleton::Instance().getAllUsers;

     for(int i = 0; i<allUsers.size(); i++)
     {
         allUsers[i].firstName;
         allUsers[i].lastName;

     }

}

void AdminPage::on_media_clicked()
{

}

void AdminPage::on_edit_clicked()
{

}
