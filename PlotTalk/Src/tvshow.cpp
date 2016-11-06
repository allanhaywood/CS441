/* The TvShow class.
 *
 * @author Allan Haywood
 */
#include "tvshow.h"

/**
 * @brief TvShow::TvShow Default constructor.
 */
TvShow::TvShow()
{
    showId=0;
    Link = "";
    graphicLink = "";

}
/**
 * @brief TvShow::TvShow Represents a tvshow in our application.
 * @param name The name of the tvshow.
 * @param tmdbLink The tmdbLink for this show.
 * @param graphicLink A link to a graphic to be used in our application.
 */
