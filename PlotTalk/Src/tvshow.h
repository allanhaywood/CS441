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
    QString name;
    QString tmdbLink;
    QString graphicLink;

    // TODO: Add Seasons once Season class is available.
    TvShow(QString name, QString tmdbLink, QString graphicLink);

    //setConnection(Connection& connection);

private:
    //Connection connection;
};

#endif // TVSHOW_H
