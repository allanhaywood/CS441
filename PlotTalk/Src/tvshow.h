/* Header for the TvShow class.
 *
 * @author Allan Haywood
 */
#ifndef TVSHOW_H
#define TVSHOW_H
#include "season.h"

#include <QString>
#include <QVector>

class TvShow
{

public:
    int showId;
    QString name;
    QString tmdbLink;
    QString graphicLink;

    TvShow();
    TvShow(QString name, QString tmdbLink, QString graphicLink);
    TvShow(int showId, QString name, QString tmdbLink, QString graphicLink);
    TvShow(int showId, QString name, QString tmdbLink, QString graphicLink, QVector<Season> seasons);

    const QVector<Season>& inspectSeasons();
    void addSeason(Season season);
    //void removeSeason(int seasonId);

private:
    QVector<Season> seasons;
};

#endif
