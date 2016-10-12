#ifndef ACCOUNTCHECKANDSTORE_H
#define ACCOUNTCHECKANDSTORE_H

#include <QDeclarativeItem>
#include <QMainWindow>
#include <QObject>
#include <QWidget>

class AccountCheckAndStore
{
private:
    AccountCheckAndStore();
    ~AccountCheckAndStore();

public:
    static getInstance();
    bool checkEmail(string email);
};

#endif // ACCOUNTCHECKANDSTORE_H
