/* Header for the TvShow class.
 *
 * @author Allan Haywood
 */
#ifndef TVSHOW_H
#define TVSHOW_H
#include <QString>
#include <QVector>

class TvShow
{

public:

    QString name; //Variable for TvShow Title
    QString tmdbLink;
    QString graphicLink;
    int showId; //Variable for TvShow Primary Key
    int seasonId; //Foreign Key For Seasons Class
    QVector<QString> tvcomments;
    QVector<QString> tvreplies;
    // TODO: Add Seasons once Season class is available.
    TvShow();
    TvShow(QString name, QString tmdbLink, QString graphicLink);

};

#endif
