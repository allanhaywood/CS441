/* Common header, to be shared across project when needed
 *
 * @author Allan Haywood
 */
#ifndef COMMON_H
#define COMMON_H

/**
 * @brief The EpisodeIdentifier struct, identifies a specific episode in the datastore.
 */
struct EpisodeIdentifier
{
    int tvShowId;
    int seasonId;
    int episodeId;
};

#endif // COMMON_H
