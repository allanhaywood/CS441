/* The header for the season class.
 *
 * @author Erick Heyl, Allan Haywood
 */
#ifndef SEASON_H
#define SEASON_H
#include <QString>
#include <QVector>

#include "episode.h"

class Season
{
public:
    friend class TvShow;
    int seasonId;
    int seasonNumber;
    QString name;

    Season();
    Season(int seasonId, int seasonNumber, QString name, QHash<int, Episode> episodes);

    QVector<Episode> inspectEpisodes();

    Episode inspectEpisode(int number);
    Episode inspectEpisode(QString name);

    void addEpisode(Episode episode);

private:
    QHash<int, Episode> episodes;
    QHash<int, Episode> &getEpisodes();
    // @throws NotFound
    const Episode &getEpisode(QString name);

    // @throws NotFound
    const Episode &getEpisode(int number);
};

#endif // SEASON_H
