#include "reaction.h"
#include <QDateTime>

Reaction::Reaction() {

}

Reaction::Reaction(int inMediaID, QString inUserName, QString inText) {
    mediaID = inMediaID;
    userName = inUserName;
    text = inText;
}


/**
 * @brief Reaction::setDateTime Sets the dateTimePosted to the current system time in UTC
 */
void Reaction::setDateTimePosted() {
    dateTimePosted = QDateTime::currentDateTimeUtc().toString("MM/DD/YYYY h:m ap");
}

/**
 * @brief Reaction::addReply Adds the ID of a reply to this Reaction
 */
void Reaction::addReply(int replyID) {
    replies.push_back(replyID);
}


Reaction::~Reaction() {

}
