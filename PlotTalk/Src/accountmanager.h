#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QMainWindow>
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QList>
#include "person.h"




class AccountManager
{
private:
    static AccountManager* instance;//creates the static instance
    AccountManager();//constructor
    ~AccountManager();//destructor
    QList<Person> peopleList;//will be replaced by database manager
    Person thisGuy;

public:

    static AccountManager* getInstance();
    bool createAccount(QString &first, QString &last, QString &Email, QString &handle, QString &password);//done
    Person getCurrentAccount();//done
    bool findPersonByEmail(QString &emailtoCheck);//done
    bool findPersonByHandle(QString &handleToCheck);//done
    int checkFields(QString &fName, QString &lName, QString &handle, QString &email, QString &password);
};

#endif // ACCOUNTMANAGER_H
