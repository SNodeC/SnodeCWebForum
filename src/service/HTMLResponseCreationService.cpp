#include "HTMLResponseCreationService.h"
#include "../utils/Utils.h"

#include <memory>
#include <sstream>

using std::ostringstream;
using std::function;
using std::shared_ptr;
using std::make_shared;


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
    const vector<std::string> cls::EMPTY_VECTOR;

#pragma endregion

#pragma region Constructors

    HTMLResponseCreationService::HTMLResponseCreationService(CommentDao &commentDao, PostDao &postDao,
                                                             TopicDao &topicDao) :
            _commentDao{commentDao}, _postDao{postDao}, _topicDao{topicDao} {}

#pragma endregion

#pragma region Static Methods

    std::string cls::createHead(const string &title) {
        ostringstream buffer{};
        buffer << "<head>\n"
                  "    <meta charset='UTF-8'>\n"
                  "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>\n"
                  "    <title>" << title << "</title>\n"
                                            "    <link rel='stylesheet' href='/css/style.css'>\n"
                                            "    <link rel='stylesheet' href='https://css.gg/heart.css'>\n"
                                            "    <link rel='stylesheet' href='https://css.gg/spinner-alt.css'>\n"
                                            "    <script type='text/javascript' src='/js/main.js'></script>\n"
                                            "</head>\n";
        return buffer.str();
    }

    std::string cls::createHeader(const string &userName) {
        static const string resultStart{
                "    <header>\n"
                "        <div class='navbar'>\n"
                "            <div class='brand'>\n"
                "                <a href='/'>\n"
                "                    <h1>" + std::string(FORUM_NAME) + "</h1>"
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
        static const string resultNoUser{resultStart + "<a id='logout' href='/login/' >Login</a>\n" + resultEnd};

        return userName.empty() ? resultNoUser :
               resultStart +
               "                    <span id='username'>Logged in as " + Utils::escapeForHTML(userName) + "</span>\n"
                                                                                                          "                    <a id='logout'>Log out</a>\n"
               + resultEnd;
    }

    std::string cls::createFooter() {
        static const string result{
                "    <footer>\n"
                "        <span>\n"
                "            &copy; This is our snode.c project | All Rights Reserved to its respective owners and whatnot\n"
                "            <br>Asteriou Philipp, Boess Leopold, Demelmayr Martin & Zuehlke Samuel\n"
                "        </span>\n"
                "    </footer>\n"};
        return result;
    }

    std::string
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

    std::string cls::createHomeResponse(const vector<Topic> &topics, const vector<int> &postCounts,
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
                "            <form id='hide-topic' class='hidden m-30' action='' method='Post'>\n"
                "                <div class='rainbow-box w-100p'>\n"
                "                    <textarea id='topic-title' class='title' name='topic-name' rows='1' cols='50' placeholder='Topic Name goes here.' minlength='3' maxlength='100'></textarea><br>\n"
                "                    <textarea id='topic-content' class='content' name='topic-description' rows='4' cols='50' placeholder='Describe your Topic you want to add.' minlength='1' maxlength='500'></textarea><br>\n"
                "                </div>\n"
                "                <input  id='submit-topic' class='submit' type='submit' value='Submit Topic'>\n"
                "                <div class='w-100p m-t-10'>\n"
                "                    <div id='error-anchor' class='error'></div>\n"
                "                    <div id='warning-anchor' class='warning'></div>\n"
                "                    <div id='info-anchor' class='info'></div>\n"
                "                </div>"
                "            </form>\n"
                "            <hr class='topic-hr'>"
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
                          "                    <h4 class='t-ov-el'><a href='/t/" << topic.id << "'>"
                          << Utils::escapeForHTML(topic.title) << "</a></h4>\n"
                                                                  "                    <p class='t-ov-el'>"
                          << Utils::escapeForHTML(topic.description) << "</p>\n"
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
                          << Utils::escapeForHTML(latestPost.creator.userName) << "</span><br>"
                          << Utils::escapeForHTML(latestPost.creationDate) << "<p>\n"
                                                                              "                </div>\n"
                                                                              "            </div>\n"
                                                                              "            <hr class='topic-hr'>";
        }

        contentBuffer << resultEnd;

        return createAndFillResponse(contentBuffer.str(), userName, DEFAULT_TITLE);
    }

    std::string cls::createNotFoundResponse(const string &userName) {
        static const string content{
                "    <div id='content' class='content'>\n"
                "        <h1>404</h1>"
                "        <h2 class='center'>Page not found</h2>\n"
                "        <p class='center'>We looked all over but I think the page you are looking for does not exist, \n"
                "        <br> nor ever wil to be frank. Who knows honestly? We certainly dont. Maybe you?</p>\n"
                "    </div>\n"};
        static const string title{"404 not found"};
        return createAndFillResponse(content, userName, title);
    }

    std::string cls::createTopicOverviewResponse(const Topic &topic, const vector<Post> &postsIncCreator,
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
                "                <div class='subjects-header'>"
                "                    <h2>Posts</h2>"
                "                </div>\n"
        };

        static const string resultEnd{
                "        </div>\n"
                "    </div>\n"
        };

        static const string addPostForm{ //TODO SAME NAME ?
                "                <div class='add-new right'><a id='toggle-post'>+ Add new Post</a></div>\n"
                "            </div>"
                "            <form id='hide-post' class='hidden m-30' action='' method='Post'>\n"
                "                <div class='rainbow-box w-100p'>\n"
                "                    <textarea id='post-title' class='title' name='post-name' rows='1' cols='50' placeholder='Post Header goes here.' minlength='3' maxlength='100'></textarea><br>\n"
                "                    <textarea id='post-content' class='content' name='post-description' rows='4' cols='50' placeholder='Here comes the Text of your finely crafted Post.' minlength='1' maxlength='500'></textarea>\n"
                "                </div>\n"
                "                <input  id='submit-post' class='submit' type='submit' value='Submit Post'>\n"
                "                <div class='w-100p m-t-10'>\n"
                "                    <div id='error-anchor' class='error'></div>\n"
                "                    <div id='warning-anchor' class='warning'></div>\n"
                "                    <div id='info-anchor' class='info'></div>\n"
                "                </div>"
                "            </form>\n"
                "            <hr class='post-hr'>\n"
        };

        static const string addNoPostForm{
                "            </div>\n"
        };

        ostringstream topicHrefBuffer{};
        topicHrefBuffer << "/t/" << topic.id;
        const string topicHref = topicHrefBuffer.str();

        ostringstream contentBuffer{};
        contentBuffer << resultHead
                      << "                <a href='/'>Home</a> >> <a href='" << topicHref << "'>"
                      << Utils::escapeForHTML(topic.title) << "</a>\n"
                      << resultMid
                      << (userName.empty() ? addNoPostForm : addPostForm);

        for (int i = 0; i < postsIncCreator.size(); ++i) {
            const Post &post = postsIncCreator[i];
            contentBuffer <<
                          "            <div class='table-row'>\n"
                          "                <div class='subjects post-title'>\n"
                          "                    <a href='" << topicHref << "/" << post.id << "'>"
                          << Utils::escapeForHTML(post.title) << "</a>\n"
                                                                 "                </div>\n"
                                                                 "                <div class='post-user center'>\n"
                                                                 "                    <span>Posted by <br> <span class='username'>"
                          << Utils::escapeForHTML(post.creator.userName) << "</span></span>\n"
                                                                            "                </div>\n"
                                                                            "                <div class='replies center'>\n"
                                                                            "                    <span>Re.: "
                          << postCommentCounts[i] << "</span>\n"
                                                     "                </div>\n"
                                                     "            </div>\n"
                                                     "            <hr class='post-hr'>\n";
        }

        contentBuffer << resultEnd;

        return createAndFillResponse(contentBuffer.str(), userName, topic.title);
    }

    std::string
    cls::createPostOverviewResponse(const Post &postIncCreatorAndTopic, const vector<Comment> &commentsIncCreator,
                                    const string &userName) {
        static const string addCommentForm{
                "        <div>\n"
                "            <h2><a id='toggle-comment'>+ Add comment</a></h2>\n"
                "        </div>\n"
                "        <form id='hide-comment' class='hidden m-b-10 m-30' action='' method='Post'>\n"
                "            <div class='rainbow-box w-100p'>\n"
                "                <textarea id='comment-content' class='content' name='comment-description' rows='4' cols='50'\n"
                "                    placeholder='Here comes the Text of your perfectly proper worded Comment.' minlength='1' maxlength='500'></textarea>\n"
                "            </div>\n"
                "            <input id='submit-comment' class='submit' type='submit' value='Reply'>\n"
                "            <div class='w-100p m-t-10'>\n"
                "                <div id='error-anchor' class='error'></div>\n"
                "                <div id='warning-anchor' class='warning'></div>\n"
                "                <div id='info-anchor' class='info'></div>\n"
                "            </div>"
                "        </form>\n"
        };

        static const string addNoCommentForm{
                "        <div class='min-h-1 m-b-20'></div>\n"
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
                      "                <a href='/'>Home</a> >> "
                      "                <a href='/t/" << topic.id << "'>" << Utils::escapeForHTML(topic.title)
                      << "</a> >> "
                         "                <a href='/t/" << topic.id << "/" << post.id << "'>"
                      << Utils::escapeForHTML(post.title) << "</a>\n"
                                                             "            </span>\n"
                                                             "        </div>\n"
                                                             "        <div class='rainbow-box'>\n"
                                                             "            <div class='table-row'>\n"
                                                             "                <div class='subject-post'>\n"
                                                             "                    <h2>" << post.title << "</h2>\n"
                                                                                                         "                    <div class='text t-ov-el'>\n"
                                                                                                         "                        by <span class='username'>"
                      << Utils::escapeForHTML(creator.userName) << "</span>\n"
                                                                   "                    </div>\n"
                                                                   "                </div>\n"
                                                                   "            </div>"
                                                                   "            <hr class='post-hr'>\n"
                                                                   "            <div class='table-row'>\n"
                                                                   "                <div class='subject-post'>\n"
                                                                   "                    <div class='text desc-post'>\n"
                      << Utils::escapeForHTML(post.content) << "\n"
                                                               "                    </div>\n"
                                                               "                </div>\n"
                                                               "            </div>\n"
                                                               "        </div>\n";

        if (!userName.empty()) {
            contentBuffer << addCommentForm;
        } else {
            contentBuffer << addNoCommentForm;
        }

        contentBuffer << commentsHead;

        for (const Comment &comment: commentsIncCreator) {
            const User &commentCreator = comment.creator;
            contentBuffer <<
                          "            <div class='body'>\n"
                          "                <div class='authors'>\n"
                          "                    <div class='username t-a-c t-ov-el'>"
                          << Utils::escapeForHTML(commentCreator.userName) << "</div>\n"
                                                                              "                    <img src='"
                          << commentCreator.avatarURL << "' alt='user avatar'>\n"
                                                         "                </div>\n"
                                                         "                <div class='content'>\n"
                          << Utils::escapeForHTML(comment.content) << "\n"
                                                                      "                </div>\n"
                                                                      "            </div>\n"
                                                                      "            <hr class='comment-hr'>\n";
        }

        contentBuffer << commentsEnd;

        return createAndFillResponse(contentBuffer.str(), userName, post.title);
    }

    std::string cls::createLoginPageResponse(const vector<std::string> &errors, const vector<std::string> &warnings,
                                             const vector<std::string> &infos) {
        static const string resultHead{
                "    <div id='content'>\n"
                "        <div class='unhidden'>\n"
                "            <form id='login-form' class='login' action='' method='Post'>\n"
                "                <h1 class='m-b-50'>Login</h1>\n"
                "                <div class='rainbow-box m-b-10'>\n"
                "                    <input id='login-username' class='user-login' placeholder='Username' required></input>\n"
                "                    <hr class='post-hr'>\n"
                "                    <input id='login-password' class='user-login' type='password' placeholder='Password' required>\n"
                "                </div>\n"
                "                <div class='m-b-10 min-h-1'>\n"
        };

        static const string resultEnd{
                "                </div>\n"
                "                <input class='submit' type='submit' value='Login' id='signin'>\n"
                "                <div class='m-t-40 t-a-c'>\n"
                "                    No account? <a href='/register/'>Register here!</a>\n"
                "                </div>"
                "                <div class='m-t-10 t-a-c w-100p'> "
                "                    &lt;&lt; <a href='javascript:history.back()'>Back</a>\n"
                "                </div>"
                "            </form>\n"
                "        </div>\n"
                "    </div>\n"
        };

        static const string errorHead{
                "                <div id='error-anchor' class='error'>"
        };

        static const string warningHead{
                "                <div id='warning-anchor' class='warning'>"
        };

        static const string infoHead{
                "                <div id='info-anchor' class='info'>"
        };

        static const string msgEnd{
                "</div>\n"
        };

        ostringstream contentBuffer{};

        contentBuffer << resultHead;

        contentBuffer << errorHead;
        for (const string &error: errors) {
            contentBuffer << "<span>" << Utils::escapeForHTML(error) << "</span><br>\n";
        }
        contentBuffer << msgEnd;

        contentBuffer << warningHead;
        for (const string &warning: warnings) {
            contentBuffer << "<span>" << Utils::escapeForHTML(warning) << "</span><br>\n";
        }
        contentBuffer << msgEnd;

        contentBuffer << infoHead;
        for (const string &info: infos) {
            contentBuffer << "<span>" << Utils::escapeForHTML(info) << "</span><br>\n";
        }
        contentBuffer << msgEnd;

        contentBuffer << resultEnd;

        return createAndFillResponse(contentBuffer.str(), EMPTY_USER_NAME, LOGIN_TITLE, false);
    }

    std::string
    cls::createRegisterAccountResponse(const vector<std::string> &errors, const vector<std::string> &warnings,
                                       const vector<std::string> &infos) {
        static const string resultHead{
                "        <div id='content'>"
                "        <div class='unhidden'>\n"
                "            <form id='register-form' class='login' action='' method='Post'>\n"
                "                <h1 class='m-b-50'>Register</h1>\n"
                "                <div class='rainbow-box m-b-10'>\n"
                "                    <input id='register-username' class='user-login' placeholder='Username' name='username' required minlength='3' maxlength='30'></input>\n"
                "                    <hr class='post-hr'>\n"
                "                    <input id='register-password1' class='user-login' type='password' placeholder='Password' name='password1' required minlength='8'>\n"
                "                    <input id='register-password2' class='user-login' type='password' placeholder='Repeat Password' name='password2' required>\n"
                "                </div>\n"
                "                <div class='m-b-10 min-h-1'>\n"
        };

        static const string resultEnd{
                "                </div>\n"
                "                <input class='submit' type='submit' value='Register' id='register'>\n"
                "                <div class='m-t-10 t-a-c w-100p'> "
                "                    &lt;&lt; <a href='javascript:history.back()'>Back</a>\n"
                "                </div>"
                "            </form>\n"
                "        </div>\n"
                "    </div>\n"
        };

        static const string errorHead{
                "                <div id='error-anchor' class='error'>"
        };

        static const string warningHead{
                "                <div id='warning-anchor' class='warning'>"
        };

        static const string infoHead{
                "                <div id='info-anchor' class='info'>"
        };

        static const string msgEnd{
                "</div>\n"
        };

        ostringstream contentBuffer{};

        contentBuffer << resultHead;

        contentBuffer << errorHead;
        for (const string &error: errors) {
            contentBuffer << "<span>" << Utils::escapeForHTML(error) << "</span><br>\n";
        }
        contentBuffer << msgEnd;

        contentBuffer << warningHead;
        for (const string &warning: warnings) {
            contentBuffer << "<span>" << Utils::escapeForHTML(warning) << "</span><br>\n";
        }
        contentBuffer << msgEnd;

        contentBuffer << infoHead;
        for (const string &info: infos) {
            contentBuffer << "<span>" << Utils::escapeForHTML(info) << "</span><br>\n";
        }
        contentBuffer << msgEnd;

        contentBuffer << resultEnd;

        return createAndFillResponse(contentBuffer.str(), EMPTY_USER_NAME, REGISTER_TITLE, false);
    }
}

