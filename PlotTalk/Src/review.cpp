#include "review.h"

Review::Review() : Reaction()
{

}

Review::Review(QString username, QString text, int rating)
    : Reaction(username, text)
{
    this->rating = rating;
}

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
