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
    AccountManager();
    AccountManager(const AccountManager &);
    AccountManager &operator=(const AccountManager &);
    ~AccountManager();
    QSharedDataPointer<AccountManagerData> data;
public:

};

#endif // ACCOUNTMANAGER_H
