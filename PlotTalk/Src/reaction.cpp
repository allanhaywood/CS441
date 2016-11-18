#include "reaction.h"
#include <QDateTime>

Reaction::Reaction()
{
    setUuid();
    username = "";
    text = "";
    setDateTimePosted();
}

Reaction::Reaction(QString username, QString text)
{
    setUuid();
    this->username = username;
    this->text = text;
    setDateTimePosted();
}

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
    dateTimePosted = QDateTime::currentDateTimeUtc().toString("MM/dd/yyyy h:m ap UTC");
}

void Reaction::setUuid()
{
    postUuid = QUuid::createUuid();
}
