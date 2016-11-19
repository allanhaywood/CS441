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
    int seasonId;
    int seasonNumber;
    QString name;

    Season();
    Season(int seasonId, int seasonNumber, QString name, QVector<Episode> episodes);

    const QVector<Episode>& inspectEpisodes();
    void addEpisode(Episode episode);
    Episode *getEpisode(QString name);

private:
    QVector<Episode> episodes;
};

#endif // SEASON_H
