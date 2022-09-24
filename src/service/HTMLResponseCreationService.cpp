#include "HTMLResponseCreationService.h"

#include <sstream>

using std::ostringstream;
using std::function;

typedef service::HTMLResponseCreationService cls;

namespace service {

#pragma region Constants

    const char *FORUM_NAME = "Unproblematic <br> Internet Forum";

    const char *HTML_START = "<!DOCTYPE html>\n"
                             "<html lang='en'>\n";
    const char *HTML_END = "</html>";
    const char *BODY_START = "<body>\n";
    const char *BODY_END = "</body>\n";

    const char *LOGIN_TITLE = "Login";
    const char *REGISTER_TITLE = "Register";

    const size_t MAX_POST_COUNT = 1000;
    const char *MAX_POST_QUALIFIER = "999+";

    const char *cls::DEFAULT_TITLE = "Our nice Forum";
    const char *cls::EMPTY_USER_NAME = "";

#pragma endregion

#pragma region Constructors

    HTMLResponseCreationService::HTMLResponseCreationService(CommentDao &commentDao, PostDao &postDao,
                                                             TopicDao &topicDao, UserDao &userDao) :
            _commentDao{commentDao}, _postDao{postDao}, _topicDao{topicDao}, _userDao{userDao} {}

#pragma endregion

#pragma region Static Methods

    string cls::createHead(const string &title) {
        ostringstream buffer{};
        buffer << "<head>\n"
                  "    <meta charset='UTF-8'>\n"
                  "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>\n"
                  "    <title>" << title << "</title>\n"
                                            "    <link rel='stylesheet' href='./css/style.css'>\n"
                                            "    <link rel='stylesheet' href='https://css.gg/heart.css'>\n"
                                            "    <script type='text/javascript' src='./js/main.js'></script>\n"
                                            "</head>\n";
        return buffer.str();
    }

    string cls::createHeader(const string &userName) {
        static const string resultStart{
                "    <header>\n"
                "        <div class='navbar'>\n"
                "            <div class='brand'>\n"
                "                <a href='home.html'>\n"
                "                    <h1>" + string(FORUM_NAME) + "</h1>"
                                                                  "                </a>"
                                                                  "            </div>\n"
                                                                  "            <div class='logout-align'>\n"
                                                                  "            <div class='logout'> \n"
        };
        static const string resultEnd{
                "                </div>\n"
                "            </div>\n"
                "        </div>\n"
                "    </header>\n"
        };
        static const string resultNoUser{resultStart + "<a id='logout'>Login</a>\n" + resultEnd};

        return userName.empty() ? resultNoUser :
               resultStart +
               "                    <span id='username'>Logged in as " + userName + "</span>\n"
                                                                                    "                    <a id='logout'>Log out</a>\n"
               + resultEnd;
    }

    string cls::createFooter() {
        static const string result{
                "    <footer>\n"
                "        <span>\n"
                "            &copy; This is our snode.c project | All Rights Reserved to its respective owners and whatnot\n"
                "            <br>Asteriou Philipp, Boess Leopold, Demelmayr Martin & Zuehlke Samuel\n"
                "        </span>\n"
                "    </footer>\n"};
        return result;
    }

    string
    cls::createAndFillResponse(const string &content, const string &userName, const string &title, bool addHeader) {
        ostringstream buffer{};
        buffer << HTML_START
               << createHead(title)
               << BODY_START;
        if (addHeader) {
            buffer << createHeader(userName);
        }
        buffer << content
               << createFooter()
               << BODY_END
               << HTML_END;
        return buffer.str();
    }

