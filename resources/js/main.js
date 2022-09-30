const ERRORSEP = ';';

window.onload = () => {


    // Home
    const toggle_topic = document.getElementById('toggle-topic');
    const toggle_text = document.getElementById('toggle-text');
    const submit_topic = document.getElementById('submit-topic');
    const topic_form = document.getElementById('hide-topic');
    const topic_title = document.getElementById('topic-title');
    const topic_content = document.getElementById('topic-content');


    // Topic overview
    const toggle_post = document.getElementById('toggle-post');
    const submit_post = document.getElementById('submit-post');
    const post_form = document.getElementById('hide-post');
    const post_title = document.getElementById('post-title');
    const post_content = document.getElementById('post-content');

    // Post overview
    const toggle_comment = document.getElementById('toggle-comment');
    const submit_comment = document.getElementById('submit-comment');
    const comment_form = document.getElementById('hide-comment');
    const comment_content = document.getElementById('comment-content');

    // Login/Logout/Register
    const login = document.getElementById('login');
    const logout = document.getElementById('logout');
    const register = document.getElementById('register');
    const login_form = document.getElementById('login-form')
    const login_username = document.getElementById('login-username');
    const login_password = document.getElementById('login-password');

    const register_form = document.getElementById('register-form');
    const register_username = document.getElementById('register-username');
    const register_password1 = document.getElementById('register-password1');
    const register_password2 = document.getElementById('register-password2');

    // Message anchors. Available wherever submits are available
    const error_anchor = document.getElementById('error-anchor');
    const warning_anchor = document.getElementById('warning-anchor');
    const info_anchor = document.getElementById('info-anchor');

    const toggleTextFunc = (element) => {
        const text = element.innerHTML;
        const prefix = text[0] === '+' ? '-' : '+';
        element.innerHTML = prefix + text.substring(1);
    };

    /* Toggle visibility for Adding Topic */
    if (toggle_topic !== null && submit_topic !== null) {
        const toggle_func = () => {
            topic_form.classList.toggle('unhidden');
            toggleTextFunc(toggle_text);
        }

        toggle_topic.addEventListener('click', toggle_func);
        submit_topic.addEventListener('click', toggle_func);
    }

    /* Toggle visibility for Adding Post */
    if (toggle_post !== null && submit_post !== null) {
        const toggle_func = () => {
            post_form.classList.toggle('unhidden');
            toggleTextFunc(toggle_post);
        }

        toggle_post.addEventListener('click', toggle_func);
        submit_post.addEventListener('click', toggle_func);
    }

    /* Toggle visibility for Adding Comment */
    if (toggle_comment !== null) {
        const toggle_func = () => {
            comment_form.classList.toggle('unhidden');
            toggleTextFunc(toggle_comment);
        }

        toggle_comment.addEventListener('click', toggle_func)
        submit_comment.addEventListener('click', toggle_func);
    }

    if (topic_form !== null) {
        topic_form.addEventListener('submit', (e) => {
            e.preventDefault();

            const payload = [...(new FormData(topic_form))];

            const userData = `Title=${payload[0][1]}&Content=${payload[1][1]}`;

            removeAllChildren(error_anchor);

            fetch('/t/', {
                method: 'Post',
                credentials: 'include',
                body: userData,
            }).then(data => {
                if (data.status === 200) {
                    window.location.reload();
                } else if (data.status === 500) {
                    data.text().then(text => listErrors(text, error_anchor))
                }
            })
                .catch(err => console.log(err));

            console.log('topic creation');
        });
    }

    if (post_form !== null) {
        post_form.addEventListener('submit', (e) => {
            e.preventDefault();

            const payload = new FormData(post_form);
            console.log(payload);

            const userData = 'Title=' + [...payload][0][1] + '&Content=' + [...payload][1][1];

            removeAllChildren(error_anchor);

            fetch('/p/' + window.location.href.split('/').pop(), {
                method: 'Post',
                credentials: 'include',
                body: userData,
            }).then(data => {
                if (data.status === 200) {
                    window.location.reload();
                    console.log(window.location.href);
                } else if (data.status === 400) {
                    data.text().then(text => listErrors(text, error_anchor))
                } else if (data.status === 500) {
                    data.text().then(text => listErrors(text, error_anchor))
                }
            })
                .catch(err => console.log(err));
            console.log(window.location.href);

            console.log('Post creation');
        });
    }

    if (comment_form !== null) {
        comment_form.addEventListener('submit', (e) => {
            e.preventDefault();

            const payload = new FormData(comment_form);
            console.log(payload);

            const content = 'Content=' + [...payload][0][1] + '&';

            removeAllChildren(error_anchor);

            fetch('/c/' + window.location.href.split('/').pop(), {
                method: 'Post',
                credentials: 'include',
                body: content,
            }).then(data => {
                if (data.status === 200) {
                    window.location.reload();
                } else if (data.status === 400) {
                    data.text().then(text => listErrors(text, error_anchor))
                } else if (data.status === 500) {
                    data.text().then(text => listErrors(text, error_anchor))
                }
            })
                .catch(err => console.log(err));

            console.log('Comment creation');
        });
    }

    if (login_form !== null) {
        login_form.addEventListener('submit', (e) => {
            e.preventDefault();

            const payload = [...(new FormData(login_form))];

            console.log(payload);
            const userData = `Username=${login_username.value}&Password=${login_password.value}`;

            removeAllChildren(error_anchor);

            fetch('/login/', {
                method: 'Post',
                credentials: 'include',
                body: userData,
            }).then(data => {
                if (data.status === 200) {
                    window.location = '/';
                } else if (data.status === 400) {
                    appendSpan(error_anchor, 'Username/password is incorrect');
                } else if (data.status === 500) {
                    appendSpan(error_anchor, "Internal server error - Try again later")
                }
            })
                .catch(err => console.log(err));

            console.log('login');
        });
    }


    if (register_form !== null) {

        register_form.addEventListener('submit', (e) => {
            e.preventDefault();

            const payload = [...(new FormData(register_form))];

            console.log(payload);


            const userData = `Username=${payload[0][1]}&Password=${payload[1][1]}`;

            removeAllChildren(error_anchor);

            fetch('/register/', {
                method: 'Post',
                credentials: 'include',
                body: userData,
            }).then(data => {
                if (data.status === 200) {
                    window.location = '/login/';
                } else if (data.status === 400) {
                    appendSpan(error_anchor, 'Username \"' + register_username.value + '\" already taken');
                } else if (data.status === 500) {
                    data.text().then(text => listErrors(text, error_anchor))
                }

            })
                .catch(err => console.log(err));
        })
    }


    if (register !== null) {
        register.addEventListener('click', () => {
            if (register_password1.value === register_password2.value) {
                register_password2.setCustomValidity('');
            } else {
                register_password2.setCustomValidity('Passwords don\'t match');
            }
        });
    }


    if (logout !== null) {
        logout.addEventListener('click', () => {
            window.location = '/login/';

            deleteAllCookies();

        });
    }
}


function appendSpan(parent, content) {
    if (content.length !== 0) {
        const span = document.createElement('span');
        span.innerHTML = `${content}<br>`;
        parent.appendChild(span);
    }
}

function removeAllChildren(parent) {
    parent.replaceChildren();
}

function listErrors(body, error_anchor) {
    const errors = body.split(ERRORSEP);

    for (let i = 0; i < errors.length; i++) {
        appendSpan(error_anchor, errors[i]);
    }
}


function deleteAllCookies() {
    var cookies = document.cookie.split(";");

    for (var i = 0; i < cookies.length; i++) {
        var cookie = cookies[i];
        var eqPos = cookie.indexOf("=");
        var name = eqPos > -1 ? cookie.substr(0, eqPos) : cookie;
        document.cookie = name + "=;expires=Thu, 01 Jan 1970 00:00:00 GMT";
    }
}