#pragma endregion Methods

#pragma region Instance Methods

void cls::createHomeResponseFromDao(const string &userName, resCallback rCallback) /* NOLINT */ {

    function<void(vector<Topic> &&)> callback = [this, rCallback, userName](vector<Topic> &&topics) {
        if (topics.empty()) {
            rCallback(createHomeResponse(topics, {}, {}, userName));
            return;
        }

        std::shared_ptr<std::string> userNamePtr = std::make_shared<std::string>(userName);
        std::shared_ptr<vector<Topic>> topicsPtr = std::make_shared<vector<Topic>>(std::move(topics));
        std::shared_ptr<size_t> topicCountPtr = std::make_shared<size_t>(topicsPtr->size());

        std::shared_ptr<vector<int>> postCountsPtr = std::make_shared<vector<int>>();
        std::shared_ptr<vector<Post>> latestPostsIncCreatorPtr = std::make_shared<vector<Post>>();

        std::shared_ptr<vector<function<void(int)>>> countCallbacksPtr = std::make_shared<vector<function<void(int)>>>(
                *topicCountPtr);
        std::shared_ptr<vector<function<void(
                vector<Post> &&)>>> postCallbacksPtr = std::make_shared<vector<function<void(vector<Post> &&)>>>(
                *topicCountPtr);
        std::shared_ptr<vector<function<void(User &&)>>> userCallbacksPtr = std::make_shared<vector<function<void(
                User &&)>>>(*topicCountPtr);

        std::shared_ptr<bool> firedPtr = std::make_shared<bool>(false);
        std::shared_ptr<size_t> countsCountPtr = std::make_shared<size_t>(0);
        std::shared_ptr<size_t> postsCountPtr = std::make_shared<size_t>(0);
        for (size_t i = 0; i < (*topicCountPtr); ++i) {
            unsigned long curTopicId = (*topicsPtr)[i].id;

            // get post counts
            (*countCallbacksPtr)[i] = [countsCountPtr, firedPtr, postsCountPtr, topicCountPtr, rCallback, topicsPtr, postCountsPtr, latestPostsIncCreatorPtr, userNamePtr]
                    (int count) {
                postCountsPtr->push_back(count);
                ++(*countsCountPtr);
                if (!(*firedPtr) && (*countsCountPtr) >= (*topicCountPtr) && (*postsCountPtr) >= (*topicCountPtr)) {
                    *firedPtr = true;
                    rCallback(createHomeResponse(*topicsPtr, *postCountsPtr, *latestPostsIncCreatorPtr, *userNamePtr));
                }
            };
            this->_topicDao.getPostCount(curTopicId, (*countCallbacksPtr)[i]);

            // get the latest post
            (*postCallbacksPtr)[i] = [this, i, userCallbacksPtr, postsCountPtr, firedPtr, countsCountPtr, topicCountPtr, rCallback, topicsPtr, postCountsPtr, latestPostsIncCreatorPtr, userNamePtr]
                    (vector<Post> &&recentPost) {
                // get the creator for the latest post
                if (recentPost.empty()) { // no recent post found
                    latestPostsIncCreatorPtr->push_back({});
                    ++(*postsCountPtr);
                    if (!(*firedPtr) && (*countsCountPtr) >= (*topicCountPtr) && (*postsCountPtr) >= (*topicCountPtr)) {
                        *firedPtr = true;
                        rCallback(createHomeResponse(*topicsPtr, *postCountsPtr, *latestPostsIncCreatorPtr,
                                                     *userNamePtr));
                    }
                } else { // most recent post found
                    std::shared_ptr<Post> recentPostPtr = std::make_shared<Post>(std::move(recentPost[0]));
                    (*userCallbacksPtr)[i] = [recentPostPtr, postsCountPtr, firedPtr, countsCountPtr, topicCountPtr, rCallback, topicsPtr, postCountsPtr, latestPostsIncCreatorPtr, userNamePtr]
                            (User &&creator) {
                        (*recentPostPtr).creator = creator;
                        latestPostsIncCreatorPtr->push_back(*recentPostPtr);
                        ++(*postsCountPtr);
                        if (!(*firedPtr) && (*countsCountPtr) >= (*topicCountPtr) &&
                            (*postsCountPtr) >= (*topicCountPtr)) {
                            *firedPtr = true;
                            rCallback(createHomeResponse(*topicsPtr, *postCountsPtr, *latestPostsIncCreatorPtr,
                                                         *userNamePtr));
                        }
                    };
                    this->_postDao.getCreator((*recentPostPtr).id, (*userCallbacksPtr)[i]);
                }
            };
            this->_postDao.getRecentPostsOfTopic(curTopicId, 1, 0, (*postCallbacksPtr)[i]);
        }
    };

    this->_topicDao.getRecentTopics(-1, 0, callback);
}

