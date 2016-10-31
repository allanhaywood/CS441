/* Header for the database manager class.
 *
 * @author Allan Haywood
 */
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include "singleton.h"
#include "jsonconnection.h"

#include <QMap>

class DatabaseManager
{
public:
    DatabaseManager();
    DatabaseManager(QString jsonPath);

    // IConnection equivalents, method names are the same, but no need to provide a reference,
    // in addition, instead of return void, it returns a reference of the object.
    TvShow& getTvShow(QString name);

    User& getUser(QString username);

    bool usernameExists(QString username);

    bool emailExists(QString email);

private:
    QMap<QString, TvShow> tvShowMap;
    QMap<QString, User> userMap;

    DatabaseManager(DatabaseManager const&);    // copy constructor hidden
    //DatabaseManager& operator=(DatabaseManager const&);  // assign op hidden

    JsonConnection connection;
};

#endif // DATABASEMANAGER_H
