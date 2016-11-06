#include "season.h"

/**
 * @brief Season:: a TvShow will have a list of Seasons, and each season will have a list of episodes
 * @param number of season
 * @param a list of episdoes for that season
 */
Season::Season(QString seasonNumber,QList episdoes)
{
    this->seasonNumber = seasonNumber;
    this->episdoes = episdoes;
}
/**
 * @brief Season:: a TvShow will have a list of Seasons, and each season will have a list of episodes
 * @param number of season
 * @return int number of episodes in episdoes list
 */
int Season::numberOfEpisodes()
{
    return this->episdoes.size();

}
