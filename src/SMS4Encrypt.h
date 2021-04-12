//
// Created by zhanglei on 2021/4/9.
//

#ifndef SMS4_SMS4ENCRYPT_H
#define SMS4_SMS4ENCRYPT_H

#include <string>
#include <vector>
#include "sms4.h"

#ifndef BLOCK_SIZE
#define BLOCK_SIZE 16
#endif

namespace src {
    class SMS4Encrypt {

    public:
        SMS4Encrypt(const std::string& password, const std::string& strInitVec) {
            //设置加密密钥
            sms4Password.resize(password.length() + 1);
            sms4Password.assign(password.begin(), password.end());

            sms4StrInitVec = strInitVec;

        }

        //加密
        void encrypt(const std::string &context, std::string &encryptBody);

        //解密
        void decrypt(const std::string& enContext, std::string& context);

    private:
        //初始化密码
        std::vector<unsigned char> sms4Password;

        //初始化向量
        std::string sms4StrInitVec;
    };
}

#endif //SMS4_SMS4ENCRYPT_H
