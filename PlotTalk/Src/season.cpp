/* The season class.
 *
 * @author Erick Heyl, Allan Haywood
 */

#include "season.h"
#include "plottalkexceptions.h"

/**
 * @brief Season::Season Constructs an empty season.
 */
Season::Season()
{
    seasonId = 0;
    seasonNumber = 0;
    name = "";
    episodes = QMap<int, Episode>();
}

/**
 * @brief Season::Season Constructs a season with the provided seasonId, name, and episodes.
 * @param seasonId The season ID as specified by the movie database.
 * @param seasonNumber The season number as specified by the movie database.
 * @param name The name of the season as specified by the movie database.
 * @param episodes A map of episodes to add to the season.
 */
Season::Season(int seasonId, int seasonNumber, QString name, QMap<int, Episode> episodes)
{
    this->seasonId = seasonId;
    this->seasonNumber = seasonNumber;
    this->name = name;
    this->episodes = episodes;
}

/**
 * @brief Season::inspectEpisodes Returns a reference to the vector of episodes.
 * @return A reference to the vector of episode.
 *
 * NOTE: Any changes to episodes will not be reflected in the TvShow class.
 */
QVector<Episode> Season::inspectEpisodes()
{
    QVector<Episode> vector = episodes.values().toVector();
    qSort(vector);
    return vector;
}

/**
 * @brief Season::getEpisodes Returns a reference to the map of episodes.
 * @return A reference to the map of episodes.
 *
 * @note The episodeId is the key.
 */
QMap<int, Episode> &Season::getEpisodes()
{
    return episodes;
}

/**
 * @brief Season::addEpisode Add an episode to this season.
 * @param episode The episode to add.
 */
void Season::addEpisode(Episode episode)
{
    episodes.insert(episode.episodeId, episode);
}

bool Season::operator<(const Season &rhs) const
{
    return this->seasonNumber < rhs.seasonNumber;
}

/**
 * @brief Season::getEpisode Return episode with matching name in this season
 * @param QString name
 * @returns matching Episode
 * @throws NotFound exception if no match found
 */
const Episode &Season::getEpisode(QString name)
{
    for (auto &episode : episodes)
    {
        if (episode.name == name)
        {
            return episode;
        }
    }

    throw NotFound("Episode not found:" + name);
}

/**
 * @brief Season::getEpisode Returns a reference to the episode with the indicated number.
 * @param number The episodeNumber
 * @return A reference to an episode with the provided number.
 */
const Episode &Season::getEpisode(int number)
{
    for (auto &episode : episodes)
    {
        if (episode.episodeNumber == number)
        {
            return episode;
        }
    }
    throw NotFound("Unable to retrieve episode " + name + " from season number " + QString::number(seasonNumber));
}

/**
 * @brief Season::inspectEpisode Returns a copy of the episode with the specified number.
 * @param number The episode number.
 * @return A copy of the episode with the specified number.
 */
Episode Season::inspectEpisode(int number)
{
    return getEpisode(number);
}

Episode Season::inspectEpisode(QString name)
{
    return getEpisode(name);
}
