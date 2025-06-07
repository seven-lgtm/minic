grammar MiniC;

// 词法规则名总是以大写字母开头

// 语法规则名总是以小写字母开头

// 每个非终结符尽量多包含闭包、正闭包或可选符等的EBNF范式描述

// 若非终结符由多个产生式组成，则建议在每个产生式的尾部追加# 名称来区分，详细可查看非终结符statement的描述

// 语法规则描述：EBNF范式

// 源文件编译单元定义
compileUnit: (funcDef | varDecl)* EOF;

// 函数定义，支持形参，支持返回void类型  int function(int a, int b) {}
funcDef: returnType T_ID T_L_PAREN (paramList)?  T_R_PAREN block; 

//函数返回值类型
returnType: T_INT
           | T_VOID;  

//函数参数 int a,int b
paramList: param (T_COMMA param)*;
 
 //  int a
param: basicType T_ID;

// 语句块看用作函数体，这里允许多个语句，并且不含任何语句
block: T_L_BRACE blockItemList? T_R_BRACE;

// 每个ItemList可包含至少一个Item
blockItemList: blockItem+;

// 每个Item可以是一个语句，或者变量声明语句
blockItem: statement | varDecl;

// 变量声明，变量的初始化
varDecl: basicType varDef (T_COMMA varDef)*  T_SEMICOLON;

// 基本类型
basicType: T_INT;
       

// 变量定义
//varDef: T_ID;

//  statement
statement:
	T_RETURN expr? T_SEMICOLON			# returnStatement   //允许函数返回值为空return;
	| lVal T_ASSIGN expr T_SEMICOLON	# assignStatement
	| block								# blockStatement
	| expr? T_SEMICOLON					# expressionStatement
	| T_IF T_L_PAREN expr T_R_PAREN statement (T_ELSE statement)?   # ifStatement    
	| T_WHILE T_L_PAREN expr T_R_PAREN statement    # whileStatement
	| T_BREAK  T_SEMICOLON        # breakStatement
	| T_CONTINUE T_SEMICOLON      #continueStatement;


// 优先级： 逻辑非  乘除取模 加减 关系运算 逻辑与 逻辑或
// 表达式文法 expr 
expr: logicalOrExp;
logicalOrExp: logicalAndExp (T_OR logicalAndExp)*;
logicalAndExp: relExp (T_AND relExp)*;

//关系表达式（优先级低于加减，高于赋值） 
relExp: addExp (relOp addExp)*;

relOp : T_LT | T_GT|  T_LE | T_GE | T_EQ  | T_NE;


// 加减表达式（最低优先级）
addExp: mulExp (addOp mulExp)*;
addOp: T_ADD | T_SUB;

// 乘除模表达式（中等优先级）
mulExp: unaryExp (mulOp unaryExp)*;
mulOp: T_MUL | T_DIV | T_MOD;


/* 
unaryExp: 
	(T_SUB | T_NOT)* (primaryExp | T_ID T_L_PAREN realParamList? T_R_PAREN)  // 支持连续负号
	| primaryExp // 基础表达式
	| T_ID T_L_PAREN realParamList? T_R_PAREN;								 // 函数调用
*/

// 一元表达式（最高优先级）
unaryExp:
	(T_SUB | T_NOT)* primaryExp // 支持连续负号 取非
	| primaryExp // 基础表达式
	| T_ID T_L_PAREN realParamList? T_R_PAREN; // 函数调用

// 基本表达式：括号表达式、整数、左值表达式
primaryExp:
	T_L_PAREN expr T_R_PAREN
	| lVal
	| T_DECIMAL // 十进制
	| T_OCTAL // 八进制
	| T_HEX; // 十六进制

// 实参列表
realParamList: expr (T_COMMA expr)*;

// 变量声明，支持变量的初始化
varDef: T_ID (T_ASSIGN expr)?; // 添加初始化表达式支持
//int a,b=3;
//int a=6,n=9;
// int a=3,b,c=90

// 左值表达式
lVal: T_ID;

// 用正规式来进行词法规则的描述

T_L_PAREN: '(';
T_R_PAREN: ')';
T_SEMICOLON: ';';
T_L_BRACE: '{';
T_R_BRACE: '}';

T_ASSIGN: '=';
T_COMMA: ',';

T_ADD: '+';
T_SUB: '-';
T_MOD: '%';
T_MUL: '*';
T_DIV: '/';

//关系运算
T_LT: '<';  //less than 
T_GT: '>';
T_LE: '<=';  
T_GE: '>=';
T_EQ: '==';
T_NE: '!=';

//逻辑运算
T_AND:'&&';
T_OR: '||';
T_NOT:'!';





// 要注意关键字同样也属于T_ID，因此必须放在T_ID的前面，否则会识别成T_ID
T_RETURN: 'return';
T_INT: 'int';
T_VOID: 'void';
T_IF: 'if';
T_ELSE: 'else';
T_BREAK:'break';
T_CONTINUE:'continue';
T_WHILE:'while';

T_ID: [a-zA-Z_][a-zA-Z0-9_]*;

T_DECIMAL: '0' | [1-9][0-9]*; // 十进制（0 或非零开头）
T_OCTAL: '0' [0-7]+; // 八进制（以0开头，后跟0-7）
T_HEX: '0' [xX] [0-9a-fA-F]+; // 十六进制（0x或0X开头）


// 行注释和块注释（跳过）
LINE_COMMENT: '//' ~[\r\n]* -> skip;
BLOCK_COMMENT: '/*' .*? '*/' -> skip;

/* 空白符丢弃 */
WS: [ \r\n\t]+ -> skip;