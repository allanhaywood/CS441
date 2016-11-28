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

    User userHeldForRefresh;

public:

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    static AccountManager* getInstance();
    void createAccount(User user);
    User &getCurrentAccount();
    selectEnum checkFieldsAndCreate(User user);
    bool checkEmailAndPassword(QString email, QString password, User &user);
    bool EmailExists(QString email);
    void ClearForLogout();
};

#endif // ACCOUNTMANAGER_H
