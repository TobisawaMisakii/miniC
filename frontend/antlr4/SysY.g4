grammar SysY;

// 编译单元
compileUnit: (decl | funcDef)* EOF;

// 声明
decl: constDecl | varDecl;

// 常量声明
constDecl: 'const' basicType constDef (',' constDef)* ';';

// 基本类型
basicType: 'int' | 'float';

// 单个常量(可以是数组)的初始化
constDef: Ident ('[' constExp ']')* '=' constInitVal;

// 常量初值
constInitVal:
	constExp										# singleConstantInit
	| '{' (constInitVal (',' constInitVal)*)? '}'	# arrayConstantInit;

// 变量声明
varDecl: basicType varDef (',' varDef)* ';';

// 变量定义
varDef:
	Ident ('[' constExp ']')*				# simpleVarDef
	| Ident ('[' constExp ']')* '=' initVal	# initializedVarDef;

// 变量初值
initVal:
	exp									# singleVarInit
	| '{' (initVal (',' initVal)*)? '}'	# arrayVarInit;

// 函数定义
funcDef: funcType Ident '(' funcFParams? ')' block;

// 函数类型
funcType: 'void' | 'int' | 'float';

// 函数形参表
funcFParams: funcFParam (',' funcFParam)*;

// ?函数形参，e.g.  int a | int a[] | float a[][exp]
funcFParam: basicType Ident ('[' ']' ('[' exp ']')*)?;

// 语句块
block: '{' blockItem* '}';

// 语句块项
blockItem:
	decl	# declarationBlockItem
	| stmt	# statementBlockItem;

// 语句
stmt:
	lVal '=' exp ';'						# assignmentStatement
	| exp? ';'								# expressionStatement
	| block									# nestedBlockStatement
	| 'if' '(' cond ')' stmt ('else' stmt)?	# ifStatement
	| 'while' '(' cond ')' stmt				# whileStatement
	| 'break' ';'							# breakStatement
	| 'continue' ';'						# continueStatement
	| 'return' exp? ';'						# returnStatement;

// 表达式
exp: addExp;

// 条件表达式
cond: lOrExp;

// 左值表达式
lVal: Ident ('[' exp ']')*;

// 基本表达式
primaryExp:
	'(' exp ')'	# groupedExpression
	| lVal		# leftValueExpression
	| number	# numberExpression;

// 数值（常数） （实际上都是非负数，负数用单目运算符实现）
number: IntConst | FloatConst;

// 一元表达式
unaryExp:
	primaryExp						# primaryUnaryExpression
	| Ident '(' funcRParams? ')'	# functionCall
	| unaryOp unaryExp				# unaryOperatorExpression;

// 单目运算符
unaryOp: '+' | '-' | '!';

// 函数实参表
funcRParams: exp (',' exp)*;

// 乘除模表达式
mulExp: unaryExp | mulExp ('*' | '/' | '%') unaryExp;

// 加减表达式
addExp: mulExp | addExp ('+' | '-') mulExp;

// 关系表达式
relExp: addExp | relExp ('<' | '>' | '<=' | '>=') addExp;

// 相等性表达式
eqExp: relExp | eqExp ('==' | '!=') relExp;

// 逻辑与表达式
lAndExp: eqExp | lAndExp '&&' eqExp;

// 逻辑或表达式
lOrExp: lAndExp | lOrExp '||' lAndExp;

// ?常量表达式（Ident 必须是常量）
constExp: addExp;

// 词法规则
Ident: [a-zA-Z_][a-zA-Z_0-9]*;

// 整型常量
IntConst: DecimalConst | OctalConst | HexadecimalConst;

DecimalConst: NonzeroDigit Digit*;
OctalConst: '0' OctalDigit*;
HexadecimalConst: HexadecimalPrefix HexadecimalDigit+;

HexadecimalPrefix: '0' [xX];
NonzeroDigit: [1-9];
Digit: [0-9];
OctalDigit: [0-7];
HexadecimalDigit: [0-9a-fA-F];

// 浮点型常量（简化版，完整实现需参考C99标准）
FloatConst:
	Digit+ '.' Digit* ExponentPart?
	| '.' Digit+ ExponentPart?
	| Digit+ ExponentPart;

ExponentPart: [eE] [+-]? Digit+;

WS: [ \t\r\n]+ -> skip;
COMMENT: '//' ~[\r\n]* -> skip;
BLOCK_COMMENT: '/*' .*? '*/' -> skip;