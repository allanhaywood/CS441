#ifndef REVIEW_H
#define REVIEW_H
#include "reaction.h"
#include "reply.h"

class Review : public Reaction
{
public:
    Review();
    Review(int inMediaID, int inUserID, QString inText, int inRating);
    int rating; //rating posted by user
    QVector<Reply> replies;
    void addReply(Reply);
};

#endif // REVIEW_H
