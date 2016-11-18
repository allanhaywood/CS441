#include "reply.h"

Reply::Reply() : Reaction()
{

}

Reply::Reply(QString username, QString text)
    : Reaction(username, text)
{

}

Reply::Reply(QUuid postUuid, QString username, QString text, QString dateTimePosted)
    : Reaction(postUuid, username, text, dateTimePosted)
{

}

