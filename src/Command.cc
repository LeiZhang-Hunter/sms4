//
// Created by zhanglei on 2020/11/10.
//
extern "C" {
#include <getopt.h>
}

#include <iostream>

#include "Command.h"


ssize_t src::Command::readn(int fd, void *vptr, size_t n) {
    ssize_t nleft;
    ssize_t nread;
    char *ptr;
    ptr = (char*)vptr;

    nleft = n;
    while (nleft > 0) {
        if ((nread = read(fd, ptr, nleft)) < 0) {
            if (errno == EINTR)
                nread = 0;
            else
                return -1;
        } else if (nread == 0) {
            break;
        }

        nleft -= nread;
        ptr += nread;
    }

    return n - nleft;
}

ssize_t src::Command::writen(int fd, void *vptr, size_t n) {
    size_t nleft;
    ssize_t nwritten;
    const char *ptr;
    ptr = (const char *)vptr;
    nleft = n;

    while (nleft > 0) {
        if ((nwritten = write(fd, ptr, nleft)) <= 0) {
            if (errno == EINTR) {
                nwritten = 0;
            } else {
                return -1;
            }


        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    return n;
}

/*==================解析命令行参数======================*/
bool src::Command::parse() {
    //遍历map组装结果
    cmdMapType::iterator cmdMapIterator;
    std::string cmdOptionString;
    std::string option;

    //检查argc
    if (cmdArgC == 0) {
        std::cerr << "Please set argc" << std::endl;
        exit(-1);
    }

    if (!cmdArgV) {
        std::cerr << "Please set argv" << std::endl;
        exit(-1);
    }

    for (cmdMapIterator = cmdMap.begin(); cmdMapIterator != cmdMap.end(); cmdMapIterator++) {
        cmdOptionString.append(&cmdMapIterator->first);
    }

    int opt = 0;
    char charOpt;
    while ((opt = getopt(cmdArgC, cmdArgV, cmdOptionString.c_str())) != -1) {
        charOpt = static_cast<char>(opt);
        cmdMapIterator = cmdMap.find(charOpt);
        if (cmdMapIterator != cmdMap.end()) {
            cmdMapIterator->second(cmdArgC, cmdArgV, charOpt);
        } else {
            std::cerr << "args" << charOpt - '0' << " not found" << std::endl;
            exit(-1);
        }
    }
    return true;
}