#!/bin/bash
# 生成ANTLR解析器（保持不变）
java -jar $HOME/miniC/thirdparty/antlr4/antlr-4.12.0-complete.jar -Dlanguage=Cpp -visitor -no-listener /home/code/miniC/frontend/antlr4/MiniC.g4

# 配置和构建项目（保持不变）
# rm -rf build
cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++
cmake --build build --parallel

# 使用LLVM生成标准IR（替代IRCompiler）
clang -S -emit-llvm -o tests/test1-1_standard.ll tests/test1-1.c

# 生成AST图（保持不变）
./build/minic -S -T -A -o ./tests/test-AST.png ./tests/test1-1.c

# 用你的编译器生成IR（保持不变）
./build/minic -S -A -I -o tests/test1-1.ll tests/test1-1.c

# 使用LLVM验证IR（替代IRCompiler验证）
llvm-as tests/test1-1.ll -o - | llvm-dis > /dev/null && echo "IR验证成功" || echo "IR验证失败"

# 命令格式：
# minic -S [-A | -D] [-T | -I] [-o output] [-O level] [-t cpu] source

# 选项-S为必须项，默认输出汇编。

# 选项-O level指定时可指定优化的级别，0为未开启优化。
# 选项-o output指定时可把结果输出到指定的output文件中。
# 选项-t cpu指定时，可指定生成指定cpu的汇编语言。

# 选项-A 指定时通过 antlr4 进行词法与语法分析。
# 选项-D 指定时可通过递归下降分析法实现语法分析。
# 选项-A与-D都不指定时按默认的flex+bison进行词法与语法分析。

# 选项-T指定时，输出抽象语法树，默认输出的文件名为ast.png，可通过-o选项来指定输出的文件。
# 选项-I指定时，输出中间IR(DragonIR)，默认输出的文件名为ir.txt，可通过-o选项来指定输出的文件。
# 选项-T和-I都不指定时，按照默认的汇编语言输出，默认输出的文件名为asm.s，可通过-o选项来指定输出的文件。

git指令：
git checkout dev_wh       # 切换到你的开发分支
git fetch origin
git merge origin/dev_CPY
git push origin dev_wh    # 将合并后的 dev_wh 推送到远程

查看分支差异	git diff dev_wh origin/dev_CPY
放弃合并	git merge --abort 或 git rebase --abort
查看合并状态	git status
查看提交历史	git log --graph --oneline