#include "episode.h"

Episode::Episode() {

EpisodeTitle=""; //All Placeholders
mediaId="";
seasonId="";
EpSummary="";
}

Episode::Episode(int inMediaID, Qstring summary, Qstring inText)
{

    this->TvshowID=mediaId;
    this->TvTitle=EpisodeTitle;
    this->Summary=EpSummary;
   //Set rest of attributes here when season class is made
}

