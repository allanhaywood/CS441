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

/**
 * @brief Episode::addReview Adds the provided review to this episode.
 * @param review The review to add.
 *
 * If a review is already posted by this user, it will be updated with this review.
 * The original UUID will be kept, to keep in sync with the backend.
 */
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

/**
 * @brief Episode::addComment Adds the provided comment to add to this episode.
 * @param comment The comment to add.
 */
void Episode::addComment(Comment comment)
{
    comments.append(comment);
}

/**
 * @brief Episode::operator < Compares to episodes to be able to sort by episode order.
 * @param rhs
 * @return Returns true if this episode is earlier than the rhs episode.
 */
bool Episode::operator<(const Episode &rhs) const
{
    return this->episodeNumber < rhs.episodeNumber;
}

/**
 * @brief Episode::inspectReviews Returns a read only list of reviews.
 * @return A read only list of reviews.
 */
QList<Review> Episode::inspectReviews()
{
    QList<Review> list = reviews.values();
    qSort(list);
    return list;
}

/**
 * @brief Episode::getComments Returns a reference to the comments.
 * @return A reference to the comments for this episode.
 */
const QList<Comment> &Episode::getComments()
{
    qSort(comments);
    return comments;
}

/**
 * @brief Episode::inspectComments Returns a read only list of comments.
 * @return A read only list of comments on this episode.
 */
QList<Comment> Episode::inspectComments()
{
    return getComments();
}
