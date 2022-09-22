window.onload = () => {
    const toggle_topic = document.getElementById('toggle-topic');
    const toggle_text = document.getElementById('toggle-text');
    const submit_topic = document.getElementById('submit-topic');
    const topic = document.getElementById("hide_topic");

    const toggle_post = document.getElementById('toggle-post');
    const submit_post = document.getElementById('submit-post');
    const post = document.getElementById("hide-post");

    const toggle_comment = document.getElementById('toggle-comment');
    const submit_comment = document.getElementById('submit-comment');
    const comment = document.getElementById("hide-comment");

    const login = document.getElementById('login');
    const logout = document.getElementById('logout');
    const signup = document.getElementById('signup');

    const toggleTextFunc = (element) => {
        const text = element.innerHTML;
        const prefix = text[0] === "+" ? "-" : "+";
        element.innerHTML = prefix + text.substring(1);
    };

    /* Toggle visibility for Adding Topic */
    if (toggle_topic !== null && submit_topic !== null) {
        const toggle_func = () => {
            topic.classList.toggle("unhidden");
            toggleTextFunc(toggle_text);
        }

        toggle_topic.addEventListener('click', toggle_func);
        submit_topic.addEventListener('click', toggle_func);
    }

    /* Toggle visibility for Adding Post */
    if (toggle_post !== null && submit_post !== null) {
        const toggle_func = () => {
            post.classList.toggle("unhidden");
            toggleTextFunc(toggle_post);
        }

        toggle_post.addEventListener('click', toggle_func);
        submit_post.addEventListener('click', toggle_func);
    }

    /* Toggle visibility for Adding Comment */
    if (toggle_comment !== null && toggle_comment !== null) {
        const toggle_func = () => {
            comment.classList.toggle("unhidden");
            toggleTextFunc(toggle_comment);
        }

        toggle_comment.addEventListener('click', toggle_func)
        submit_comment.addEventListener('click', toggle_func);
    }

    if (login !== null) {
        login.addEventListener('click', () => {
            window.location = "home.html";
            console.log("login");
        });
    }

    if (signup !== null) {
        signup.addEventListener('click', () => {
            window.location = "home.html";
            console.log("signup");
        });
    }

    if (logout !== null) {
        logout.addEventListener('click', () => {
            window.location = "login.html";
            console.log("logout");
        });
    }
}