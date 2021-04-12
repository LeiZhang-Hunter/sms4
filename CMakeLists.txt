cmake_minimum_required(VERSION 3.16)
project(sms4)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

include_directories(src)
include_directories(openssl)
link_directories(lib)
#文件不多直接列下来
add_executable(sms4 main.cc
        src/Command.cc
        src/EncryptWorker.cc
        src/SMS4Encrypt.cc)
target_link_libraries(sms4
        ssl
        crypto
        )
