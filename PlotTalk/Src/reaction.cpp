#include "reaction.h"
#include <QDateTime>

Reaction::Reaction() {

}

Reaction::Reaction(int inMediaID, int inUserID, QString inText) {
    mediaID = inMediaID;
    userID = inUserID;
    text = inText;
}


/**
 * @brief Reaction::setDateTime Sets the dateTimePosted to the current system time in UTC
 */
void Reaction::setDateTimePosted() {
    dateTimePosted = QDateTime::currentDateTimeUtc().toString("MM/dd/yyyy h:m ap UTC");
}


Reaction::~Reaction() {

}
