#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QMainWindow>
#include <QObject>
#include <QSharedDataPointer>
#include <QWidget>

class AccountManagerData;

class AccountManager
{
private:
    static AccountManager* instance;
    AccountManager();
    AccountManager(const AccountManager &);
    AccountManager &operator=(const AccountManager &);
    ~AccountManager();
    QSharedDataPointer<AccountManagerData> data;
public:

    static *getInstance();
    bool createAccount(QString &first, QString &last, QString &email, QString &password);

};

#endif // ACCOUNTMANAGER_H
