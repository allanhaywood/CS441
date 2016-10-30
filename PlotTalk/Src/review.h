#ifndef REVIEW_H
#define REVIEW_H
#include "reaction.h"

class Review : public Reaction
{
public:
    Review();
    Review(int inMediaID, QString inUserName, QString inText, int inRating);
    int rating;
};

#endif // REVIEW_H
