#ifndef TESTSEASON_H
#define TESTSEASON_H

#include <QObject>
#include <season.h>
#include <Qstring>

class testSeason : public QObject
{
    Q_OBJECT
private slots:
    void testSeasonConstructor();
};

#endif // TESTSEASON_H
