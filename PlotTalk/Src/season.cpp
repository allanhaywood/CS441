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
    episodes = QVector<Episode>();
}

/**
 * @brief Season::Season Constructs a season with the provided seasonId, name, and episodes.
 * @param seasonId The season ID as specified by the movie database.
 * @param seasonNumber The season number as specified by the movie database.
 * @param name The name of the season as specified by the movie database.
 * @param episodes A vector of episodes to add to the season.
 */
Season::Season(int seasonId, int seasonNumber, QString name, QVector<Episode> episodes)
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
const QVector<Episode>& Season::inspectEpisodes()
{
    return episodes;
}

/**
 * @brief Season::addEpisode Add an episode to this season.
 * @param episode The episode to add.
 */
void Season::addEpisode(Episode episode)
{
    episodes.append(episode);
}

/**
 * @brief Season::getEpisode Return episode with matching name in this season
 * @param QString name
 * @returns matching Episode
 * @throws NotFound exception if no match found
 */
Episode* Season::getEpisode(QString name)
{
    for(int i = 0; i < episodes.size(); i++) {
        if (episodes[i].name == name) {
            return &episodes[i];
        }
    }
    throw NotFound("Unable to retrieve episode " + name + " from season number " + QString::number(seasonNumber));
}
