#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QMainWindow>
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QList>

#include "databasemanager.h"
#include "user.h"

enum class selectEnum//creates an enum that is used to pass back errors from account manager
{
    ALLCLEAR,
    BAD_EMAIL,
    DUPLICATE_EMAIL,
    USERNAME_TAKEN,
    VALUES_MISSING,
    BAD_PASSWORD
};

class AccountManager
{
private:
    static AccountManager* instance;//creates the static instance
    AccountManager();//constructor
    ~AccountManager();//destructor
    User thisGuy;

public:


    static AccountManager* getInstance();
    bool createAccount(QString &first, QString &last, QString &Email, QString &handle, QString &password);//done
    User getCurrentAccount();//done
    selectEnum checkFieldsAndCreate(QString &fName, QString &lName, QString &handle, QString &email, QString &password);
    bool checkEmailAndPassword(QString& email, QString& password, User &user);
};

#endif // ACCOUNTMANAGER_H
