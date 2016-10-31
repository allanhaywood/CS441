#include "comment.h"

Comment::Comment()
{

}

Comment::Comment(int inMediaID, QString inUserName, QString inText) : Reaction( inMediaID, inUserName, inText)
{

}
