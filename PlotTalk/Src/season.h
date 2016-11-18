/* The header for the season class.
 *
 * @author Erick Heyl, Allan Haywood
 */
#ifndef SEASON_H
#define SEASON_H
#include <QString>
#include <QVector>
#include <QMap>

#include "episode.h"

class Season
{
public:
    friend class TvShow;
    int seasonId;
    int seasonNumber;
    QString name;

    Season();
    Season(int seasonId, int seasonNumber, QString name, QMap<int, Episode> episodes);

    const QVector<Episode> inspectEpisodes();
    QMap<int, Episode> &getEpisodes();

    void addEpisode(Episode episode);
    Episode getEpisode(QString name);

private:
    QMap<int, Episode> episodes;
};

#endif // SEASON_H
