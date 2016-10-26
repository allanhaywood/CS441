#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <connection.h>
#include <jsonconnection.h>

class DatabaseManager : public Connection
{
public:
    DatabaseManager();

    // Connection interface
    void getTvShow(QString name, TvShow &tvShow);

private:
    JsonConnection connection;
};

#endif // DATABASEMANAGER_H
