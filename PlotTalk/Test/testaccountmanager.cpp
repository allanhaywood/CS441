/* Tests the account manager class */
#include <QtTest/QTest>
#include "testaccountmanager.h"
#include "accountmanager.h"

void testAccountManager::testGetCurrentAccount()//returns the account that was created
{
    QString fName="Josh";
    QString lName="Reaves";
    QString validHandle3="HandleUnique";
    QString validEmail3="reave005@cougars.csusm.edu";
    QString validPwd="aRe1nOt2?!";

    // Remove test users before attempting to add.
    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;
    DatabaseManagerSingleton::Instance().removeUser(validHandle3);

    User holder;
    AccountManager *checkme= AccountManager::getInstance();
    QCOMPARE(checkme->checkFieldsAndCreate(fName,lName,validHandle3,validEmail3,validPwd, false),selectEnum::ALLCLEAR);
    holder=checkme->getCurrentAccount();
    QCOMPARE(holder.firstName,fName);
    QCOMPARE(holder.lastName,lName);
    QCOMPARE(holder.email,validEmail3);
    QCOMPARE(holder.username,validHandle3);
    QCOMPARE(holder.passwordHash,validPwd);

    // Remove temp user when done.
    DatabaseManagerSingleton::Instance().removeUser(validHandle3);
}

void testAccountManager::testCheckFields()
{
    QString fName="Josh";
    QString lName="Reaves";
    QString validHandle="Handle1";
    QString validHandle2="Handle2";
    QString validEmail="reave006@cougars.csusm.edu";
    QString validEmail2="joshua.j.reaves@gmail.com";
    QString badEmail="@gas.fat";
    QString Pwd1 ="ABCabc123!";
    QString Pwd2 ="123JJRjjr";
    QString badPwd="hieveryone!";
    QString badPwd2 ="123456789";
    QString none ="";
    QString badPwd3 ="!@#$%^&*&^%$";
    QString badPwd5 = "1#3.Abc";
    QString badPwd4 ="hello world21!";

    AccountManager *checkme= AccountManager::getInstance();

    // Remove test users before attempting to add.
    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;
    DatabaseManagerSingleton::Instance().removeUser(validHandle);
    DatabaseManagerSingleton::Instance().removeUser(validHandle2);

    QCOMPARE(checkme->checkFieldsAndCreate(fName,lName,validHandle,validEmail,Pwd1, false),selectEnum::ALLCLEAR);//account added
    QCOMPARE(checkme->checkFieldsAndCreate(fName,lName,validHandle,validEmail2,Pwd1, false),selectEnum::USERNAME_TAKEN);//handle is already used
    QCOMPARE(checkme->checkFieldsAndCreate(none,lName,validHandle2,validEmail2,Pwd1, false),selectEnum::VALUES_MISSING);//First Name is not acceptable
    QCOMPARE(checkme->checkFieldsAndCreate(fName,none,validHandle2,validEmail2,Pwd1, false),selectEnum::VALUES_MISSING);//Last Name is not acceptable
    QCOMPARE(checkme->checkFieldsAndCreate(fName,lName,validHandle2,validEmail,Pwd1, false),selectEnum::DUPLICATE_EMAIL);//email is already used
    QCOMPARE(checkme->checkFieldsAndCreate(fName,lName,validHandle2,validHandle,Pwd1, false),selectEnum::BAD_EMAIL);//email format bad
    QCOMPARE(checkme->checkFieldsAndCreate(fName,lName,validHandle2,badEmail,Pwd1, false),selectEnum::BAD_EMAIL);//less bad email is rejected
    QCOMPARE(checkme->checkFieldsAndCreate(fName,lName,validHandle2,validEmail2,badPwd, false),selectEnum::BAD_PASSWORD);//bad password format is rejected
    QCOMPARE(checkme->checkFieldsAndCreate(fName,lName,validHandle2,validEmail2,badPwd2, false),selectEnum::BAD_PASSWORD);//other bad password is rejected
    QCOMPARE(checkme->checkFieldsAndCreate(fName,lName,validHandle2,validEmail2,Pwd2, false),selectEnum::BAD_PASSWORD);//bad passward is rejected
    QCOMPARE(checkme->checkFieldsAndCreate(fName,lName,validHandle2,validEmail2,badPwd3, false),selectEnum::BAD_PASSWORD);//bad passward is rejected
    QCOMPARE(checkme->checkFieldsAndCreate(fName,lName,validHandle2,validEmail2,badPwd4, false),selectEnum::BAD_PASSWORD);//bad passward is rejected
    QCOMPARE(checkme->checkFieldsAndCreate(fName,lName,validHandle2,validEmail2,badPwd5, false),selectEnum::BAD_PASSWORD);//bad passward is rejected
    QCOMPARE(checkme->checkFieldsAndCreate(fName,lName,validHandle2,validEmail2,Pwd1, false),selectEnum::ALLCLEAR);//second account is added
    QCOMPARE(checkme->checkFieldsAndCreate(fName,lName,validHandle2,validEmail2,Pwd1, false),selectEnum::DUPLICATE_EMAIL);//email is already used

    // Remove temp users when done.
    DatabaseManagerSingleton::Instance().removeUser(validHandle);
    DatabaseManagerSingleton::Instance().removeUser(validHandle2);

}