    string cls::createHomeResponse(const vector<Topic> &topics, const vector<int> &postCounts,
                                   const vector<Post> &latestPostsIncCreator, const string &userName) {
        static const string resultHead{
                "    <div id='content' class='container'>\n"
                "        <div class='subforum rainbow-box'>\n"
                "            <div class='subforum-title'>\n"
                "                <div><h2>Topics</h2></div>\n"
        };

        static const string maxPostSpan{string() +
                                        "                    <span class='t-center'>" + MAX_POST_QUALIFIER +
                                        "<br> Posts</span>\n"
        };

        static const string resultEnd{
                "        </div>\n"
                "    </div>\n"
        };

        static const string addTopicForm{
                "                <div class='right'><a id='toggle-topic'><h2 id='toggle-text'>+ Add new Topic</h2></a></div>\n"
                "            </div>\n"
                "            <div id='hide_topic' class='hidden'>\n"
                "                <div class='rainbow-box'>\n"
                "                    <textarea class='title' name='topic-name' rows='1' cols='50' placeholder='Topic Name goes here.'></textarea><br>\n"
                "                    <textarea class='content' name='topic-description' rows='4' cols='50' placeholder='Describe your Topic you want to add.'></textarea><br>\n"
                "                    <input  id='submit-topic' class='submit' type='submit' value='Submit Topic'>\n"
                "                </div>\n"
                "            </div>\n"
        };

        static const string addNoTopicForm{
                "            </div>\n"
        };

        ostringstream contentBuffer{};

        contentBuffer << resultHead
                      << (userName.empty() ? addNoTopicForm : addTopicForm);

        for (int i = 0; i < topics.size(); ++i) {
            const Topic &topic = topics[i];
            const Post &latestPost = latestPostsIncCreator[i];
            contentBuffer <<
                          "            <div class='subforum-row'>\n"
                          "                <div class='subforum-icon subforum-column center'>\n"
                          "                    <i class='gg-heart center'></i>\n"
                          "                </div>\n"
                          "                <div class='subforum-description subforum-column'>\n"
                          "                    <h4 class='t-ov-el'><a href='/topic/" << topic.id << "'>" << topic.title
                          << "</a></h4>\n"
                             "                    <p class='t-ov-el' >" << topic.description << "</p>\n"
                                                                                                "                </div>\n"
                                                                                                "                <div class='subforum-stats subforum-column center'>\n";
            if (postCounts[i] < MAX_POST_COUNT) {
                contentBuffer << "                    <span class='t-center'>" << postCounts[i]
                              << "<br> Posts</span>\n";
            } else {
                contentBuffer << maxPostSpan;
            }
            contentBuffer <<
                          "                </div>\n"
                          "                <div class='subforum-info subforum-column'>\n"
                          "                    <p class='t-ov-el'>Latest by <br> <span class='username'>"
                          << latestPost.creator.userName << "</span><br>" << latestPost.creationDate << "<p>\n"
                                                                                                        "                </div>\n"
                                                                                                        "            </div>\n"
                                                                                                        "            <hr class='topic-hr'>";
        }

        contentBuffer << resultEnd;

        return createAndFillResponse(contentBuffer.str(), userName, DEFAULT_TITLE);
    }

    string cls::createNotFoundResponse(const string &userName) {
        static const string content{
                "    <div class='rainbow-box'>\n"
                "        <span class='error'>404</span>\n"
                "        <h2 class='center'>Page not found</h2>\n"
                "        <p class='center'>We looked all over but I thinkt the page you are looking for does not exist, \n"
                "        <br> nor ever wil to be frank. Who knows honestly? We certainly dont. Maybe you?</p>\n"
                "    </div>\n"};
        static const string title{"404 not found"};
        return createAndFillResponse(content, userName, title);
    }

