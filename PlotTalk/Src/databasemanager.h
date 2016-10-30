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

    // IConnection equivalent, method names are the same, but no need to provide a reference,
    // in addition, instead of return void, it returns a reference of the object.
    TvShow& getTvShow(QString name);

private:
    QMap<QString, TvShow> tvShowMap;

    DatabaseManager(DatabaseManager const&);    // copy constructor hidden
    //DatabaseManager& operator=(DatabaseManager const&);  // assign op hidden

    JsonConnection jsonConnection;
};

#endif // DATABASEMANAGER_H
