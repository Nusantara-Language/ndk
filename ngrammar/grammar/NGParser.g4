parser grammar NGParser;

options {
	language = Cpp;
    tokenVocab = NGLexer;
}

/* Parser */
init: loadFile* statement* EOF;

loadFile: KW_MUAT LIT_TEKS;

statement: expression SEMICOLON;

expression: logicalOrExpression;

logicalOrExpression:
	logicalAndExpression (OP_OR logicalAndExpression)*;

logicalAndExpression:
	relationalExpression (OP_AND relationalExpression)*;

relationalExpression:
	additiveExpression (
		OP_EQ additiveExpression
		| OP_NEQ additiveExpression
		| OP_LT additiveExpression
		| OP_GT additiveExpression
		| OP_LEQ additiveExpression
		| OP_GEQ additiveExpression
	)*;

additiveExpression:
	multiplicativeExpression (
		OP_ADD multiplicativeExpression
		| OP_SUB multiplicativeExpression
	)*;

multiplicativeExpression:
	unaryExpression (
		OP_MUL unaryExpression
		| OP_DIV unaryExpression
		| OP_MOD unaryExpression
	)*;

unaryExpression:
	OP_NOT unaryExpression
	| OP_BW_NOT unaryExpression
	| OP_INC unaryExpression
	| OP_DEC unaryExpression
	| primaryExpression;

primaryExpression:
	IDENTIFIER
	| LIT_BUL
	| LIT_DES
	| LIT_KAR
	| LIT_TEKS
	| LIT_BENAR
	| LIT_SALAH
	| PAREN_OPEN expression PAREN_CLOSE;