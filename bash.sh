#!/bin/bash
# 生成ANTLR解析器
java -jar $HOME/Complier/miniC/thirdparty/antlr4/antlr-4.12.0-complete.jar -Dlanguage=Cpp -visitor -no-listener /home/lwx/Complier/miniC/frontend/antlr4/SysY.g4
cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++
cmake --build build --parallel
# 生成AST图
# ./build/minic -S -T -A -o ./tests/test-AST.png ./tests/test.c
# # 生成标准ir
# clang -S -emit-llvm -o tests/test_std1.ll tests/test.c
# # 用自己的编译器生成ir
./build/minic -S -A -L -o tests/test2-1.ll tests/test2-1.c
# 生成ARM64汇编
clang -S -target aarch64-linux-gnu -o tests/test2-1.s tests/test2-1.ll
# 编译生成ARM64汇编文件
# aarch64-linux-gnu-gcc -o tests/test_arm tests/test.arm -no-pie
# 运行ARM64程序
# qemu-aarch64 ./tests/test_arm
echo $?