#ifndef TESTTVSHOW_H
#define TESTTVSHOW_H

#include <QObject>
#include "tvshow.h"

class TestTvShow : public QObject
{
    Q_OBJECT
private slots:
    void testConstructor();
};

#endif // TESTTVSHOW_H
