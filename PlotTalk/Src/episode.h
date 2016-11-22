/* The header for the episode class.
 *
 * @author Damien Brantley, Allan Haywood
 */
#ifndef EPISODE_H
#define EPISODE_H
#include<review.h>
#include<comment.h>

#include<QString>
#include<QVector>
#include<QHash>

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

    Episode(int episodeId, int episodeNumber, QString name, QString summary, QHash<QString, Review> reviews, QList<Comment> comments);

    QList<Review> inspectReviews();
    QList<Comment> inspectComments();

    void addReview(Review review);
    void addComment(Comment comment);


private:
    QHash<QString, Review> reviews;
    QList<Comment> comments;

    const QList<Comment> &getComments();
};

#endif // EPISODE_H
