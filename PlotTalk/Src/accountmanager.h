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
    User BlankMan;
    User &referenceTodatabaseUser=BlankMan;

public:

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    static AccountManager* getInstance();
    bool createAccount(QString first, QString last, QString Email, QString handle, QString password);//done
    bool createAccount(QString first, QString last, QString Email, QString handle, QString password, bool isAdmin);
    bool createAccount(User user);
    User &getCurrentAccount();//done
    selectEnum checkFieldsAndCreate(QString fName, QString lName, QString handle, QString email, QString password, bool isAdmin);
    bool checkEmailAndPassword(QString email, QString password, User &user);
    bool EmailExists(QString email);
    void ClearForLogout();
};

#endif // ACCOUNTMANAGER_H
