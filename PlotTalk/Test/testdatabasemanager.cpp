/* Tests the Database Manager class.
 *
 * @author Allan Haywood
 */
#include <QtTest/QtTest>
#include "plottalkexceptions.h"
#include "testdatabasemanager.h"

/**
 * @brief TestDatabaseManager::TestGetTvShowDefaultConstructor Uses the default constructor for the DBManager and looks up
 * a TvShow.
 */
void TestDatabaseManager::TestGetTvShowDefaultConstructor()
{
    // Set up strings to compare against.
    QString name = "Game Of Thrones";
    QString expectedTmdbLink = "https://www.themoviedb.org/tv/1399-game-of-thrones";
    QString expectedGraphicLink = "https://image.tmdb.org/t/p/w600_and_h900_bestv2/jihl6mlt7ablhbhjgeoibiouvl1.jpg";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    TvShow& tvShow = DatabaseManagerSingleton::Instance().getTvShow(name);

    QCOMPARE(tvShow.name.toLower(), name.toLower());
    QCOMPARE(tvShow.tmdbLink.toLower(), expectedTmdbLink.toLower());
    QCOMPARE(tvShow.graphicLink.toLower(), expectedGraphicLink.toLower());
}

/**
 * @brief TestDatabaseManager::TestGetTvShowJsonPathConstructor Uses the json path constructor, and looks up a Tvshow.
 */
void TestDatabaseManager::TestGetTvShowJsonPathConstructor()
{
    // Set up strings to compare against.
    QString name = "Breaking Bad";
    QString expectedTmdbLink = "https://www.themoviedb.org/tv/1396-breaking-bad";
    QString expectedGraphicLink = "https://image.tmdb.org/t/p/w600_and_h900_bestv2/1yevjox3rjo2jbkrrihimj7uos9.jpg";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    TvShow& tvShow = DatabaseManagerSingleton::Instance(":/json/Json/test2.json").getTvShow(name);

    QCOMPARE(tvShow.name.toLower(), name.toLower());
    QCOMPARE(tvShow.tmdbLink.toLower(), expectedTmdbLink.toLower());
    QCOMPARE(tvShow.graphicLink.toLower(), expectedGraphicLink.toLower());
}

/**
 * @brief TestDatabaseManager::NegTestGetTvShowJsonPathConstructor Looks up a TvShow that doesn't exist in the json file.
 * Checks that that proper exception is thrown.
 */
void TestDatabaseManager::NegTestGetTvShowJsonPathConstructor()
{
    // Set up strings to compare against.
    QString name = "Doesn't exist";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    QVERIFY_EXCEPTION_THROWN
            (
                TvShow tvShow = DatabaseManagerSingleton::Instance(":/json/Json/test2.json").getTvShow(name),
                NotFound
            );
}