#ifndef TESTTVSHOW_H
#define TESTTVSHOW_H

#include <QObject>
#include "../Src/tvshow.h"

class TestTvShow : public QObject
{
    Q_OBJECT
private slots:
    void testDefaultConstructor();
};

#endif // TESTTVSHOW_H
