#include "season.h"

/**
 * @brief default constructor
 */
Season::Season()
{
}

/**
 * @brief Season:: a TvShow will have a list of Seasons, and each season will have a list of episodes
 * @param number of season
 * @param a list of episodes for that season
 */
Season::Season(int seasonNumber)
{
    this->seasonNumber = seasonNumber;
}
