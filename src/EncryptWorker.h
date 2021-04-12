//
// Created by zhanglei on 2021/4/9.
//

#ifndef SMS4_ENCRYPTWORKER_H
#define SMS4_ENCRYPTWORKER_H


#include <memory>

#include "SMS4Encrypt.h"
#include "Command.h"

namespace src {
    class EncryptWorker : public std::enable_shared_from_this<EncryptWorker>{
    public:
        EncryptWorker() {
            command = std::make_shared<Command>();
        }

        bool setCommandArgc(int argc) {
            command->setCmdArgC(argc);
            return true;
        }

        bool setCommandArgv(char **argv) {
            command->setCmdArgV(argv);
            return true;
        }

        bool setInputFile(int argc, char **argv, const char &cmd) {
            inputFile = argv[optind];
            return true;
        }

        bool setOutputFile(int argc, char **argv, const char &cmd) {
            outputFile = argv[optind];
            return true;
        }

        bool setPassword(int argc, char **argv, const char &cmd) {
            sms4Password = argv[optind];
            return true;
        }

        bool setVector(int argc, char **argv, const char &cmd) {
            sms4StrInitVec = argv[optind];
            return true;
        }

        bool setOperation(int argc, char **argv, const char &cmd) {
            operation = argv[optind];
            return true;
        }

        void run();

        ~EncryptWorker() {

        }

    private:
        //命令行解析
        std::shared_ptr<Command> command;

        //加密库
        std::shared_ptr<SMS4Encrypt> encrypt;

        //初始化密码
        std::string sms4Password;

        //初始化向量
        std::string sms4StrInitVec;

        //输入文件
        std::string inputFile;

        //输出文件
        std::string outputFile;

        //操作加密还是解密
        std::string operation = "en";

    };
}

#endif //SMS4_ENCRYPTWORKER_H
