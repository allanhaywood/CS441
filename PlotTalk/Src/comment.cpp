/* Comment class. Used to add comments to an episode.
 *
 * @author Joey Freeman, Allan Haywood
 */
#include "comment.h"

/**
 * @brief Comment::Comment Default constructor for comment.
 */
Comment::Comment() : Reaction()
{

}

/**
 * @brief Comment::Comment Constructs a comment with the provided username and text.
 * @param username The username to include in comment.
 * @param text The actual comment text.
 *
 * This will generate the Uuid and mark the current time dateTimePosted.
 */
Comment::Comment(QString username, QString text)
    : Reaction(username, text)
{

}

/**
 * @brief Comment::Comment Constructs a comment with all provided info.
 * @param postUuid A pre-existing uuid to use for the comment.
 * @param username The username to include in the comment.
 * @param text The actual text of the comment.
 * @param dateTimePosted The datetime comment was posted.
 */
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
