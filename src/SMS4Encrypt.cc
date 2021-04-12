//
// Created by zhanglei on 2021/4/9.
//

#include <iostream>
#include "SMS4Encrypt.h"

void src::SMS4Encrypt::encrypt(const std::string &context, std::string &encryptBody) {
    //对数据进行加密
    size_t contentLength = context.length();
    size_t encryptDataLen = ((contentLength / BLOCK_SIZE) + 1) * BLOCK_SIZE;
    //加密的key
    sms4_key_t key;

    sms4_set_encrypt_key(&key, sms4Password.data());

    //char  cPad = BLOCK_SIZE - strPlaintext.length() % BLOCK_SIZE;
    char cPad = static_cast<char>((BLOCK_SIZE - contentLength % BLOCK_SIZE));
    std::vector<unsigned char> inputBody(encryptDataLen, cPad);
    std::copy(context.begin(), context.end(), inputBody.begin());
    encryptBody.resize(encryptDataLen);

    std::string  sms4StrInitVecValue(sms4StrInitVec);
    //初始化加密缓冲区
    sms4_cbc_encrypt((unsigned char *)inputBody.data(), (unsigned char *)encryptBody.data(), encryptDataLen, &key,
                     (unsigned char*)sms4StrInitVec.c_str(), 1);

}

void src::SMS4Encrypt::decrypt(const std::string& enContext, std::string& context) {

    size_t enContextLength = enContext.size();

    //解密的key
    sms4_key_t deKey;

    //对数据进行加密
    std::string  sms4StrInitVecValue(sms4StrInitVec);
    sms4_set_decrypt_key(&deKey, sms4Password.data());

    context.resize(enContextLength);
    //解密
    sms4_cbc_encrypt((unsigned char *)(enContext.c_str()), (unsigned char *)context.c_str(), enContextLength, &deKey,
            (unsigned char *)sms4StrInitVec.c_str(), 0);
    context.resize((enContextLength - context[enContextLength - 1]));
}
