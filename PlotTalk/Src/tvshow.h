/* Header for the TvShow class.
 *
 * @author Allan Haywood
 */
#ifndef TVSHOW_H
#define TVSHOW_H
#include "season.h"
#include "review.h"
#include "comment.h"
#include "common.h"

#include <QString>
#include <QVector>
#include <QMap>

class TvShow
{

public:
    int showId;
    QString name;
    QString tmdbLink;
    QString graphicLink;

    TvShow();
    TvShow(QString name, QString tmdbLink, QString graphicLink);
    TvShow(int showId, QString name, QString tmdbLink, QString graphicLink);
    TvShow(int showId, QString name, QString tmdbLink, QString graphicLink, QMap<int, Season> seasons);

    const QVector<Season> inspectSeasons();
    QMap<int, Season> &getSeasons();

    void addSeason(Season season);
    Season getSeason(int number);

    void addEpisodeReview(EpisodeIdentifier episodeIdentifier, Review review);
    void addEpisodeComment(EpisodeIdentifier episodeIdentifier, Comment comment);

    // Not implementing replies yet.
    //void addReactionReply(EpisodeIdentifier episodeIdentifier, QUuid reactionUuid, Reply reply);

private:
    QMap<int, Season> seasons;
};

#endif
