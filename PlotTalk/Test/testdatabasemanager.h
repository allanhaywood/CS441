/* Header for tests for the database manager.
 *
 * @author Allan Haywood
 */
#ifndef TESTDATABASEMANAGER_H
#define TESTDATABASEMANAGER_H

#include <QObject>
#include "databasemanager.h"

class TestDatabaseManager : public QObject
{
    Q_OBJECT
private slots:
    void testGetTvShowDefaultConstructor();
    void TestGetTvShowJsonPathConstructor();
};

#endif // TESTDATABASEMANAGER_H
