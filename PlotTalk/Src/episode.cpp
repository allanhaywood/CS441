/* The episode class.
 *
 * @author Damien Brantley, Allan Haywood
 */
#include "episode.h"

/**
 * @brief Episode::Episode Creates an episode.
 */
Episode::Episode()
{
    episodeId = 0;
    episodeNumber = 0;
    name = "";
}

/**
 * @brief Episode::Episode Creates an episode with the provided episodeId and name.
 * @param episodeId The episode ID used by the movie database.
 * @param episodeNumber The episode number used by the movie database.
 * @param name The name as used by the movie database.
 */
Episode::Episode(int episodeId, int episodeNumber, QString name)
{
    this->episodeId = episodeId;
    this->episodeNumber = episodeNumber;
    this->name = name;
}
