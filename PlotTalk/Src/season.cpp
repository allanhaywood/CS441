#include "season.h"

/**
 * @brief Season:: a TvShow will have a list of Seasons, and each season will have a list of episodes
 * @param number of season
 * @param a list of episodes for that season
 */
Season::Season(QString seasonNumber, QList<int> episodes)
{
    this->seasonNumber = seasonNumber;
    this->episodes = episodes;
}
/**
 * @brief Season:: a TvShow will have a list of Seasons, and each season will have a list of episodes
 * @param number of season
 * @return int number of episodes in episdoes list
 */
int Season::numberOfEpisodes()
{
    return episodes.size();

}