void cls::createTopicOverviewResponseFromDao(unsigned long topicId, const string &userName,
                                             resCallback rCallback) { /* NOLINT */
    std::shared_ptr<std::string> userNamePtr = std::make_shared<std::string>(userName);

    function<void(Topic &&)> callback = [this, rCallback, userNamePtr](Topic &&topic) {
        std::shared_ptr<Topic> topicPtr = std::make_shared<Topic>(std::move(topic));

        function<void(vector<Post> &&)> postsCallback = [this, rCallback, topicPtr, userNamePtr](vector<Post> &&posts) {
            if (posts.empty()) {
                rCallback(this->createTopicOverviewResponse(*topicPtr, posts, {}, *userNamePtr));
                return;
            }

            std::shared_ptr<vector<Post>> postsPtr = std::make_shared<vector<Post>>(std::move(posts));
            std::shared_ptr<size_t> postCountPtr = std::make_shared<size_t>(postsPtr->size());
            std::shared_ptr<vector<int>> commentCountsPtr = std::make_shared<vector<int>>(*postCountPtr);

            std::shared_ptr<vector<function<void(int)>>> commentCallbacksPtr = std::make_shared<vector<function<void(
                    int)>>>(*postCountPtr);
            std::shared_ptr<vector<function<void(
                    User &&)>>> creatorCallbacksPtr = std::make_shared<vector<function<void(User &&)>>>(*postCountPtr);

            std::shared_ptr<bool> firedPtr = std::make_shared<bool>(false);
            std::shared_ptr<size_t> countsCountPtr = std::make_shared<size_t>(0);
            std::shared_ptr<size_t> creatorsCountPtr = std::make_shared<size_t>(0);
            for (size_t i = 0; i < (*postCountPtr); ++i) {
                // get comment counts
                (*commentCallbacksPtr)[i] = [this, i, commentCountsPtr, countsCountPtr, firedPtr, creatorsCountPtr, postCountPtr, rCallback, topicPtr, postsPtr, userNamePtr](
                        int count) {
                    (*commentCountsPtr)[i] = count;
                    ++(*countsCountPtr);
                    if (!(*firedPtr) && (*countsCountPtr) >= (*postCountPtr) &&
                        (*creatorsCountPtr) >= (*postCountPtr)) {
                        *firedPtr = true;
                        rCallback(this->createTopicOverviewResponse(*topicPtr, *postsPtr, *commentCountsPtr,
                                                                    *userNamePtr));
                    }
                };
                this->_postDao.getCommentCount((*postsPtr)[i].creator.id, (*commentCallbacksPtr)[i]);

                // get creators for each post
                (*creatorCallbacksPtr)[i] = [this, i, postsPtr, creatorsCountPtr, firedPtr, countsCountPtr, postCountPtr, rCallback, topicPtr, commentCountsPtr, userNamePtr](
                        User &&user) {
                    (*postsPtr)[i].creator = user;
                    ++(*creatorsCountPtr);
                    if (!(*firedPtr) && (*countsCountPtr) >= (*postCountPtr) &&
                        (*creatorsCountPtr) >= (*postCountPtr)) {
                        *firedPtr = true;
                        rCallback(this->createTopicOverviewResponse(*topicPtr, *postsPtr, *commentCountsPtr,
                                                                    *userNamePtr));
                    }
                };
                this->_postDao.getCreator((*postsPtr)[i].id, (*creatorCallbacksPtr)[i]);
            }
        };

        _postDao.getRecentPostsOfTopic((*topicPtr).id, -1, 0, postsCallback);
    };

    _topicDao.getById(topicId, callback);
}

