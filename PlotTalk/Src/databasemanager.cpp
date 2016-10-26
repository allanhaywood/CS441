#include "databasemanager.h"
#include "jsonconnection.h"

DatabaseManager::DatabaseManager() : connection(":/json/Json/test.json")
{
}

void DatabaseManager::getTvShow(QString name, TvShow &tvShow)
{
    connection.getTvShow(name, tvShow);
}
