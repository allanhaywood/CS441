/* The Review class.
 *
 * @author Joey Freeman, Allan Haywood
 */
#include "review.h"

/**
 * @brief Review::Review A default constructor with all values initialized.
 */
Review::Review() : Reaction()
{
    rating = 0;
}

/**
 * @brief Review::Review Creates a review with the specified values.
 * @param username The username for the review.
 * @param text The text for the review.
 * @param rating The rating for the review.
 *
 * @note The UUID and Timestamp will be automatically created.
 */
Review::Review(QString username, QString text, int rating)
    : Reaction(username, text)
{
    this->rating = rating;
}

/**
 * @brief Review::Review Creates a review with the specified values.
 * @param postUuid The UUID to use.
 * @param username The username for the review.
 * @param text The text for the review.
 * @param dateTimePosted The timestamp for this review.
 * @param rating The rating for the review.
 *
 * @note The UUID and Timestamp are NOT automatically created, the provided ones are used.
 */
Review::Review(QUuid postUuid, QString username, QString text, QString dateTimePosted, int rating)
    : Reaction(postUuid, username, text, dateTimePosted)
{
    this->rating = rating;
}

/*
 * Not adding replies yet.
void Review::addReply(Reply reply)
{
    replies.append(reply);
}

const QVector<Reply> &Review::inspectReplies()
{
    return replies;
}
*/
