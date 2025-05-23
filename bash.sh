#!/bin/bash
# 生成ANTLR解析器
java -jar $HOME/miniC/thirdparty/antlr4/antlr-4.12.0-complete.jar -Dlanguage=Cpp -visitor -no-listener /home/code/miniC/frontend/antlr4/MiniC.g4
# 配置和构建项目
# rm -rf build
cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++
cmake --build build --parallel
# 生成AST图
./build/minic -S -T -A -o ./tests/test-AST.png ./tests/test.c
# 生成标准ir
tools/IRCompiler/Linux-x86_64/Ubuntu-22.04/IRCompiler -S -L -o tests/test_std.ll tests/test.c 
# 用自己的编译器生成ir
./build/minic -S -A -L -o tests/test.ll tests/test.c
# 用ircompiler运行自己的ir测试准确性
tools/IRCompiler/Linux-x86_64/Ubuntu-22.04/IRCompiler -R tests/test.ll

# # 生成标准LLVM IR (.ll文件)
# clang -S -emit-llvm -o tests/test_std1.ll tests/test.c
# # 自己的编译器生成LLVM IR
# ./build/minic -S -A -emit-llvm -o tests/test.ll tests/test.c
# # 执行IR (通过JIT)
# lli tests/test.ll
# 查看返回值
echo $?  
rm -rf ./llvm-*

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

# git指令：
# git checkout dev_CPY          # 切换到队友的分支
# git fetch origin dev_CPY             # 获取远程最新代码
# git checkout dev_wh       # 切换到你的开发分支
# git merge origin/dev_CPY     # 合并远程更新（或 git pull origin dev_CPY）
# git add .			  修改过的文件和新增的文件添加到暂存区
# git commit -m "XXX"     将暂存区的文件提交到本地仓库
# git push origin dev_wh    # 将合并后的 dev_wh 推送到远程

# 查看分支差异	git diff dev_wh origin/dev_CPY
# 放弃合并	git merge --abort 或 git rebase --abort
# 查看合并状态	git status
# 查看提交历史	git log --graph --oneline
# 创建一个本地分支并自动跟踪  git checkout -b dev_CPY origin/dev_CPY
# git branch -r  # 查看所有远程跟踪分支
# git checkout 78fabb2 -- tools/IRCompiler/Linux-x86_64/Ubuntu-22.04/IRCompiler 恢复到某个特定的提交版本