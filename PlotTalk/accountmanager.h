#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QMainWindow>
#include <QWidget>
#include <QFile>
#include <QTextStream>

struct Person
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
    static AccountManager* instance;
    AccountManager();
    ~AccountManager();

    bool checkEmail(QString &emailToCheck);
    bool checkHandle(QString &handle);
    bool loadDetails(QString &handle);

    QFile file;
    Person ThisGuy;

public:

    static AccountManager* getInstance();
    bool createAccount(QString &first, QString &last, QString &email, QString &handle, QString &password);
    Person getCurrentAccount();


    Person findPersonByEmail(QString &emailtoCheck);
    Person findPersonByHandle(QString &handle);


};

#endif // ACCOUNTMANAGER_H
