window.onload = () => {

    // Home
    const toggle_topic = document.getElementById('toggle-topic');
    const toggle_text = document.getElementById('toggle-text');
    const submit_topic = document.getElementById('submit-topic');
    const topic = document.getElementById('hide_topic');

    // Topic overview
    const toggle_post = document.getElementById('toggle-post');
    const submit_post = document.getElementById('submit-post');
    const post = document.getElementById('hide-post');

    // Post overview
    const toggle_comment = document.getElementById('toggle-comment');
    const submit_comment = document.getElementById('submit-comment');
    const comment = document.getElementById('hide-comment');

    // Login/Logout/Register
    const login = document.getElementById('login');
    const logout = document.getElementById('logout');
    const register = document.getElementById('register');

    const form = document.getElementById('registerForm');
    const username = document.getElementById('username');
    const password1 = document.getElementById('password1');
    const password2 = document.getElementById('password2');

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
            topic.classList.toggle('unhidden');
            toggleTextFunc(toggle_text);
        }

        toggle_topic.addEventListener('click', toggle_func);
        submit_topic.addEventListener('click', toggle_func);
    }

    /* Toggle visibility for Adding Post */
    if (toggle_post !== null && submit_post !== null) {
        const toggle_func = () => {
            post.classList.toggle('unhidden');
            toggleTextFunc(toggle_post);
        }

        toggle_post.addEventListener('click', toggle_func);
        submit_post.addEventListener('click', toggle_func);
    }

    /* Toggle visibility for Adding Comment */
    if (toggle_comment !== null) {
        const toggle_func = () => {
            comment.classList.toggle('unhidden');
            toggleTextFunc(toggle_comment);
        }

        toggle_comment.addEventListener('click', toggle_func)
        submit_comment.addEventListener('click', toggle_func);
    }

    if (login !== null) {
        login.addEventListener('click', () => {
            window.location = 'home.html';
            console.log('login');
        });
    }

    form.addEventListener('submit', (e) => {
        e.preventDefault();

        const payload = new FormData(form);

        console.log(payload);

        const userData = 'Username=' + [...payload][0][1] + '&Password=' + [...payload][1][1];

        removeAllChildren(error_anchor);

        fetch('/register', {
            method: 'Post',
            body: userData,
        }).then(data => {
            if (data.status === 200) {
                console.log('it go');
            } else if (data.status === 400) {
                appendSpan(error_anchor, 'Username \"' + username.value + ' \" already taken');
            }
        })
            .catch(err => console.log(err));
    })

    if (register !== null) {
        register.addEventListener('click', () => {

            if (password1.value === password2.value) {
                password2.setCustomValidity('');
            } else {
                password2.setCustomValidity('Passwords don\'t match');
            }
        });
    }


    if (logout !== null) {
        logout.addEventListener('click', () => {
            window.location = 'login.html';
            console.log('logout');
        });
    }
}


function appendSpan(parent, content) {
    const span = document.createElement('span');
    span.innerHTML = `${content}<br>`;
    parent.appendChild(span);
}

function removeAllChildren(parent) {
    parent.replaceChildren();
}
