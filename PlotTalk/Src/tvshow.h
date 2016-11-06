/* Header for the TvShow class.
 *
 * @author Allan Haywood
 */
#ifndef TVSHOW_H
#define TVSHOW_H
#include <QString>

class TvShow
{
private:


public:
    TvShow(); //Default Constructor
    int showId;  //Identifier for TvShow Primary Key
    QString Title;
    QString Link;
    QString graphicLink;
    int SeasonId; //Foreign Key For Seasons Class
    GetSeason(int seasonid); //Method for grabbing a particular season






//json Connector;

#endif // TVSHOW_H
};
