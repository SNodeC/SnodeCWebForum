#Create Database  Forum;

CREATE OR REPLACE TABLE Users
(
    id       INT UNSIGNED AUTO_INCREMENT,
    username VARCHAR(30) not null,
    password VARCHAR(50) not null,
    joinDate timestamp default current_timestamp,
    PRIMARY KEY (id)
);

CREATE OR REPLACE TABLE Subtopic
(
    id         INT UNSIGNED AUTO_INCREMENT,
    creatorID  INT UNSIGNED,
    title      VARCHAR(100) not null,
    createDate timestamp default current_timestamp,
    PRIMARY KEY (id),
    FOREIGN KEY (creatorID) REFERENCES Users (ID)
);

CREATE OR REPLACE TABLE Thread
(
    id         INT UNSIGNED AUTO_INCREMENT,
    subtopicID INT UNSIGNED,
    creatorID  INT UNSIGNED,
    title      VARCHAR(100) not null,
    createDate timestamp default current_timestamp,
    PRIMARY KEY (id),
    FOREIGN KEY (creatorID) REFERENCES Users (ID),
    FOREIGN KEY (subtopicID) REFERENCES Subtopic (ID)
);

CREATE OR REPLACE TABLE Topic
(
    id        INT UNSIGNED AUTO_INCREMENT,
    threadID  INT UNSIGNED,
    posterID  INT UNSIGNED,
    topicText VARCHAR(500) not null,
    postDate  timestamp default current_timestamp,
    PRIMARY KEY (id),
    FOREIGN KEY (threadID) REFERENCES Thread (ID),
    FOREIGN KEY (posterID) REFERENCES Users (ID)
);





