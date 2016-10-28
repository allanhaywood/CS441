#include <QtTest/QtTest>
#include "testtvshow.h"

void TestTvShow::testConstructor()
{
    // Set up strings to compare against.
    QString name = "Tvshow name";
    QString tmdbLink = "https://www.themoviedb.org/";
    QString graphicLink = "https://www.themoviedb.org/assets/8ce4f6ee3ea26190a7f21d1f9e7e9be2/images/v4/logos/182x162.png";

    TvShow tvShow = TvShow(name, tmdbLink, graphicLink);
    QCOMPARE(name, tvShow.name);
    QCOMPARE(tmdbLink, tvShow.tmdbLink);
    QCOMPARE(graphicLink, tvShow.graphicLink);
}
