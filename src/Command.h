//
// Created by zhanglei on 2021/4/9.
//

#ifndef SMS4_COMMAND_H
#define SMS4_COMMAND_H

#include <getopt.h>
#include <unistd.h>
#include <functional>
#include <map>


namespace src {
    class Command {
        typedef std::function<bool(int argc, char **argv, const char &)> cmdClosureType;
        typedef std::map<char, cmdClosureType> cmdMapType;
        typedef std::map<const char, const std::string &> cmdResultMapType;
    public:
        void setCmdArgC(int argc) {
            cmdArgC = argc;
        }

        void setCmdArgV(char **argv) {
            cmdArgV = argv;
        }

        /**
         * 将注册的命令加入到Map中
         * @param cmd
         */
        void reg(const char &cmd, const cmdClosureType &closure) {
            cmdMap[cmd] = closure;
        }

        char **getCmdArgv() {
            return cmdArgV;
        }

        int getCmdArgC() {
            return cmdArgC;
        }

        ssize_t readn(int fd, void *vptr, size_t n);

        ssize_t writen(int fd, void *vptr, size_t n);

        bool parse();

    private:
        cmdMapType cmdMap;
        cmdResultMapType cmdResultMap;
        int cmdArgC = 0;
        char **cmdArgV = nullptr;
    };
}

#endif //SMS4_COMMAND_H
