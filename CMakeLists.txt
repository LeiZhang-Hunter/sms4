cmake_minimum_required(VERSION 3.16)
project(sms4)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g")
#set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -O3")
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
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
