#ifndef SEASON_H
#define SEASON_H
#include <QString>
#include <Qlist>


class Season
{
public:
    QString seasonNumber;
    QList<int> episodes;

    int numberOfEpisodes();

    Season(QString seasonNumber,QList<int> episodes);
};

#endif // SEASON_H
