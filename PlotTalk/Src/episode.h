#ifndef EPISODE_H
#define EPISODE_H

#include<QString>
#include<QVector>
#include<review.h>
#include<comment.h>

class Episode
{
protected:
     //constructor


public:
    Episode();
    Episode(int inMediaID, QString epsummary, QString Title);
    int mediaId; //Placeholder for Episode Unique Id
    int seasonId; //For Season Unique Id
    QString episodeTitle; //For Episode Title from Database
    QString epSummary;
    QVector<Review> reviews;
    QVector<Comment> comments;
    ~Episode();

//Set connection Object
//Placeholder for more methods

    void getEpisode(int EpKey); //Method of retreving all Episode Data from The Database based on the Key it is Given
    void getSeason(int seasonKey); //Get the Season based on which key is passed into this method
};

#endif //EPISODE_H
