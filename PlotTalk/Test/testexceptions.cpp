/* Tests PlotTalk exceptions */
#include <QtTest/QTest>
#include "testexceptions.h"
#include "tvshow.h"

void testExceptions::testExceptionThrow()
{
    TvShow show ("Show Name", "", ""); //create a show with nothing in it
    QString actualMessage;
    try {
        show.inspectSeason(0); //try to retrieve an episode from it - will throw NotFound exception
    } catch (PlotTalkException e) {
        actualMessage = e.message;
    }
    QString expectedMessage = "Unable to retrieve season number 0 from show Show Name";
    QCOMPARE(actualMessage, expectedMessage);
}
