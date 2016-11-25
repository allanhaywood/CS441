/* Tests the Tv Show class.
 *
 * @author Allan Haywood
 */
#include <QtTest/QtTest>
#include "testtvshow.h"
#include "jsonconnection.h"

void TestTvShow::TestConstructor()
{
    // Set up strings to compare against.
    QString name = "Tvshow name";
    QString tmdbLink = "https://www.themoviedb.org/";
    QString graphicLink = "https://www.themoviedb.org/assets/8ce4f6ee3ea26190a7f21d1f9e7e9be2/images/v4/logos/182x162.png";
    int ShowId=0;
    TvShow tvShow = TvShow(name, tmdbLink, graphicLink);
    QCOMPARE(name, tvShow.name);
    QCOMPARE(tmdbLink, tvShow.tmdbLink);
    QCOMPARE(graphicLink, tvShow.graphicLink);
    QCOMPARE(ShowId, tvShow.showId);
}
