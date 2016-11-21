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
    seasons = QMap<int, Season>();
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
    seasons = QMap<int, Season>();
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
    seasons = QMap<int, Season>();
}

/**
 * @brief TvShow::TvShow Represents a tvshow in our application
 * @param showId The showId as specified by the moviedb.
 * @param name The name of the tvshow.
 * @param tmdbLink The URL to the show on the moviedb website.
 * @param graphicLink A URL to a graphic for the show.
 * @param seasons A map of seasons to add to the tvshow.
 */
TvShow::TvShow(int showId, QString name, QString tmdbLink, QString graphicLink, QMap<int, Season> seasons)
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
const QVector<Season> TvShow::inspectSeasons()
{
    return seasons.values().toVector();
}

QMap<int, Season> &TvShow::getSeasons()
{
    return seasons;
}

/**
 * @brief TvShow::addSeason Adds a season to the tvshow.
 * @param season The season to add.
 */
void TvShow::addSeason(Season season)
{
    seasons.insert(season.seasonId, season);
}

/**
 * @brief TvShow::getSeason Return season with matching number in this TvShow
 * @param int number
 * @returns matching Season
 * @throws NotFound exception if no match found
 */
Season &TvShow::getSeason(int number)
{
    for (auto &season : seasons)
    {
        if ( season.seasonNumber == number )
        {
            return season;
        }
    }

    throw NotFound{};
}

/**
 * @brief TvShow::inspectSeason Returns a copy of the specified season.
 * @param number The number of the season to return.
 * @return The season with the specified number.
 */
Season TvShow::inspectSeason(int number)
{
    return getSeason(number);
}

/**
 * @brief TvShow::addEpisodeReview Adds the specified review to the specified episode.
 * @param episodeIdentifier The specific episode to add the review to.
 * @param review The review to add.
 */
void TvShow::addEpisodeReview(EpisodeIdentifier episodeIdentifier, Review review)
{
    seasons[episodeIdentifier.seasonId].episodes[episodeIdentifier.episodeId].addReview(review);
}

/**
 * @brief TvShow::addEpisodeComment Adds the specified comment to the specified episode.
 * @param episodeIdentifier The specific episode to add the comment to.
 * @param comment The comment to add.
 */
void TvShow::addEpisodeComment(EpisodeIdentifier episodeIdentifier, Comment comment)
{
    seasons[episodeIdentifier.seasonId].episodes[episodeIdentifier.episodeId].addComment(comment);
}
