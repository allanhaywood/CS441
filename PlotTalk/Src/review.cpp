#include "review.h"

Review::Review()
{

}

Review::Review(int inMediaID, QString inUserName, QString inText, int inRating) : Reaction( inMediaID, inUserName, inText)
{
    rating = inRating;
}
