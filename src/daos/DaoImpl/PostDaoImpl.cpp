//
// Created by student on 9/21/22.
//

#include "PostDaoImpl.h"
#include "../../domain/Topic.h"
#include "../../domain/Post.h"

bool PostDaoImpl::create(std::string title) {
    return false;
}

Topic PostDaoImpl::getSubtopic(unsigned long id) {
    return Topic();
}

std::list<Post>
PostDaoImpl::getRecentThreadsOfSubtopic(unsigned long id, int amount, std::time_t start, std::time_t end) {
    return std::list<Post>();
}
