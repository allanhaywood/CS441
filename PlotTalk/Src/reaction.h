/* Reaction base class that is inherited by Comment, Review, and Reply.
 * Provides common functionality for all posts by users on media items.
 * @author Joey Freeman, Allan Haywood
*/
#ifndef REACTION_H
#define REACTION_H
#include "common.h"

#include <QString>
#include <QUuid>

class Reaction
{
public:
    QUuid postUuid; //unique identifier of this post
    QString username; //should be initialized to current user
    QString text; //main body of post (or review text)
    QString dateTimePosted; //in UTC for now to avoid localization issues

protected: //protected constructors to prevent direct instantiation of base class
    Reaction();
    Reaction(QString username, QString text);
    Reaction(QUuid postUuid, QString username, QString text, QString dateTimePosted);

private:
    void setDateTimePosted();
    void setUuid();
};

#endif // REACTION_H
