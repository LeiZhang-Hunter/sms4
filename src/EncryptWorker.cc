#include <fcntl.h>
#include <iostream>
#include <fstream>

#include "EncryptWorker.h"

using namespace std::placeholders;

void src::EncryptWorker::run() {
    //注入命令处理的回调函数

    command->reg('i', std::bind(&EncryptWorker::setInputFile, shared_from_this(), _1, _2, _3));
    command->reg('o', std::bind(&EncryptWorker::setOutputFile, shared_from_this(), _1, _2, _3));
    command->reg('p', std::bind(&EncryptWorker::setPassword, shared_from_this(), _1, _2, _3));
    command->reg('v', std::bind(&EncryptWorker::setVector, shared_from_this(), _1, _2, _3));
    command->reg('d', std::bind(&EncryptWorker::setOperation, shared_from_this(), _1, _2, _3));
    command->reg('s', std::bind(&EncryptWorker::setBlockSize, shared_from_this(), _1, _2, _3));
    command->parse();

    //输入参数检查
    if (inputFile.empty()) {
        std::cerr << "-i empty!" << std::endl;
        exit(-1);
    }

    if (outputFile.empty()) {
        std::cerr << "-o empty!" << std::endl;
        exit(-1);
    }

    if (sms4Password.empty()) {
        std::cerr << "-p empty!" << std::endl;
        exit(-1);
    }

    if (sms4StrInitVec.empty()) {
        std::cerr << "-v empty!" << std::endl;
        exit(-1);
    }

    encrypt = std::make_shared<SMS4Encrypt>(sms4Password, sms4StrInitVec);

    unlink(outputFile.c_str());

    int writeFd;
    writeFd = open(outputFile.c_str() , O_CREAT | O_RDWR| O_APPEND, 0664);
    if (writeFd == -1) {
        std::cerr << "open error:" << outputFile.c_str() << ";error:" << strerror(errno) << std::endl;
        exit(-1);
    }

    int readFd;
    readFd = open(inputFile.c_str() , O_CREAT | O_RDWR, 0664);
    if (readFd == -1) {
        std::cerr << "open error:" << inputFile.c_str() << ";error:" << strerror(errno) << std::endl;
        exit(-1);
    }


    //std::vector<char> buffer;
    std::string buffer;
    std::string readBuffer;
    std::string encryptString;
    std::string decryptString;
    std::string co;
    size_t readBytes = 0;

    //是否是加密
    bool isEncrypt = true;

    if (operation == "de") {
        isEncrypt = false;
    }



    size_t buffer_size = 0;
    //size_t block_size = BUFSIZ;
    //这里对由于广电要求
    if (!blockSize) {
        blockSize = BUFSIZ;
    }
    if (isEncrypt) {
        buffer_size = blockSize;
    } else {
        buffer_size += ((blockSize / BLOCK_SIZE) + 1) * BLOCK_SIZE;
    }

    //读取文件
    std::cout << buffer_size << std::endl;
    while (1) {
        buffer.resize(buffer_size);

        readBytes = command->readn(readFd, (void *)(buffer.c_str()), buffer_size);
        std::cout << readBytes << std::endl;

        if (readBytes == 0) {
            break;
        }

        buffer.resize(readBytes);
        if (readBytes < buffer_size) {
            buffer[readBytes] = '\0';
        }

        //加密的情况直接去读BUFSIZE 8192
        if (isEncrypt) {

            encrypt->encrypt(buffer, encryptString);
            command->writen(writeFd, (void *)encryptString.c_str(), encryptString.size());
        } else {
            //确定读取的块大小
            encrypt->decrypt(buffer, decryptString);
            command->writen(writeFd, (void *)decryptString.c_str(), decryptString.size());
        }
    }



    close(writeFd);
    close(readFd);
}