    string cls::createTopicOverviewResponse(const Topic &topic, const vector<Post> &postsIncCreator,
                                            const vector<int> &postCommentCounts, const string &userName) {
        static const string resultHead{
                "    <div id='content' class='container m-b-100'>\n"
                "        <div class='navigate'>\n"
                "            <span>\n"
        };

        static const string resultMid{
                "            </span>\n"
                "        </div>\n"
                "        <div class='posts-table rainbow-box' >\n"
                "            <div class='table-head'>\n"
                "                <div class='subjects-header'>Posts</div>\n"
        };

        static const string resultEnd{
                "        </div>\n"
                "    </div>\n"
        };

        static const string addTopicForm{
                "                <div class='add-new right'><a id='toggle-post'>+ Add new Post</a></div>\n"
                "            </div>"
                "            <div id='hide-post' class='hidden'>\n"
                "                <div class='rainbow-box'>\n"
                "                    <textarea class='title' name='post-name' rows='1' cols='50' placeholder='Post Header goes here.'></textarea><br>\n"
                "                    <textarea class='content' name='post-description' rows='4' cols='50' placeholder='Here comes the Text of your finely crafted Post.'></textarea><br>\n"
                "                    <input  id='submit-post' class='submit' type='submit' value='Submit Post'>\n"
                "                </div>\n"
                "            </div>\n"
        };

        static const string addNoTopicForm{
                "            </div>\n"
        };

        ostringstream topicHrefBuffer{};
        topicHrefBuffer << "/topic/" << topic.id;
        const string topicHref = topicHrefBuffer.str();

        ostringstream contentBuffer{};
        contentBuffer << resultHead
                      << "                <a href='\\'>Home</a> >> <a href='" << topicHref << "'>" << topic.title
                      << "</a>\n"
                      << resultMid
                      << (userName.empty() ? addNoTopicForm : addTopicForm);

        for (int i = 0; i < postsIncCreator.size(); ++i) {
            const Post &post = postsIncCreator[i];
            contentBuffer <<
                          "            <div class='table-row'>\n"
                          "                <div class='subjects post-title'>\n"
                          "                    <a href='" << topicHref << "/" << post.id << "'>" << post.title
                          << "</a>\n"
                             "                </div>\n"
                             "                <div class='post-user center'>\n"
                             "                    <span>Posted by <br> <span class='username'>" << post.creator.userName
                          << "</span></span>\n"
                             "                </div>\n"
                             "                <div class='replies center'>\n"
                             "                    <span>Re.: " << postCommentCounts[i] << "</span>\n"
                                                                                          "                </div>\n"
                                                                                          "            </div>\n"
                                                                                          "            <hr class='post-hr'>\n";
        }

        contentBuffer << resultEnd;

        return createAndFillResponse(contentBuffer.str(), userName, topic.title);
    }

