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

    User holder;
    AccountManager *checkme= AccountManager::getInstance();
    QCOMPARE((checkme->checkFields(fName,lName,validHandle3,validEmail3,validPwd)),1);
    holder=checkme->getCurrentAccount();
    QCOMPARE(holder.firstName,fName);
    QCOMPARE(holder.lastName,lName);
    QCOMPARE(holder.email,validEmail3);
    QCOMPARE(holder.username,validPwd);
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

    QCOMPARE((checkme->checkFields(fName,lName,validHandle,validEmail,Pwd1)),1);//account added
    QCOMPARE((checkme->checkFields(fName,lName,validHandle,validEmail2,Pwd1)),3);//handle is already used
    QCOMPARE((checkme->checkFields(none,lName,validHandle2,validEmail2,Pwd1)),6);//First Name is not acceptable
    QCOMPARE((checkme->checkFields(fName,none,validHandle2,validEmail2,Pwd1)),6);//Last Name is not acceptable
    QCOMPARE((checkme->checkFields(fName,lName,validHandle2,validEmail,Pwd1)),4);//email is already used
    QCOMPARE((checkme->checkFields(fName,lName,validHandle2,validHandle,Pwd1)),2);//email format bad
    QCOMPARE((checkme->checkFields(fName,lName,validHandle2,badEmail,Pwd1)),2);//less bad email is rejected
    QCOMPARE((checkme->checkFields(fName,lName,validHandle2,validEmail2,badPwd)),5);//bad password format is rejected
    QCOMPARE((checkme->checkFields(fName,lName,validHandle2,validEmail2,badPwd2)),5);//other bad password is rejected
    QCOMPARE((checkme->checkFields(fName,lName,validHandle2,validEmail2,Pwd2)),5);//bad passward is rejected
    QCOMPARE((checkme->checkFields(fName,lName,validHandle2,validEmail2,badPwd3)),5);//bad passward is rejected
    QCOMPARE((checkme->checkFields(fName,lName,validHandle2,validEmail2,badPwd4)),5);//bad passward is rejected
    QCOMPARE((checkme->checkFields(fName,lName,validHandle2,validEmail2,badPwd5)),5);//bad passward is rejected
    QCOMPARE((checkme->checkFields(fName,lName,validHandle2,validEmail2,Pwd1)),1);//second account is added
    QCOMPARE((checkme->checkFields(fName,lName,validHandle2,validEmail2,Pwd1)),4);//email is already used

}

