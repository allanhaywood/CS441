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

    const QVector<Episode> inspectEpisodes();
    QHash<int, Episode> &getEpisodes();

    void addEpisode(Episode episode);

    // @throws NotFound
    Episode &getEpisode(QString name);

    // @throws NotFound
    Episode &getEpisode(int number);

    Episode inspectEpisode(int number);

private:
    QHash<int, Episode> episodes;
};

#endif // SEASON_H
