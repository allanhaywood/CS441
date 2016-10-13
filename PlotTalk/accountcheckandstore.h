#ifndef ACCOUNTCHECKANDSTORE_H
#define ACCOUNTCHECKANDSTORE_H


#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QList>

class AccountCheckAndStore
{
 private:
    struct person
    {
        QString First;
        QString Last;
        QString email;
        QString password;
    };

    QList<person> ListOfPeople;
    static AccountCheckAndStore* AccountInstance;

    AccountCheckAndStore();
    ~AccountCheckAndStore();



public:
    static AccountCheckAndStore* getInstance();
    bool checkEmail(QString &email);
    bool AddPerson(QString &first, QString &last, QString &email, QString &password);
};

#endif // ACCOUNTCHECKANDSTORE_H
