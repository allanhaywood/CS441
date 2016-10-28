#include <QtTest/QtTest>
#include "testjsonconnection.h"

void TestJsonConnection::testGetTvShow()
{
    // Set up strings to compare against.
    QString name = "Game Of Thrones";
    QString expectedTmdbLink = "http://www.imdb.com/title/tt0944947/";
    QString expectedGraphicLink = "https://images-na.ssl-images-amazon.com/images/M/MV5BMjM5OTQ1MTY5Nl5BMl5BanBnXkFtZTgwMjM3NzMxODE@._V1_SY1000_CR0,0,674,1000_AL_.jpg";

    JsonConnection jsonConnection = JsonConnection(":/json/Json/test.json");
    TvShow tvShow = jsonConnection.getTvShow(name);

    QCOMPARE(tvShow.name.toLower(), name.toLower());
    QCOMPARE(tvShow.tmdbLink.toLower(), expectedTmdbLink.toLower());
    QCOMPARE(tvShow.graphicLink.toLower(), expectedGraphicLink.toLower());
}
