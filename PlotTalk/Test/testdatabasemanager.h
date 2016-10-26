#ifndef TESTDATABASEMANAGER_H
#define TESTDATABASEMANAGER_H

#include <QObject>
#include "databasemanager.h"

class TestDatabaseManager : public QObject
{
    Q_OBJECT
private slots:
    void testGetTvShow();
};

#endif // TESTDATABASEMANAGER_H
