#ifndef CONNECTION_H
#define CONNECTION_H

#include "tvshow.h"

class Connection
{
public:
    virtual void getTvShow(QString name, TvShow &tvShow) = 0;
private:
};

#endif // CONNECTION_H
