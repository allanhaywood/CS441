/* Header for the jsonconnection class.
 *
 * @author Allan Haywood
 */
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "singleton.h"
#include <iconnection.h>
#include <jsonconnection.h>

class DatabaseManager : public IConnection
{
public:
    DatabaseManager();
    DatabaseManager(QString jsonPath);

    // IConnection interface
    void getTvShow(QString name, TvShow &tvShow);

private:

    DatabaseManager(DatabaseManager const&);    // copy constructor hidden
    DatabaseManager& operator=(DatabaseManager const&);  // assign op hidden

    JsonConnection jsonConnection;
};

#endif // DATABASEMANAGER_H
