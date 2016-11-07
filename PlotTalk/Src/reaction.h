/* Reaction base class that is inherited by Comment, Review, and Reply.
 * Provides common functionality for all posts by users on media items.
 * @author Joey Freeman
*/
#ifndef REACTION_H
#define REACTION_H

#include<QString>
#include <QVector>

class Reaction
{
protected: //protected constructors to prevent direct instantiation of base class
    Reaction();
    Reaction(int inMediaID, int inUserID, QString inText);
public:
    int postID; //unique identifier of this post
    int mediaID; //unique idenitifer of episode/season/movie this Reaction appears on
    int userID; //should be initialized to current user
    QString dateTimePosted; //in UTC for now to avoid localization issues
    QString text; //main body of post (or review text)
    void setDateTimePosted();
    ~Reaction();
};

#endif // REACTION_H
