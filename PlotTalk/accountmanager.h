#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QMainWindow>
#include <QObject>
#include <QSharedDataPointer>
#include <QWidget>

class AccountManagerData;

class AccountManager
{
public:
    AccountManager();
    AccountManager(const AccountManager &);
    AccountManager &operator=(const AccountManager &);
    ~AccountManager();

private:
    QSharedDataPointer<AccountManagerData> data;
};

#endif // ACCOUNTMANAGER_H