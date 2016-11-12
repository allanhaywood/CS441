/* The header for the episode class.
 *
 * @author Damien Brantley, Allan Haywood
 */
#ifndef EPISODE_H
#define EPISODE_H

#include<QString>
#include<QVector>
#include<review.h>
#include<comment.h>

class Episode
{
public:
    int episodeId;
    QString name;

    Episode();
    Episode(int episodeId, QString name);

    // Adding reactions later.
    //Episode(int episodeId, QString name, QVector<Review> reviews, QVector<Comment> comments);

    //QVector<Review> getReviews();
    //QVector<Review> getComments();

    //void addReview();
    //QVector<Review> getComments();


private:
    //QVector<Review> reviews;
    //QVector<Comment> comments;
};

#endif // EPISODE_H
