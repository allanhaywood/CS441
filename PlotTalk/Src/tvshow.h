/* Header for the TvShow class.
 *
 * @author Allan Haywood
 */
#ifndef TVSHOW_H
#define TVSHOW_H
#include <QString>

class TvShow
{
public:
    int showId;
    QString Title;
    QString Link;
    QString graphicLink;
    int SeasonId; //Foreign Key For Seasons Class
    // TODO: Add Seasons once Season class is available.
    TvShow();
    TvShow(int showId,QString Title, QString Link, QString graphicLink);
    GetTvShow();
    GetSeason(SeasonId);



private:

//json Connector};

#endif // TVSHOW_H
