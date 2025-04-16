# dev_CPY开发文档
## 前端
从源程序到语法树的转换过程，其中词法/语法分析器均需要与symbol table交互

### 1. 环境配置
-    打开.zshrc

     ```shell
     vim ~/.zshrc
     ```

- 在文件末尾添加三行语句

  ```shell
  export CLASSPATH=".:$HOME/Compiler/exp04-minic-expr/thirdparty/antlr4/antlr-4.12.0-complete.jar:$CLASSPATH"
  alias antlr4='java -jar $HOME/Compiler/exp04-minic-expr/thirdparty/antlr4/antlr-4.12.0-complete.jar'
  alias grun='java org.antlr.v4.gui.TestRig'
  ```

-    sourse一下

     ```shell
     source ~/.zshrc
     ```

-    测试一下，输入antlr4

     ```shell
     antlr4
     ```

### 1.1 debug setting
调整vscode/lauch.json，对tests/test1-1.c，使用Debug minic Antlr4 Grammar可以生成语法分析树


### 1.2 antlr4生成语法分析器过程：
- 语法分析器的语法文件：`*.g4`，包含了词法分析器和语法分析器的规则，需要自己添加规则
- 对`.g4`文件进行编译，生成词法分析器和语法分析器的代码
- 运行词法分析器，读取输入文件，生成token流
- 运行语法分析器，读取token流，生成语法树
- 运行语法树遍历器，遍历语法树，执行相应的操作


#### 1.2.1 g4文件
这就是典型的语法产生式的撰写：**非终结符+产生式**

```antlr4
//添加对多个函数的支持
compileUnit: (funcDef)+;

//添加对声明变量的支持
blockItem: declaration | statement;

// 声明规则
declaration: T_INT initDeclaratorList T_SEMICOLON;

// 一个声明可以有多个变量：int a, b = 5;
initDeclaratorList: initDeclarator (',' initDeclarator)*;

// initDeclarator: 变量名 或 变量名 = 表达式
initDeclarator: T_ID ('=' expr)?;

statement:
	T_RETURN expr T_SEMICOLON	# returnStatement
	| T_ID '=' expr T_SEMICOLON	# assignStatement;

//新增表达式规则
expr
	: expr op = ('*' | '/') expr		# mulDivExpr
	| expr op = ('+' | '-') expr	# addSubExpr
	| '(' expr ')'					# parenExpr
	| T_ID							# idExpr
	| T_DIGIT						# numberExpr;
```

修改完成后，还要重新生成antlr4相关文件，采用命令如下：

```shell
 antlr4 -Dlanguage=Cpp -visitor -no-listener /home/cpy/Compiler/exp04-minic-expr/frontend/antlr4/MiniC.g4
```
参数说明：

-    -Dlanguage=Cpp 表示生成的语言为C++
-    -visitor 表示生成visitor模式的C++文件
-    -no-listener 表示不生成listener模式的文件
-    /home/cpy/Compiler/exp04-minic-expr/frontend/antlr4/MiniC.g4 这是g4文件的路径

#### 1.2.2 修改Antlr4CSTVisitor.cpp

-    由于修改之后，statement产生式如下：

     ```antlr4
     statement:
     	T_RETURN expr T_SEMICOLON	# returnStatement
     	| T_ID '=' expr T_SEMICOLON	# assignStatement;
     ```
