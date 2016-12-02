/* Reaction base class that is inherited by Comment, Review, and Reply.
 * Provides common functionality for all posts by users on media items.
 *
 *  @author Joey Freeman, Allan Haywood
*/
#include "reaction.h"
#include <QDateTime>

/**
 * @brief Reaction::Reaction Creates a default reaction with all values initialized.
 */
Reaction::Reaction()
{
    setUuid();
    username = "";
    text = "";
    setDateTimePosted();
}

/**
 * @brief Reaction::Reaction Creates a reaction with the specified user and text.
 * @param username The username for the reaction.
 * @param text The text content of the reaction.
 *
 * The Uuid is automatically generated and the current timestamp set to dateTimePosted.
 */
Reaction::Reaction(QString username, QString text)
{
    setUuid();
    this->username = username;
    this->text = text;
    setDateTimePosted();
}

/**
 * @brief Reaction::Reaction Constructs a reaction with all provided values.
 * @param postUuid The uuid to use, this will be used instead of generating a new uuid.
 * @param username The username.
 * @param text The text.
 * @param dateTimePosted The datetime posted, used instead of timestamping a new date.
 */
Reaction::Reaction(QUuid postUuid, QString username, QString text, QString dateTimePosted)
{
    this->postUuid = postUuid;
    this->username = username;
    this->text = text;
    this->dateTimePosted = dateTimePosted;
}

/**
 * @brief Reaction::setDateTime Sets the dateTimePosted to the current system time in UTC
 */
void Reaction::setDateTimePosted()
{
    dateTimePosted = QDateTime::currentDateTimeUtc().toString("MM/dd/yyyy h:m ap");
}

/**
 * @brief Reaction::setUuid Generates a new uuid and sets it.
 */
void Reaction::setUuid()
{
    postUuid = QUuid::createUuid();
}

/**
 * @brief Reaction::operator < Compares two reactions by their posted date.
 * @param rhs The other reaction to compare to.
 * @return True if the left reaction is earlier than the right reaction.
 */
bool Reaction::operator<(const Reaction &rhs) const
{
    QDateTime lhsUtcTime = QDateTime::fromString(dateTimePosted, "MM/dd/yyyy h:m ap");
    QDateTime rhsUtcTime = QDateTime::fromString(rhs.dateTimePosted, "MM/dd/yyyy h:m ap");

    return lhsUtcTime < rhsUtcTime;
}
