/* The reply header.
 *
 * @author Joey Freeman
 *
 * @note: Not currently used.
 */

#ifndef REPLY_H
#define REPLY_H
#include "reaction.h"
#include "common.h"
#include <QVector>
#include <QUuid>

class Reply : public Reaction
{
public:
    Reply();
    Reply(QString username, QString text);
    Reply(QUuid postUuid, QString username, QString text, QString dateTimePosted);
private: //prevents nested replies by overriding inheritance. To allow, remove private reply members.
    void addReply(Reply reply);
    const QVector<Reply> &inspectReplies();
};

#endif // REPLY_H
