#ifndef TVSHOW_H
#define TVSHOW_H
#include <QString>

class TvShow
{
public:
    QString name;
    QString imdbLink;
    QString graphicLink;

    // TODO: Add Seasons once Season class is available.

    TvShow();

    //TvShow(QString name, QString imdbLink, QString graphicLink, Connection& connection);
    TvShow(QString name, QString imdbLink, QString graphicLink);

    //setConnection(Connection& connection);

private:
    //Connection& connection;

};

#endif // TVSHOW_H
