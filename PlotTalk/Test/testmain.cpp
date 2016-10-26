#include <QtTest/QtTest>

// Add includes for all test class headers here.
#include "testtvshow.h"
#include "testjsonconnection.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    // Add variable for each test class here.
    TestTvShow testTvShow;
    TestJsonConnection testJsonConnection;

    // Add references to each test class variable here, seperating with |
    return QTest::qExec(&testTvShow, argc, argv) |
            QTest::qExec(&testJsonConnection, argc, argv);
}
