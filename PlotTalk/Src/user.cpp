/* Implementation of the user class.
 *
 * @author Allan Haywood
 */
#include "user.h"

User::User()
{
    username = "";
    firstName = "";
    lastName = "";
    email = "";
    passwordHash = "";
    _isAdmin = false;
}

User::User(QString username, QString firstName, QString lastName, QString email, QString passwordhash)
{
    this->username = username;
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
    this->passwordHash = passwordhash;
    _isAdmin = false;
}

User::User(QString username, QString firstName, QString lastName, QString email, QString passwordhash, bool isAdmin)
{
    this->username = username;
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
    this->passwordHash = passwordhash;
    _isAdmin = isAdmin;
}

bool User::isAdmin()
{
    return _isAdmin;
}
