#ifndef TESTACCOUNTMANAGER_H
#define TESTACCOUNTMANAGER_H

#include <QObject>
#include "accountmanager.h"

class testAccountManager : public QObject
{
    Q_OBJECT
private slots:
    void testCheckFields();//check all types of account creation errors
    void testGetCurrentAccount();//returns the account that was created
};

#endif // TESTACCOUNTMANAGER_H
