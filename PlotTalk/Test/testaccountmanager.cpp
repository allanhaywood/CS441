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

    User userHold= User (validHandle3,fName,lName,validEmail3,validPwd, false);
    QCOMPARE(checkme->checkFieldsAndCreate(userHold),selectEnum::ALLCLEAR);
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
   // DatabaseManagerSingleton::Instance().removeUser(validHandle2);

    User toCheckAndChange = User(validHandle,fName,lName,validEmail,Pwd1, false);
    QCOMPARE(checkme->checkFieldsAndCreate(toCheckAndChange),selectEnum::ALLCLEAR);//account added

    toCheckAndChange.username = validHandle;  //already taken
    toCheckAndChange.firstName = fName;
    toCheckAndChange.lastName = lName;
    toCheckAndChange.email = validEmail2;
    toCheckAndChange.passwordHash = Pwd1;
    QCOMPARE(checkme->checkFieldsAndCreate(toCheckAndChange),selectEnum::USERNAME_TAKEN);//handle is already used

    toCheckAndChange.username = validHandle2;
    toCheckAndChange.firstName = none;  //missing first name
    toCheckAndChange.lastName = lName;
    toCheckAndChange.email = validEmail2;
    toCheckAndChange.passwordHash = Pwd1;
    QCOMPARE(checkme->checkFieldsAndCreate(toCheckAndChange),selectEnum::VALUES_MISSING);//First Name is not acceptable

    toCheckAndChange.firstName = fName;
    toCheckAndChange.lastName = none;   //missing last name
    toCheckAndChange.username = validHandle2;
    toCheckAndChange.email = validEmail2;
    toCheckAndChange.passwordHash = Pwd1;
    QCOMPARE(checkme->checkFieldsAndCreate(toCheckAndChange),selectEnum::VALUES_MISSING);//Last Name is not acceptable

    toCheckAndChange.firstName = fName;
    toCheckAndChange.lastName = lName;
    toCheckAndChange.username = validHandle2;
    toCheckAndChange.email = validEmail;  //email alraedy taken
    toCheckAndChange.passwordHash = Pwd1;
    QCOMPARE(checkme->checkFieldsAndCreate(toCheckAndChange),selectEnum::DUPLICATE_EMAIL);//email is already used

    toCheckAndChange.firstName = fName;
    toCheckAndChange.lastName = lName;
    toCheckAndChange.username = validHandle2;
    toCheckAndChange.email = validHandle;   //a handle does not meet the criteria of an email
    toCheckAndChange.passwordHash = Pwd1;
    QCOMPARE(checkme->checkFieldsAndCreate(toCheckAndChange),selectEnum::BAD_EMAIL);//email format bad

    toCheckAndChange.firstName = fName;
    toCheckAndChange.lastName = lName;
    toCheckAndChange.username = validHandle2;
    toCheckAndChange.email = badEmail;      //this is a bad email format
    toCheckAndChange.passwordHash = Pwd1;
    QCOMPARE(checkme->checkFieldsAndCreate(toCheckAndChange),selectEnum::BAD_EMAIL);//less bad email is rejected

    toCheckAndChange.firstName = fName;
    toCheckAndChange.lastName = lName;
    toCheckAndChange.username = validHandle2;
    toCheckAndChange.email = validEmail2;
    toCheckAndChange.passwordHash = badPwd;  //bad passwword format
    QCOMPARE(checkme->checkFieldsAndCreate(toCheckAndChange),selectEnum::BAD_PASSWORD);//bad password format is rejected

    toCheckAndChange.firstName = fName;
    toCheckAndChange.lastName = lName;
    toCheckAndChange.username = validHandle2;
    toCheckAndChange.email = validEmail2;
    toCheckAndChange.passwordHash = badPwd2;  //different format for bad password
    QCOMPARE(checkme->checkFieldsAndCreate(toCheckAndChange),selectEnum::BAD_PASSWORD);//other bad password is rejected

    toCheckAndChange.firstName = fName;
    toCheckAndChange.lastName = lName;
    toCheckAndChange.username = validHandle2;
    toCheckAndChange.email = validEmail2;
    toCheckAndChange.passwordHash = Pwd2;//no special characters in this password
    QCOMPARE(checkme->checkFieldsAndCreate(toCheckAndChange),selectEnum::BAD_PASSWORD);//bad passward is rejected

    toCheckAndChange.firstName = fName;
    toCheckAndChange.lastName = lName;
    toCheckAndChange.username = validHandle2;
    toCheckAndChange.email = validEmail2;
    toCheckAndChange.passwordHash = badPwd3;// another type of bad password
    QCOMPARE(checkme->checkFieldsAndCreate(toCheckAndChange),selectEnum::BAD_PASSWORD);//bad passward is rejected


    toCheckAndChange.firstName = fName;
    toCheckAndChange.lastName = lName;
    toCheckAndChange.username = validHandle2;
    toCheckAndChange.email = validEmail2;
    toCheckAndChange.passwordHash = badPwd4;//another type of bad password
    QCOMPARE(checkme->checkFieldsAndCreate(toCheckAndChange),selectEnum::BAD_PASSWORD);//bad passward is rejected


    toCheckAndChange.firstName = fName;
    toCheckAndChange.lastName = lName;
    toCheckAndChange.username = validHandle2;
    toCheckAndChange.email = validEmail2;
    toCheckAndChange.passwordHash = badPwd5;  //another type of bad password
    QCOMPARE(checkme->checkFieldsAndCreate(toCheckAndChange),selectEnum::BAD_PASSWORD);//bad passward is rejected


    toCheckAndChange.firstName = fName;
    toCheckAndChange.lastName = lName;
    toCheckAndChange.username = validHandle2;
    toCheckAndChange.email = validEmail2;
    toCheckAndChange.passwordHash = Pwd1;  //all information is good
    QCOMPARE(checkme->checkFieldsAndCreate(toCheckAndChange),selectEnum::ALLCLEAR);//second account is added
    QCOMPARE(checkme->checkFieldsAndCreate(toCheckAndChange),selectEnum::DUPLICATE_EMAIL);//email is already used

    // Remove temp users when done.
    DatabaseManagerSingleton::Instance().removeUser(validHandle);
    DatabaseManagerSingleton::Instance().removeUser(validHandle2);

}

