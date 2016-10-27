/* Tests the Database Manager class.
 *
 * @author Allan Haywood
 */
#include <QtTest/QtTest>
#include "testdatabasemanager.h"

void TestDatabaseManager::testGetTvShowDefaultConstructor()
{
    // Set up strings to compare against.
    QString name = "Game Of Thrones";
    QString expectedTmdbLink = "https://www.themoviedb.org/tv/1399-game-of-thrones";
    QString expectedGraphicLink = "https://image.tmdb.org/t/p/w600_and_h900_bestv2/jihl6mlt7ablhbhjgeoibiouvl1.jpg";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    TvShow tvShow = TvShow("", "", "");
    DatabaseManagerSingleton::Instance().getTvShow(name, tvShow);

    QCOMPARE(tvShow.name.toLower(), name.toLower());
    QCOMPARE(tvShow.tmdbLink.toLower(), expectedTmdbLink.toLower());
    QCOMPARE(tvShow.graphicLink.toLower(), expectedGraphicLink.toLower());
}

void TestDatabaseManager::TestGetTvShowJsonPathConstructor()
{
    // Set up strings to compare against.
    QString name = "Breaking Bad";
    QString expectedTmdbLink = "https://www.themoviedb.org/tv/1396-breaking-bad";
    QString expectedGraphicLink = "https://image.tmdb.org/t/p/w600_and_h900_bestv2/1yevjox3rjo2jbkrrihimj7uos9.jpg";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    TvShow tvShow = TvShow("", "", "");
    DatabaseManagerSingleton::Instance(":/json/Json/test2.json").getTvShow(name, tvShow);

    QCOMPARE(tvShow.name.toLower(), name.toLower());
    QCOMPARE(tvShow.tmdbLink.toLower(), expectedTmdbLink.toLower());
    QCOMPARE(tvShow.graphicLink.toLower(), expectedGraphicLink.toLower());
}
