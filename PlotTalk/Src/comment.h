#ifndef COMMENT_H
#define COMMENT_H
#include "reaction.h"

class Comment : public Reaction
{
public:
    Comment();
    Comment(int inMediaID, QString inUserName, QString inText);
};

#endif // COMME_H
