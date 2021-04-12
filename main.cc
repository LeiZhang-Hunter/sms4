extern "C" {
    #include "openssl/sms4.h"
}

#include <iostream>
#include <memory>


#include "EncryptWorker.h"

#define BLOCK_SIZE 16
using namespace std;
int main(int argc,char* argv[])
{
    //设置初始密码（16位）
    //设置初始化向量（16位）
    std::shared_ptr<src::EncryptWorker> worker = std::make_shared<src::EncryptWorker>();
    worker->setCommandArgc(argc);
    worker->setCommandArgv(argv);
    worker->run();
}