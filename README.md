# sms4 加解密工具

## 已经使用的环境

```
ubuntu、centos
```

## github地址

```
https://github.com/LeiZhang-Hunter/sms4
```

## 安装

```
build.sh
```

可执行文件出现在build下面

## 命令解析

```
    -i 输入要处理的文件
    -o 要输出到哪个文件
    -d 输入要加密还是要解密,加密是"en",解密是de
    -p 为sms4 加密密码
    -v 为sms4 初始化 向量
```

## 使用 

加密使用展示

```
./sms4 -i a.txt -o a.en.txt -d en -p 1000000ACCOUNT#@ -v 462_V20000000000
```

解密使用展示:

```
./sms4 -i a.en.txt -o a.de.txt -d de -p 1000000ACCOUNT#@ -v 462_V20000000000
```