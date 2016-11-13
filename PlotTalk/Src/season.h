#ifndef SEASON_H
#define SEASON_H
#include <QString>
#include <Qlist>
#include<episode.h>


class Season
{
public:
    int seasonNumber = 0;
    QList<Episode> episodes;

    Season(int seasonNumber);
    Season();
};

#endif // SEASON_H
