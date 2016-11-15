/* The TvShow class.
 *
 * @author Allan Haywood
 */
#include "tvshow.h"
#include "plottalkexceptions.h"

/**
 * @brief TvShow::TvShow Default constructor.
 */
TvShow::TvShow()
{
    showId = 0;
    name = "";
    tmdbLink = "";
    graphicLink = "";
    seasons = QVector<Season>();
}

/**
 * @brief TvShow::TvShow Represents a tvshow in our application.
 * @param name The name of the tvshow.
 * @param tmdbLink The tmdbLink for this show.
 * @param graphicLink A link to a graphic to be used in our application.
 */
TvShow::TvShow(QString name, QString tmdbLink, QString graphicLink)
{
    showId = 0;
    this->name = name;
    this->tmdbLink = tmdbLink;
    this->graphicLink = graphicLink;
    seasons = QVector<Season>();
}

/**
 * @brief TvShow::TvShow Represents a tvshow in our application
 * @param showId The showId as specified by the moviedb.
 * @param name The name of the tvshow.
 * @param tmdbLink The URL to the show on the moviedb website.
 * @param graphicLink A URL to a graphic for the show.
 */
TvShow::TvShow(int showId, QString name, QString tmdbLink, QString graphicLink)
{
    this->showId = showId;
    this->name = name;
    this->tmdbLink = tmdbLink;
    this->graphicLink = graphicLink;
    seasons = QVector<Season>();
}

/**
 * @brief TvShow::TvShow Represents a tvshow in our application
 * @param showId The showId as specified by the moviedb.
 * @param name The name of the tvshow.
 * @param tmdbLink The URL to the show on the moviedb website.
 * @param graphicLink A URL to a graphic for the show.
 * @param seasons A vector of seasons to add to the tvshow.
 */
TvShow::TvShow(int showId, QString name, QString tmdbLink, QString graphicLink, QVector<Season> seasons)
{
    this->showId = showId;
    this->name = name;
    this->tmdbLink = tmdbLink;
    this->graphicLink = graphicLink;
    this->seasons = seasons;
}

/**
 * @brief TvShow::inspectSeasons Returns a reference to the vector of season.
 * @return A reference to the vector of season.
 *
 * NOTE: Any changes made to seasons will not be reflected in the TvShow class.
 */
const QVector<Season>& TvShow::inspectSeasons()
{
    return seasons;
}

/**
 * @brief TvShow::addSeason Adds a season to the tvshow.
 * @param season The season to add.
 */
void TvShow::addSeason(Season season)
{
    seasons.append(season);
}

/**
 * @brief TvShow::getSeason Return season with matching number in this TvShow
 * @param int number
 * @returns matching Season
 * @throws NotFound exception if no match found
 */
Season TvShow::getSeason(int number)
{
    foreach (Season season, seasons) {
        if (season.seasonNumber == number) {
            return season;
        }
    }
    throw NotFound();
}