void cls::createPostOverviewResponseFromDao(unsigned long postId, const string &userName,
                                            resCallback rCallback) {  /* NOLINT */

    function<void(Post &&)> callback = [this, rCallback, userName](Post &&post) {
        std::shared_ptr<std::string> userNamePtr = std::make_shared<std::string>(userName);
        std::shared_ptr<Post> postPtr = std::make_shared<Post>(std::move(post));

        // get user for post
        function<void(User &&)> creatorCallback = [this, rCallback, userNamePtr, postPtr](User &&user) {
            (*postPtr).creator = user;
            // get topic for post
            function<void(Topic &&)> topicCallback = [this, rCallback, userNamePtr, postPtr](Topic &&topic) {
                (*postPtr).topic = topic;
                // get comments for post
                function<void(vector<Comment> &&)> commentsCallback = [this, rCallback, userNamePtr, postPtr](
                        vector<Comment> &&comments) {
                    if (comments.empty()) {
                        rCallback(this->createPostOverviewResponse(*postPtr, comments, *userNamePtr));
                        return;
                    }

                    // get creators for each comment
                    std::shared_ptr<vector<Comment>> commentsPtr = std::make_shared<vector<Comment>>(
                            std::move(comments));
                    std::shared_ptr<size_t> commentsCountPtr = std::make_shared<size_t>(commentsPtr->size());

                    std::shared_ptr<vector<function<void(
                            User &&)>>> userCallbacksPtr = std::make_shared<vector<function<void(User &&)>>>(
                            *commentsCountPtr);

                    std::shared_ptr<bool> firePtr = std::make_shared<bool>(false);
                    std::shared_ptr<size_t> creatorCountPtr = std::make_shared<size_t>(0);
                    for (size_t i = 0; i < (*commentsCountPtr); ++i) {
                        (*userCallbacksPtr)[i] = [this, i, commentsPtr, firePtr, creatorCountPtr, commentsCountPtr, rCallback, postPtr, userNamePtr](
                                User &&creator) {
                            (*commentsPtr)[i].creator = creator;
                            ++(*creatorCountPtr);
                            if (!(*firePtr) && (*creatorCountPtr) >= (*commentsCountPtr)) {
                                *firePtr = true;
                                rCallback(this->createPostOverviewResponse(*postPtr, *commentsPtr, *userNamePtr));
                            }
                        };
                        this->_commentDao.getCreator((*commentsPtr)[i].id, (*userCallbacksPtr)[i]);
                    }
                };
                this->_commentDao.getRecentCommentsOfPost((*postPtr).id, -1, 0, commentsCallback);
            };
            this->_postDao.getTopic((*postPtr).id, topicCallback);
        };
        this->_postDao.getCreator((*postPtr).id, creatorCallback);
    };
    this->_postDao.getById(postId, callback);
}

#pragma endregion
