extern "C" {
    #include "openssl/sms4.h"
}

#include <string>
#include <iostream>
#include <memory>


#include "EncryptWorker.h"

#define BLOCK_SIZE 16
using namespace std;
int main(int argc,char* argv[])
{
    //设置初始密码（16位）
    string strPasswd="1000000ACCOUNT#@";
    sms4_key_t key;
    //设置初始化向量（16位）
    string strInitVec = "462_V20000000000";
    std::shared_ptr<src::EncryptWorker> worker = std::make_shared<src::EncryptWorker>();
    worker->setCommandArgc(argc);
    worker->setCommandArgv(argv);
    worker->run();
}