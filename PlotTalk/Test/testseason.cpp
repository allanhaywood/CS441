#include "testseason.h"
#include <QtTest/QtTest>

void testSeason::testSeasonConstructor()
{
    int seasonId = 9;
    QString name = "Test";

    QVector<Episode> episodes = QVector<Episode>();

    Season season = Season(seasonId, name, episodes);
    QCOMPARE(season.seasonId, seasonId);
    QCOMPARE(season.name, name);
}
