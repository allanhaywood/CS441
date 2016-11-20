#include "testseason.h"
#include <QtTest/QtTest>

void testSeason::testSeasonConstructor()
{
    int seasonId = 9;
    int seasonNumber = 1;
    QString name = "Test";

    QMap<int, Episode> episodes = QMap<int, Episode>();

    Season season = Season(seasonId, seasonNumber, name, episodes);
    QCOMPARE(season.seasonId, seasonId);
    QCOMPARE(season.seasonNumber, seasonNumber);
    QCOMPARE(season.name, name);
}
