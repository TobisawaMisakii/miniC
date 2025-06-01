#!/bin/bash
# 生成ANTLR解析器
java -jar $HOME/Complier/miniC/thirdparty/antlr4/antlr-4.12.0-complete.jar -Dlanguage=Cpp -visitor -no-listener /home/lwx/Complier/miniC/frontend/antlr4/SysY.g4
cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++
cmake --build build --parallel
# 生成AST图
./build/minic -S -T -A -o ./tests/test-AST.png ./tests/test.c
# 生成标准ir
# tools/IRCompiler/Linux-x86_64/Ubuntu-22.04/IRCompiler -S -L -o tests/test_std.ll tests/test.c 
clang -S -emit-llvm -o tests/test_std1.ll tests/test.c
# 用自己的编译器生成ir
./build/minic -S -A -L -o tests/test.ll tests/test.c
# 用ircompiler运行自己的ir测试准确性
# tools/IRCompiler/Linux-x86_64/Ubuntu-22.04/IRCompiler -R tests/test.ll
#lli tests/test.ll
clang -o tests/test tests/test.ll tests/std.c
./tests/test
echo $?