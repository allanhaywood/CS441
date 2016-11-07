#include "review.h"

Review::Review()
{

}

Review::Review(int inMediaID, int inUserID, QString inText, int inRating) : Reaction( inMediaID, inUserID, inText)
{
    rating = inRating;
}

/**
 * @brief Reaction::addReply Adds a Reply to this Review
 * @param reply The reply to be added
 */
void Review::addReply(Reply reply) {
    replies.push_back(reply);
}
