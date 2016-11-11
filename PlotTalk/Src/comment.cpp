#include "comment.h"

Comment::Comment()
{

}

Comment::Comment(int inMediaID, int inUserID, QString inText) : Reaction( inMediaID, inUserID, inText)
{

}

/**
 * @brief Reaction::addReply Adds a Reply to this Comment
 * @param reply The reply to be added
 */
void Comment::addReply(Reply reply) {
    replies.push_back(reply);
}
