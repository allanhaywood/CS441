#include "testseason.h"
#include <QtTest/QtTest>

void testSeason::testSeasonConstructor()
{
    QString seasonNumber = "9";
    QList<int> episodes;

    Season season = Season(seasonNumber,episodes);
    QCOMPARE(seasonNumber, season.seasonNumber);
    QCOMPARE(episodes, season.episodes);


}
