#ifndef REVIEW_H
#define REVIEW_H
#include "reaction.h"
//#include "reply.h"

class Review : public Reaction
{
public:
    int rating; //rating posted by user

    Review();
    Review(QString username, QString text, int rating);
    Review(QUuid postUuid, QString username, QString text, QString dateTimePosted, int rating);

    // Not doing the work on reply yet, work is needed in dashboard to add the functionality.
    //void addReply(Reply reply);
    //const QVector<Reply> &inspectReplies();

private:
    //QVector<Reply> replies;
};

#endif // REVIEW_H
