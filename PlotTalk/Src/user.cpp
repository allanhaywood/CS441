#include "user.h"

User::User()
{
    username = "";
    email = "";
    passwordhash = "";
}

User::User(QString username, QString email, QString passwordhash)
{
    this->username = username;
    this->email = email;
    this->passwordhash = passwordhash;
}
