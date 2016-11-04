#include "user.h"

User::User()
{
    username = "";
    email = "";
    passwordHash = "";
}

User::User(QString username, QString firstName, QString lastName, QString email, QString passwordhash)
{
    this->username = username;
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
    this->passwordHash = passwordhash;
}
