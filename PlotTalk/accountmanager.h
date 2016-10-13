#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QMainWindow>
#include <QSharedDataPointer>
#include <QWidget>


class AccountManager
{
private:
    static AccountManager* instance;
    AccountManager();
    ~AccountManager();

public:

    static AccountManager* getInstance();
    bool createAccount(QString &first, QString &last, QString &email, QString &password);

};

#endif // ACCOUNTMANAGER_H
