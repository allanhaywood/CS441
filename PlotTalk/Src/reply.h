#ifndef REPLY_H
#define REPLY_H
#include "reaction.h"

class Reply : public Reaction
{
public:
    Reply();
    Reply(int inMediaID, QString inUserName, QString inText);
};

#endif // REPLY_H
