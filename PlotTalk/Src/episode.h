/* The header for the episode class.
 *
 * @author Damien Brantley, Allan Haywood
 */
#ifndef EPISODE_H
#define EPISODE_H

#include<QString>
#include<QVector>
#include<QMap>
#include<review.h>
#include<comment.h>

class Episode
{
public:
    friend class TvShow;
    friend class Season;
    int episodeId;
    int episodeNumber;
    QString name;
    QString summary;

    Episode();
    Episode(int episodeId, int episodeNumber, QString name, QString summary);

    Episode(int episodeId, int episodeNumber, QString name, QString summary, QMap<QString, Review> reviews, QList<Comment> comments);

    void addReview(Review review);
    void addComment(Comment comment);

    const QList<Review> inspectReviews();
    const QList<Comment> &getComments();

private:
    QMap<QString, Review> reviews;
    QList<Comment> comments;
};

#endif // EPISODE_H
