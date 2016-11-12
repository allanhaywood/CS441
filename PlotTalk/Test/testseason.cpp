#include "testseason.h"
#include <QtTest/QtTest>

void testSeason::testSeasonConstructor()
{
    int seasonNumber = 9;

    Season season = Season(seasonNumber);
    QCOMPARE(seasonNumber, season.seasonNumber);

}
