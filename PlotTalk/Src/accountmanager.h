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
    bool createAccount(QString &first, QString &last, QString &email, QString &handle, QString &password);//done
    Person getCurrentAccount();//done
    bool findPersonByEmail(Person &PassBack, QString &emailtoCheck);//done
    bool findPersonByHandle(Person &PassBack, QString &handleToCheck);//done

};

#endif // ACCOUNTMANAGER_H
