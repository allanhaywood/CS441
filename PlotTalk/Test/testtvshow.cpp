#include <QtTest/QtTest>
#include "testtvshow.h"

void TestTvShow::testDefaultConstructor()
{
    // Set up strings to compare against.
    QString name = "Tvshow name";
    QString imdbLink = "http://www.imdb.com";
    QString graphicLink = "";

    TvShow tvShow = TvShow();
    QCOMPARE(name, tvShow.name);
    QCOMPARE(imdbLink, tvShow.imdbLink);
    QCOMPARE(graphicLink, tvShow.graphicLink);
}