    string
    cls::createPostOverviewResponse(const Post &postIncCreatorAndTopic, const vector<Comment> &commentsIncCreator,
                                    const string &userName) {
        static const string addCommentForm{
                "        <div>\n"
                "            <h2><a id='toggle-comment'>+ Add comment</a></h2>\n"
                "        </div>\n"
                "        <div id='hide-comment' class='hidden left'>\n"
                "            <div class='rainbow-box'>\n"
                "                <textarea class='content' name='comment-description' rows='4' cols='50'\n"
                "                    placeholder='Here comes the Text of your perfectly proper worded Comment.'></textarea><br>\n"
                "                <input id='submit-comment' class='submit' type='submit' value='Reply'>\n"
                "            </div>\n"
                "        </div>\n"
        };

        static const string commentsHead{
                "        <div class='rainbow-box'>\n"
        };

        static const string commentsEnd{
                "        </div>\n"
                "    </div>\n"
        };

        const Topic &topic = postIncCreatorAndTopic.topic;
        const User &creator = postIncCreatorAndTopic.creator;
        const Post &post = postIncCreatorAndTopic;

        ostringstream contentBuffer{};
        contentBuffer <<
                      "    <div id='content' class='container m-b-100'>\n"
                      "        <div class='navigate'>\n"
                      "            <span>\n"
                      "                <a href='\\'>Home</a> >> "
                      "                <a href='/topic/" << topic.id << "'>" << topic.title << "</a> >> "
                                                                                               "                <a href='/topic/"
                      << topic.id << "/" << post.id << "'>" << post.title << "</a>\n"
                                                                             "            </span>\n"
                                                                             "        </div>\n"
                                                                             "        <div class='rainbow-box'>\n"
                                                                             "            <div class='table-row'>\n"
                                                                             "                <div class='subject-post'>\n"
                                                                             "                    <h2>" << post.title
                      << "</h2> <br>"
                         "                    <div class='text t-ov-el'>\n"
                         "                        by <span class='username'>" << creator.userName << "</span>\n"
                                                                                                     "                    </div>\n"
                                                                                                     "                </div>\n"
                                                                                                     "            </div>"
                                                                                                     "            <hr class='post-hr'>\n"
                                                                                                     "            <div class='table-row'>\n"
                                                                                                     "                <div class='subject-post'>\n"
                                                                                                     "                    <div class='text'>\n"
                      << post.content << "\n"
                                         "                    </div>\n"
                                         "                </div>\n"
                                         "            </div>\n"
                                         "        </div>\n";

        if (!userName.empty()) {
            contentBuffer << addCommentForm;
        }

        contentBuffer << commentsHead;

        for (const Comment &comment: commentsIncCreator) {
            const User &commentCreator = comment.creator;
            contentBuffer <<
                          "            <div class='body'>\n"
                          "                <div class='authors'>\n"
                          "                    <div class='username'>" << commentCreator.userName << "</div>\n"
                                                                                                     "                    <img src='"
                          << commentCreator.avatarURL << "' alt='user avatar'>\n"
                                                         "                </div>\n"
                                                         "                <div class='content'>\n"
                          << comment.content << "\n"
                                                "                </div>\n"
                                                "            </div>\n"
                                                "            <hr class='comment-hr'>\n";
        }

        contentBuffer << commentsEnd;

        return createAndFillResponse(contentBuffer.str(), userName, post.title);
    }

    string cls::createLoginPageResponse() {
        const string content{
                "    <div class='unhidden'>\n"
                "        <div class='login'>\n"
                "            <h1 class='m-t-100'>Login</h1>\n"
                "            <div class='rainbow-box m-b-20'>\n"
                "                <input class='user-login m-b-10' placeholder='Username'></input><br>\n"
                "                <input class='user-login' type='password' placeholder='Password'>\n"
                "            </div>\n"
                "            <input  class='submit' type='submit' value='Login' id='login'>\n"
                "            <div class='m-t-50 t-a-c'>\n"
                "                No account? <a href='register.html'>Register here!</a>\n"
                "            </div>\n"
                "        </div>\n"
                "    </div>"};
        return createAndFillResponse(content, EMPTY_USER_NAME, LOGIN_TITLE, false);
    }

    string cls::createRegisterAccountResponse() {
        const string content{
                "    <div class='unhidden'>\n"
                "        <div class='login'>\n"
                "            <h1 class='m-t-100'>Login</h1>\n"
                "            <div class='rainbow-box m-b-20'>\n"
                "                <input class='user-login m-b-10' placeholder='Set Username'></input>\n"
                "                <input  class='user-login' type='password' placeholder='Password'>\n"
                "                <input  class='user-login' type='password' placeholder='Repeat Password'>\n"
                "            </div>\n"
                "            <input  class='submit' type='submit' value='Sign Up' id='signup'>\n"
                "        </div>\n"
                "    </div>"};
        return createAndFillResponse(content, EMPTY_USER_NAME, REGISTER_TITLE, false);
    }
}

#pragma endregion Methods

#pragma region Instance Methods

