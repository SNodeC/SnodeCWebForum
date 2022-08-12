# SnodeCWebForum
-.-

# Bitch Ass Volker Project:

## Todo Functionality
- [] Register yourself with Username and Password
- [] Create new subtopic
- [] Create thread in subtopic
- [] Post topics to thread
- [] Read posts of a thread

---

## Techniques to use

- Master-Branch of SNode.C
- Express-Module of SNode.C for Web-API (use webserver implemented during the lecture as a template)
- Use MariaDB as external Database (Maybe it works with my SQL Volker hasn't checked it tho)
    - MariaDB-Module of SNode.C (apps/database/testmariadb.cpp application for further info on usage)
        - Install `libmariadb-dev` using `apt install libmariadb-dev` as `root`
        - Install `mariadb-server` using `apt install mariadb-server` as `root`
- Use cookies for session management
- URL-Queries to select a specific subtopic and thread. (For reading and posting)
- `app.post(...)` for posting to a thread
- Database model that supports functionality

---

## Organization

Deadline of Submission: ***September 30th 18:00***
