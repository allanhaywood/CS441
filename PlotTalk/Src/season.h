/* The header for the season class.
 *
 * @author Erick Heyl, Allan Haywood
 */
#ifndef SEASON_H
#define SEASON_H
#include "episode.h"

#include <QString>
#include <QVector>
#include <QMap>

class Season
{
public:
    friend class TvShow;
    int seasonId;
    int seasonNumber;
    QString name;

    Season();
    Season(int seasonId, int seasonNumber, QString name, QMap<int, Episode> episodes);

    QVector<Episode> inspectEpisodes();

    Episode inspectEpisode(int number);
    Episode inspectEpisode(QString name);

    void addEpisode(Episode episode);

    bool operator<(const Season &rhs) const;

private:
    QMap<int, Episode> episodes;
    QMap<int, Episode> &getEpisodes();
    // @throws NotFound
    const Episode &getEpisode(QString name);

    // @throws NotFound
    const Episode &getEpisode(int number);
};

#endif // SEASON_H
