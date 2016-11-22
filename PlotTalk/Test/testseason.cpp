#include "testseason.h"
#include <QtTest/QtTest>

void testSeason::testSeasonConstructor()
{
    int seasonId = 9;
    int seasonNumber = 1;
    QString name = "Test";

    QHash<int, Episode> episodes = QHash<int, Episode>();

    Season season = Season(seasonId, seasonNumber, name, episodes);
    QCOMPARE(season.seasonId, seasonId);
    QCOMPARE(season.seasonNumber, seasonNumber);
    QCOMPARE(season.name, name);
}
