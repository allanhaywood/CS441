#ifndef TESTREPLY_H
#define TESTREPLY_H
#include <QObject>
#include "Reply.h"

class TestReply : public QObject
{
    Q_OBJECT
private slots:
    void TestCreateReply();
};

#endif // TESTREPLY_H
