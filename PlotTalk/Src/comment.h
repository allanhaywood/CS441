#ifndef COMMENT_H
#define COMMENT_H
#include "reaction.h"
#include "reply.h"

class Comment : public Reaction
{
public:
    Comment();
    Comment(int inMediaID, int inUserID, QString inText);
    QVector<Reply> replies;
    void addReply(Reply);
};

#endif // COMME_H
