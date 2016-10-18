#include "tvshow.h"

// Default Constructor
TvShow::TvShow()
{
    this->name = "Tvshow name";
    this->imdbLink = "http://www.imdb.com";
    this->graphicLink = "";
}

TvShow::TvShow(QString name, QString imdbLink, QString graphicLink)
{
    this->name = name;
    this->imdbLink = imdbLink;
    this->graphicLink = graphicLink;
    //this->connection = connection;
}
