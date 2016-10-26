#include <QtTest/QtTest>
#include "testdatabasemanager.h"

void TestDatabaseManager::testGetTvShow()
{
    // Set up strings to compare against.
    QString name = "Game Of Thrones";
    QString expectedTmdbLink = "http://www.imdb.com/title/tt0944947/";
    QString expectedGraphicLink = "https://images-na.ssl-images-amazon.com/images/M/MV5BMjM5OTQ1MTY5Nl5BMl5BanBnXkFtZTgwMjM3NzMxODE@._V1_SY1000_CR0,0,674,1000_AL_.jpg";

    DatabaseManager databaseManager = DatabaseManager();

    TvShow tvShow = TvShow("", "", "");
    databaseManager.getTvShow(name, tvShow);

    QCOMPARE(tvShow.name.toLower(), name.toLower());
    QCOMPARE(tvShow.tmdbLink.toLower(), expectedTmdbLink.toLower());
    QCOMPARE(tvShow.graphicLink.toLower(), expectedGraphicLink.toLower());
}
