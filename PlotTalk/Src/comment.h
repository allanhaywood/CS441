/* The header for the comment class.
 *
 * @author Joey Freeman, Allan Haywood
 */
#ifndef COMMENT_H
#define COMMENT_H
#include "reaction.h"
//#include "reply.h"

//#include <QVector>


class Comment : public Reaction
{
public:
    Comment();
    Comment(QString username, QString text);
    Comment(QUuid postUuid, QString username, QString text, QString dateTimePosted);

    // Not doing the work on reply yet, work is needed in dashboard to add the functionality.
    //void addReply(Reply reply);
    //const QVector<Reply> &inspectReplies();

private:
    //QVector<Reply> replies;
};

#endif // COMMENT_H
