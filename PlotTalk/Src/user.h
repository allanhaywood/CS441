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
    User(QString username, QString firstName, QString lastName, QString email, QString passwordHash);
    User(QString username, QString firstName, QString lastName, QString email, QString passwordHash, bool isAdmin);

    bool isAdmin();

private:
    bool _isAdmin;
};

#endif // USER_H
