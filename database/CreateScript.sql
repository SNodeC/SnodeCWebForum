#Create Database  Forum;

CREATE OR REPLACE TABLE User
(
    id        INT UNSIGNED AUTO_INCREMENT,
    username  VARCHAR(30) not null,
    password  VARCHAR(50) not null,
    salt      VARCHAR(20) not null,
    avatarURL VARCHAR(50) not null,
    creationDate  datetime default NOW(),
    PRIMARY KEY (id)
);

CREATE OR REPLACE TABLE Topic
(
    id           INT UNSIGNED AUTO_INCREMENT,
    creatorID    INT UNSIGNED,
    title        VARCHAR(100) not null,
    description  VARCHAR(500) not null,
    creationDate datetime default NOW(),
    PRIMARY KEY (id),
    FOREIGN KEY (creatorID) REFERENCES User (ID)
);

CREATE OR REPLACE TABLE Post
(
    id           INT UNSIGNED AUTO_INCREMENT,
    topicID      INT UNSIGNED,
    creatorID    INT UNSIGNED,
    title        VARCHAR(100) not null,
    content      VARCHAR(500) not null,
    creationDate datetime default NOW(),
    PRIMARY KEY (id),
    FOREIGN KEY (creatorID) REFERENCES User (ID),
    FOREIGN KEY (topicID) REFERENCES Topic (ID)
);

CREATE OR REPLACE TABLE Comment
(
    id           INT UNSIGNED AUTO_INCREMENT,
    postID       INT UNSIGNED,
    posterID     INT UNSIGNED,
    content      VARCHAR(500) not null,
    creationDate datetime default NOW(),
    PRIMARY KEY (id),
    FOREIGN KEY (postID) REFERENCES Post (ID),
    FOREIGN KEY (posterID) REFERENCES User (ID)
);





