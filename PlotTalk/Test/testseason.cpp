#include "testseason.h"
#include <QtTest/QtTest>

void testSeason::testSeasonConstructor()
{
    int seasonId = 9;
    int seasonNumber = 1;
    QString name = "Test";

    QVector<Episode> episodes = QVector<Episode>();

    Season season = Season(seasonId, seasonNumber, name, episodes);
    QCOMPARE(season.seasonId, seasonId);
    QCOMPARE(season.seasonNumber, seasonNumber);
    QCOMPARE(season.name, name);
}
