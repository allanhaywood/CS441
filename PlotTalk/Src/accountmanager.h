#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QMainWindow>
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QList>

#include "databasemanager.h"
#include "user.h"




class AccountManager
{
private:
    static AccountManager* instance;//creates the static instance
    AccountManager();//constructor
    ~AccountManager();//destructor
    //QList<Person> peopleList;//will be replaced by database manager
    User thisGuy;

public:

    static AccountManager* getInstance();
    bool createAccount(QString &first, QString &last, QString &Email, QString &handle, QString &password);//done
    User getCurrentAccount();//done
    bool findPersonByEmail(QString &emailtoCheck, DatabaseManager database);//done
    bool findPersonByHandle(QString &handleToCheck, DatabaseManager database);//done
    int checkFields(QString &fName, QString &lName, QString &handle, QString &email, QString &password);
};

#endif // ACCOUNTMANAGER_H
