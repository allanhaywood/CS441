/* Main for all the unit tests.
 *
 * @author Allan Haywood
 */
#include <QtTest/QtTest>

// Add includes for all test class headers here.
#include "testtvshow.h"
#include "testjsonconnection.h"
#include "testdatabasemanager.h"
#include "testreply.h"
#include "testaccountmanager.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    // Add variable for each test class here.
    TestTvShow testTvShow;
    TestJsonConnection testJsonConnection;
    TestDatabaseManager testDatabaseManager;
    TestReply testReply;
    testAccountManager testActMgr;

    // Add references to each test class variable here, seperating with |
    int result = QTest::qExec(&testTvShow, argc, argv) |
                 QTest::qExec(&testReply, argc, argv) |
                 QTest::qExec(&testJsonConnection, argc, argv) |
                 QTest::qExec(&testDatabaseManager, argc, argv) |
                 QTest::qExec(&testActMgr,argc,argv);

    //make the overall result of the tests more obvious
    if (result == 0) {
        qDebug() << "ALL TESTS PASSED";
    } else {
        qDebug() << "TEST FAILED";
    }

    return result;
}
