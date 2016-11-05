/* Header for the User class.
 *
 * @author Allan Haywood
 */
#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:

    QString username;
    QString firstName;
    QString lastName;
    QString email;
    QString passwordHash;

    // TODO: Complete creating User object.
    User();
    User(QString username, QString firstname, QString lastName, QString email, QString passwordHash);

private:
    //Connection connection;
};

#endif // USER_H
