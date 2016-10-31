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
    QString email;
    QString passwordhash;

    // TODO: Complete creating User object.
    User();
    User(QString username, QString email, QString passwordhash);

private:
    //Connection connection;
};

#endif // USER_H
