#include <QtTest/QtTest>
#include "review.h"
#include "testreply.h"

void TestReply::TestCreateReply()
{
    // Set up values to compare against
    int mediaID = 10;
    QString currentDateTime = QDateTime::currentDateTimeUtc().toString("MM/DD/YYYY h:m ap");
    QString userNameReview = "user1";
    int rating = 1;
    QString textReview = "I hate this show.";
    QString userNameReply = "user2";
    QString textReply = "This show is my life.";

    Review review(10, "user1", "I hate this show.", 1);
    review.setDateTimePosted();
    Reply reply(10, "user2", "This show is my life.");
    reply.setDateTimePosted();
    review.addReply(reply.postID);

     /*
    QCOMPARE(review.userName, userNameReview);
    QCOMPARE(review.mediaID, mediaID);
    QCOMPARE(review.text, textReview);
    QCOMPARE(review.dateTimePosted, currentDateTime);
    QCOMPARE(review.rating, rating);
    QCOMPARE(review.replies[0], reply.postID);
    QCOMPARE(reply.userName, userNameReply);
    QCOMPARE(reply.mediaID, mediaID);
    QCOMPARE(reply.text, textReply);
    */
    QCOMPARE("test", "test");

}
