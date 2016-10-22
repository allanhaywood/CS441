#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QMainWindow>
#include <QWidget>
#include <QFile>
#include <QTextStream>

struct Person//a person element for passing around as needed (may need to be migrated to a different header file)
{
    QString firstName;
    QString lastName;
    QString email;
    QString handle;
    QString password;
};

class AccountManager
{
private:
    static AccountManager* instance;//creates the static instance
    AccountManager();//constructor
    ~AccountManager();//destructor


    QString fileName="Data.txt";
    Person ThisGuy;

public:

    static AccountManager* getInstance();
    bool createAccount(QString &first, QString &last, QString &email, QString &handle, QString &password);//done
    Person getCurrentAccount();//done


    bool findPersonByEmail(Person &PassBack, QString &emailtoCheck);//done
    bool findPersonByHandle(Person &PassBack, QString &handleToCheck);//done

};

#endif // ACCOUNTMANAGER_H
