#ifndef TESTJSONCONNECTION_H
#define TESTJSONCONNECTION_H

#include <QObject>
#include "jsonconnection.h"

class TestJsonConnection : public QObject
{
    Q_OBJECT
private slots:
    void testGetTvShow();
};

#endif // TESTJSONCONNECTION_H
