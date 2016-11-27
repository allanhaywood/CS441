/* Common header, to be shared across project when needed
 *
 * @author Allan Haywood
 */
#ifndef COMMON_H
#define COMMON_H
#include <QString>
#include <QList>

/**
 * @brief The EpisodeIdentifier struct, identifies a specific episode in the datastore.
 */
struct EpisodeIdentifier
{
    int tvShowId;
    int seasonId;
    int episodeId;

    bool operator==(const EpisodeIdentifier &rhs) const
    {
        return ( (tvShowId == rhs.tvShowId) && (seasonId == rhs.seasonId) && (episodeId == rhs.episodeId) );
    }

    // Returns the tvShowId, seasonId, episodeId concatented, with : as the delimiter.
    // This is intended to be used as the key for a dictionary.
    QString getKey() const
    {
        return QString::number(tvShowId) + ":" + QString::number(seasonId) + ":" + QString::number(episodeId);
    }

    // Used for sorting
    bool operator<(const EpisodeIdentifier &rhs) const
    {
        return (this->getKey() < rhs.getKey());
    }

    // Converts an EpisodeIdentifier key into an EpisodeIdentifier.
    static EpisodeIdentifier fromKey(const QString &episodeIdentifierKey)
    {
        QList<QString> keyItems = episodeIdentifierKey.split(":");
        EpisodeIdentifier episodeIdentifier;
        episodeIdentifier.tvShowId = keyItems[0].toInt();
        episodeIdentifier.seasonId = keyItems[1].toInt();
        episodeIdentifier.episodeId = keyItems[2].toInt();

        return episodeIdentifier;
    }

};

#endif // COMMON_H
