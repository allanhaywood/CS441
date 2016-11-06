#ifndef SEASON_H
#define SEASON_H
#include <QString>
#include <Qlist>


class Season
{
public:
    QString seasonNumber;
    Qlist<Episodes> episdoes;

    int nubmberOfEpisodes();

    Season(QString seasonNumber,QList episdoes);
};

#endif // SEASON_H
