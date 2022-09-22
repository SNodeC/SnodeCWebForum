//
// Created by student on 9/21/22.
//

#include "CommentDaoImpl.h"
#include "../../domain/Comment.h"

bool CommentDaoImpl::create(std::string content) {
    return false;
}

std::list<Comment>
CommentDaoImpl::getRecentTopicsOfThread(unsigned long id, int amount, std::time_t start, std::time_t end) {
    return std::list<Comment>();
}
