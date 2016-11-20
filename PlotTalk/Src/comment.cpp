#include "comment.h"




/**
 * @brief Reaction::addReply Adds a Reply to this Comment
 * @param reply The reply to be added
 */
Comment::Comment() : Reaction()
{

}

Comment::Comment(QString username, QString text)
    : Reaction(username, text)
{

}

Comment::Comment(QUuid postUuid, QString username, QString text, QString dateTimePosted)
    : Reaction(postUuid, username, text, dateTimePosted)
{

}

/* Not adding replies yet.
void Comment::addReply(Reply reply)
{
    replies.append(reply);
}

const QVector<Reply> &Comment::inspectReplies()
{
    return replies;
}
*/
