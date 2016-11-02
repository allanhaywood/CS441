#ifndef TESTACCOUNTMANAGER_H
#define TESTACCOUNTMANAGER_H

#include <QObject>
#include "accountmanager.h"

class testAccountManager : public QObject
{
    Q_OBJECT
private slots:
    void testConstructor();//test the singleton constructor
    void TestcreateAccount();//generates a new account
    void testGetCurrentAccount();//returns the account that was created
    void TestFindPersonByEmail();//check if an email exists in the database
    void testFindPersonByHandle();//check if a handle exists in the database
};

#endif // TESTACCOUNTMANAGER_H
