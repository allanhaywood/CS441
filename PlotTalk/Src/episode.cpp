#include "episode.h"

Episode::Episode() {

episodeTitle=""; //All Placeholders
mediaId=0;
epSummary="";
}


Episode::Episode(int inMediaID, QString epsummary, QString Title){
  this->mediaId=inMediaID;
    this->epSummary=epsummary;
    this->episodeTitle=Title;
}

/*
 *  @brief destructor
 */
Episode::~Episode() {

}

