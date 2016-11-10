#ifndef REPLY_H
#define REPLY_H
#include "reaction.h"
#include <QVector>

class Reply : public Reaction
{
public:
    Reply();
    Reply(int inMediaID, int inUserID, QString inText);
private: //prevents nested replies by overriding inheritance. To allow, remove private reply members.
    QVector<Reply> replies;
    void addReply(Reply reply);
};

#endif // REPLY_H
