#include <QtTest/QtTest>
#include <QDebug>
#include "review.h"
#include "testreply.h"

void TestReply::TestCreateReply()
{
    // Set up values to compare against
    int mediaID = 10;
    QString currentDateTime = QDateTime::currentDateTimeUtc().toString("MM/dd/yyyy h:m ap UTC");
    int userIDReview = 1;
    int rating = 1;
    QString textReview = "I hate this show.";
    int userIDReply = 2;
    QString textReply = "This show is my life.";

    Review review(10, 1, "I hate this show.", 1);
    review.setDateTimePosted();
    Reply reply(10, 2, "This show is my life.");
    reply.setDateTimePosted();
    review.addReply(reply);
    Reply postedReply = review.replies[0];

    QCOMPARE(review.userID, userIDReview);
    QCOMPARE(review.mediaID, mediaID);
    QCOMPARE(review.text, textReview);
    QCOMPARE(review.dateTimePosted, currentDateTime);
    QCOMPARE(review.rating, rating);
    QCOMPARE(postedReply.mediaID, reply.mediaID);
    QCOMPARE(postedReply.userID, userIDReply);
    QCOMPARE(postedReply.mediaID, mediaID);
    QCOMPARE(postedReply.text, textReply);
    QCOMPARE(postedReply.dateTimePosted, review.dateTimePosted);
    qDebug() << "Review and reply created at " << reply.dateTimePosted;

}
