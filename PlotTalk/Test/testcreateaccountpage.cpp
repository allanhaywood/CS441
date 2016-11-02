#include "testcreateaccountpage.h"
#include "createacctpage.h"
#include<QtTest/QtTest>
#include <guiddef.h>

void testcreateaccountpage::testConstructor()
{
//system generated constructor
}
void testcreateaccountpage::testOnCreateAcctButtonPress()
{
QString fName="Josh";
QString lName="Reaves";
QString validHandle="Handle1";
QString validEmail="reave006@cougars.csusm.edu";
QString Pwd1 ="ABCabc123!";
QString Pwd2 ="abcABC123!";
QString badPwd="hieveryone!";
QString badPwd2 ="123456";
QString badPwd3 ="!@#$%^&";
QString badPwd4 ="hello world21!";

CreateAcctPage newPage;

//newPage.QWidget.


//newPage.on_CreateAcctButton_clicked();
}
