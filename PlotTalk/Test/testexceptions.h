#ifndef TESTEXCEPTIONS_H
#define TESTEXCEPTIONS_H
#include "plottalkexceptions.h"

#include <QObject>

class testExceptions : public QObject
{
    Q_OBJECT
private slots:
    void testExceptionThrow();
};

#endif // TESTEXCEPTIONS.H
