INSERT INTO User (username, password, salt, avatarURL)
VALUES ('Fidi', 'hashstuff', 'pepper', 'urlbuarl'),
       ('Cleo', 'hashstuff', 'pepper', 'urlbuarl'),
       ('Matin', 'hashstuff', 'pepper', 'urlbuarl'),
       ('Sam', 'hashstuff', 'pepper', 'urlbuarl'),
       ('volki', 'hashstuff', 'pepper', 'urlbuarl');

Insert INTO Topic (creatorID, title, description)
VALUES (1, 'Dos and donts of ethnic cleansing 1', 'well take a guess what its about'),
       (2, 'No', 'Get fucked'),
       (3, 'valorant sux ass', 'it do '),
       (4, 'CSS and how to drow circles', 'arts and crafts'),
       (5, 'snodeC', 'the F stands for fun');

INSERT INTO Post (topicID, creatorID, title, content)
VALUES (1, 1, 'Fidi Post', 'Just do it!'),
       (1, 2, 'Cleo post', 'Last weeks cleansing results: it good'),

       (2, 5, 'Volki Post', 'You guys schould look at my github'),
       (2, 1, 'Fidi Post 2', ' no... Get fucked'),

       (3, 3, 'MAtin Post', ' Its not that bad '),
       (3, 4, 'Sam Post', ' it is tho'),

       (4, 5, 'Volki Post 2', ' Art bad cpp good'),
       (4, 2, 'Cleo Post 2', ' suck my ass fucking shit ass artists'),

       (5, 3, 'Matin Post 2', 'volker is no name'),
       (5, 4, 'Sam Post 2', ' Can we close this topic?');

INSERT INTO Comment (postID, creatorID, content)
VALUES (1, 2, 'Cleo Comment'),
       (1, 3, 'MAtin Comment'),
       (1, 4, 'Sam Comment'),

       (2, 5, 'Volki Comment'),
       (2, 1, 'Fidi Comment'),
       (2, 2, 'Cleo Comment'),

       (3, 3, 'MAtin Comment'),
       (3, 4, 'Sam Comment'),
       (3, 5, 'Volki Comment'),

       (4, 1, 'Fidi Comment'),
       (4, 2, 'Cleo Comment'),
       (4, 3, 'MAtin Comment'),

       (5, 4, 'Sam Comment'),
       (5, 5, 'Volki Comment'),
       (5, 1, 'Fidi Comment'),

       (6, 2, 'Cleo Comment'),
       (6, 3, 'MAtin Comment'),
       (6, 4, 'Sam Comment'),

       (7, 5, 'Volki Comment'),
       (7, 1, 'Fidi Comment'),
       (7, 2, 'Cleo Comment'),

       (8, 3, 'MAtin Comment'),
       (8, 4, 'Sam Comment'),
       (8, 5, 'Volki Comment'),

       (9, 1, 'Fidi Comment'),
       (9, 2, 'Cleo Comment'),
       (9, 3, 'MAtin Comment'),

       (10, 4, 'Sam Comment'),
       (10, 5, 'Volki Comment'),
       (10, 1, 'Fidi Comment');






