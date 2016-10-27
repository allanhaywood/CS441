/* Tests the Json Connection class.
 *
 * @author Allan Haywood
 */
#include <QtTest/QtTest>
#include "testjsonconnection.h"

void TestJsonConnection::testGetTvShow()
{
    // Set up strings to compare against.
    QString name = "Game Of Thrones";
    QString expectedTmdbLink = "https://www.themoviedb.org/tv/1399-game-of-thrones";
    QString expectedGraphicLink = "https://image.tmdb.org/t/p/w600_and_h900_bestv2/jihl6mlt7ablhbhjgeoibiouvl1.jpg";

    JsonConnection jsonConnection = JsonConnection(":/json/Json/test.json");

    TvShow tvShow = TvShow("", "", "");
    jsonConnection.getTvShow(name, tvShow);

    QCOMPARE(tvShow.name.toLower(), name.toLower());
    QCOMPARE(tvShow.tmdbLink.toLower(), expectedTmdbLink.toLower());
    QCOMPARE(tvShow.graphicLink.toLower(), expectedGraphicLink.toLower());
}
