#ifndef ACCOUNTCHECKANDSTORE_H
#define ACCOUNTCHECKANDSTORE_H

#include <QDeclarativeItem>
#include <QMainWindow>
#include <QObject>
#include <QWidget>

class AccountCheckAndStore
{
 private:
    struct person
    {
        string First;
        string Last;
        string email;
        string password;
    };


    AccountCheckAndStore();
    ~AccountCheckAndStore();

public:
    static getInstance();
    bool checkEmail(string email);
    bool AddPerson(QString &first, QString &last, QString &email, QString &password);
};

#endif // ACCOUNTCHECKANDSTORE_H
