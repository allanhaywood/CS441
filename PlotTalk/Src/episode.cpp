/* The episode class.
 *
 * @author Damien Brantley, Allan Haywood
 */
#include "episode.h"

/**
 * @brief Episode::Episode Creates an episode.
 */
Episode::Episode()
{
    episodeId = 0;
    episodeNumber = 0;
    name = "";
    summary = "";
    reviews = QMap<QString, Review>();
    comments = QList<Comment>();
}

/**

/**
 * @brief Episode::Episode Creates an episode with the provided episodeId and name.
 * @param episodeId The episode ID used by the movie database.
 * @param episodeNumber The episode number used by the movie database.
 * @param name The name as used by the movie database.
 * @param summary The summary for this episode as provided by movie database.
 * @param reviews A qmap of reviews, with the username as the key.
 * @param comments A vector of comments.
 */
Episode::Episode(int episodeId, int episodeNumber, QString name, QString summary, QMap<QString, Review> reviews, QList<Comment> comments)
{
    this->episodeId = episodeId;
    this->episodeNumber = episodeNumber;
    this->name = name;
    this->summary = summary;
    this->reviews = reviews;
    this->comments = comments;
}

void Episode::addReview(Review review)
{
    // Since there can be only a single review per user, this allows an existing
    // review to be overwritten, but the same UUID is kept, so the backend won't end
    // up with multiple reviews per user (as the UUID is a primary key)
    // Basically it treats it like a review edit.
    if ( reviews.contains(review.username) )
    {
        review.postUuid = reviews[review.username].postUuid;
    }

    reviews[review.username] = review;
}

void Episode::addComment(Comment comment)
{
    comments.append(comment);
}

const QList<Review> Episode::inspectReviews()
{
    return reviews.values();
}

const QList<Comment> &Episode::getComments()
{
    return comments;
}

const QList<Comment> Episode::inspectComments()
{
    return getComments();
}