void cls::createHomeResponseFromDao(const string &userName, const resCallback &rCallback) {

    auto callback = [this, &rCallback, &userName](vector<Topic> &&topics) {
        size_t topicCount = topics.size();

        vector<int> postCounts(topicCount);
        vector<Post> latestPostsIncCreator(topicCount);

        vector<function<void(int)>> countCallbacks(topicCount);
        vector<function<void(vector<Post> &&)>> postCallbacks(topicCount);
        vector<function<void(User & )>> userCallbacks(topicCount);

        bool fired = false;
        size_t countsCount = 0;
        size_t postsCount = 0;
        for (size_t i = 0; i < topicCount; ++i) {
            const Topic &curTopic = topics[i];

            // fetch post counts
            countCallbacks[i] = [this, i, &countsCount, &fired, &postsCount, topicCount, &rCallback, &topics, &postCounts, &latestPostsIncCreator, &userName]
                    (int count) {
                postCounts[i] = count;
                ++postsCount;
                if (!fired && countsCount == topicCount && postsCount == topicCount) {
                    fired = true;
                    rCallback(this->createHomeResponse(topics, postCounts, latestPostsIncCreator, userName));
                };
            };

            // fetch the latest post creator
            postCallbacks[i] = [this, i, &userCallbacks, &postsCount, &fired, &countsCount, topicCount, &rCallback, &topics, &postCounts, &latestPostsIncCreator, &userName]
                    (vector<Post> &&recentPost) {
                Post &post = recentPost[0];
                userCallbacks[i] = [&post, &postsCount, &fired, &countsCount, topicCount, &rCallback, &topics, &postCounts, &latestPostsIncCreator, &userName]
                        (User &creator) {
                    post.creator = creator;
                    ++postsCount;
                    if (!fired && countsCount == topicCount && postsCount == topicCount) {
                        fired = true;
                        rCallback(createHomeResponse(topics, postCounts, latestPostsIncCreator, userName));
                    };
                };
                this->_postDao.getCreator(post.id, userCallbacks[i]);
            };

            this->_postDao.getRecentPostsOfTopic(curTopic.id, 1, 0, postCallbacks[i]);
        }
    };

    _topicDao.getRecentTopics(-1, 0, callback);
}

void
cls::createTopicOverviewResponseFromDao(unsigned long topicId, const string &userName, const resCallback &rCallback) {
    auto callback = [this, &rCallback, &userName](Topic &topic) {

        auto postsCallback = [this, &rCallback, &topic, &userName](vector<Post> &&posts) {
            size_t postCount = posts.size();
            vector<int> commentCounts;

            vector<function<void(int)>> commentCallbacks(postCount);
            vector<function<void(User & )>> creatorCallbacks(postCount);

            bool fired = false;
            size_t countsCount = 0;
            size_t creatorsCount = 0;
            for (size_t i = 0; i < postCount; ++i) {
                Post &curPost = posts[i];

                // fetch comment counts
                commentCallbacks[i] = [i, &commentCounts, &countsCount, &fired, &creatorsCount, &postCount, &rCallback, &topic, &posts, &userName](
                        int count) {
                    commentCounts[i] = count;
                    ++countsCount;
                    if (!fired && countsCount == postCount && creatorsCount == postCount) {
                        fired = true;
                        rCallback(createTopicOverviewResponse(topic, posts, commentCounts, userName));
                    }
                };
                this->_postDao.getCommentCount(curPost.id, commentCallbacks[i]);

                // fetch creators for posts
                creatorCallbacks[i] = [&curPost, &creatorsCount, &fired, &countsCount, &postCount, &rCallback, &topic, &posts, &commentCounts, &userName](
                        User &user) {
                    curPost.creator = user;
                    ++creatorsCount;
                    if (!fired && countsCount == postCount && creatorsCount == postCount) {
                        fired = true;
                        rCallback(createTopicOverviewResponse(topic, posts, commentCounts, userName));
                    }
                };
                this->_postDao.getCreator(curPost.id, creatorCallbacks[i]);
            }
        };

        _postDao.getRecentPostsOfTopic(topic.id, -1, 0, postsCallback);
    };

    _topicDao.getById(topicId, callback);
}

void
cls::createPostOverviewResponseFromDao(unsigned long postId, const string &userName, const resCallback &rCallback) {
    // TODO: Implement this
}


#pragma endregion
