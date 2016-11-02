CREATE DATABASE db_name;

/*CREATE Queries:
Format for general inserts	_Val just means it’s variable*/

/* *****So all the IDs for each table are NOT GOING to be AUTO_INCREMENT...
	****They will be IDs from the movie database*/

/*ACTUALLY, AUTO_INCREMENT for the WatchedMovie & WatchedEpisode tables...I think*/
	
CREATE TABLE Users(
	UserID		INTEGER		NOT NULL	AUTO_INCREMENT,
	Username 	VARCHAR(20) NOT NULL	UNIQUE,
	Password 	VARCHAR(20)	NOT NULL	DEFAULT ' ',
	Email 		VARCHAR(40)	NOT NULL	DEFAULT ' ', 
	PRIMARY KEY(UserID)
);


CREATE TABLE TvShow(
	TvshowID		INTEGER		NOT NULL	UNIQUE,
	/*Not sure what value we want for title, link, graphic link throughout tables*/
	TvTitle			VARCHAR(40)	NOT NULL	DEFAULT 'No TvShow Title',
	TvLink			VARCHAR(400)NOT NULL	DEFAULT ' ',
	TvGraphicLink	VARCHAR(400)NOT NULL	DEFAULT ' ',
	PRIMARY KEY(TvshowID)
);

CREATE TABLE Movie(
	MovieID				INTEGER		NOT NULL	UNIQUE,
	MovieTitle			VARCHAR(40)	NOT NULL	DEFAULT 'No Movie Title',
	MovieLink			VARCHAR(400)NOT NULL	DEFAULT ' ',
	MovieGraphicLink	VARCHAR(400)NOT NULL	DEFAULT ' ',
	PRIMARY KEY(MovieID)
);

CREATE TABLE Season(
	SeasonID	INTEGER		NOT NULL	UNIQUE,
	TvShowID	INTEGER		NOT NULL	DEFAULT 0,
	SeasonTitle	VARCHAR(40)	NOT NULL	DEFAULT 'No Season Title',
	/*to come think of it, will there be a link and graphiclink for Season???*/
	PRIMARY KEY(SeasonID),
	FOREIGN KEY (TvshowID)	REFERENCES TvShow(TvShowID)
);

CREATE TABLE Episode(
	EpisodeID		INTEGER		NOT NULL	UNIQUE,
	SeasonID		INTEGER		NOT NULL	DEFAULT 0,
	EpisodeTitle	VARCHAR(40)	NOT NULL	DEFAULT 'No Episode Title',
	/*need summary attribute*/
	Summary			VARCHAR(4000)	NOT NULL	DEFAULT 'Not available',
	/*here too, will there be a link and graphiclink for Episode???*/
	PRIMARY KEY(EpisodeID),
	FOREIGN KEY (SeasonID)	REFERENCES Season(SeasonID)
);

CREATE TABLE Review(
	ReviewID		INTEGER		NOT NULL	AUTO_INCREMENT,
	UserID			INTEGER		NOT NULL	DEFAULT 0,
	EpisodeID		INTEGER		NOT NULL	DEFAULT 0,
	Rating			INTEGER		NOT NULL,	DEFAULT 0,
	ReviewText		VARCHAR(4000)	NOT NULL, DEFAULT "No text",
	ReviewTime		TIME		NOT NULL,
	/*still need to think about this specfic entity*/
	/*Not sure if we want Review and Comment to be seperate*/
	/*OR do we want Reaction to a Reaction concept/relatioship*/
	PRIMARY KEY(ReactionID),
	FOREIGN KEY (UserID)	REFERENCES Users(UserID),
	FOREIGN KEY (EpisodeID)	REFERENCES Episode(EpisodeID)
);

CREATE TABLE Comment(
	CommentID	INTEGER			NOT NULL	AUTO_INCREMENT
	UserID		INTEGER			NOT NULL	DEFAULT 0,
	EpisodeID	INTEGER			NOT NULL	DEFAULT 0,
	CommentText	VARCHAR(4000)	NOT NULL, 	DEFAULT "No comment",
	ReviewTime	TIME		NOT NULL,
	PRIMARY KEY(CommentID),
	FOREIGN KEY (UserID)	REFERENCES Users(UserID),
	FOREIGN KEY (EpisodeID)	REFERENCES Episode(EpisodeID)
);

CREATE TABLE ReviewReplies(
	ReviewRepliesID	INTEGER			NOT NULL	AUTO_INCREMENT
	ReviewID		INTEGER			NOT NULL	DEFAULT 0,
	UserID			INTEGER			NOT NULL	DEFAULT 0,
	RevReplyText	VARCHAR(4000)	NOT NULL 	DEFAULT "No reply to review",
	RevReplyTime	TIME			NOT NULL,
	PRIMARY KEY(ReviewRepliesID),
	FOREIGN KEY (ReviewID)	REFERENCES Review(ReviewID),
	FOREIGN KEY (UserID)	REFERENCES Users(UserID)
);

CREATE TABLE CommentReplies(
	CommentRepliesID	INTEGER	NOT NULL	AUTO_INCREMENT
	ReviewID			INTEGER			NOT NULL	DEFAULT 0,
	UserID				INTEGER			NOT NULL	DEFAULT 0,
	ComReplyText		VARCHAR(4000)	NOT NULL 	DEFAULT "No reply to review",
	ComReplyTime		TIME			NOT NULL,
	PRIMARY KEY(CommentRepliesID),
	FOREIGN KEY (ReviewID)	REFERENCES Review(ReviewID),
	FOREIGN KEY (UserID)	REFERENCES Users(UserID)
);

/*RELATIONSHIP TABLES*/

CREATE TABLE WatchedMovie(
	WacthedMovieID	INTEGER		NOT NULL	AUTO_INCREMENT,
	UserID			INTEGER		NOT NULL	DEFAULT 0,
	MovieID			INTEGER		NOT NULL	DEFAULT 0,
	PRIMARY KEY(WacthedMovieID),
	FOREIGN KEY (UserID)	REFERENCES Users(UserID),
	FOREIGN KEY (MovieID)	REFERENCES Movie(MovieID)
);

CREATE TABLE WacthedEpisode(
	WatchedEpisodeID	INTEGER		NOT NULL	AUTO_INCREMENT,
	UserID				INTEGER		NOT NULL	DEFAULT 0,
	EpisodeID	 		INTEGER		NOT NULL	DEFAULT 0,
	PRIMARY KEY(WatchedEpisodeID),
	FOREIGN KEY (UserID)	REFERENCES Users(UserID)
	FOREIGN KEY (EpisodeID)	REFERENCES Episode(EpisodeID)
);










