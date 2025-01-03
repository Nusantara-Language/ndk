lexer grammar NGLexer;

options {
	language = Cpp;
}

// Whitespace
WS: [ \t\r\n]+ -> skip;

// Comments
LINE_COMMENT: '//' ~[\r\n]* -> skip;
BLOCK_COMMENT: '/*' .*? '*/' -> skip;

// Brackets
BRACE_OPEN: '{';
BRACE_CLOSE: '}';
PAREN_OPEN: '(';
PAREN_CLOSE: ')';

// Keywords
KW_MUAT: 'muat';
KW_BUL: 'bul';
KW_DES: 'des';
KW_TEKS: 'teks';
KW_KAR: 'kar';
KW_LOGIC: 'log';

// Operators
OP_INC: '++';
OP_DEC: '--';
OP_ADD_ASSIGN: '+=';
OP_SUB_ASSIGN: '-=';
OP_MUL_ASSIGN: '*=';
OP_DIV_ASSIGN: '/=';
OP_MOD_ASSIGN: '%=';
OP_BW_LS_ASSIGN: '<<=';
OP_BW_RS_ASSIGN: '>>=';
OP_BW_AND_ASSIGN: '&=';
OP_BW_OR_ASSIGN: '|=';
OP_BW_XOR_ASSIGN: '^=';

// Arithmetic Operators
OP_ADD: '+';
OP_SUB: '-';
OP_MUL: '*';
OP_DIV: '/';
OP_MOD: '%';

// Relational Operators
OP_EQ: '==';
OP_NEQ: '!=';
OP_LEQ: '<=';
OP_GEQ: '>=';
OP_LT: '<';
OP_GT: '>';

// Logical Operators
OP_NOT: '!';
OP_AND: '&&';
OP_OR: '||';

// Bitwise Operators
OP_BW_LS: '<<';
OP_BW_RS: '>>';
OP_BW_AND: '&';
OP_BW_OR: '|';
OP_BW_XOR: '^';
OP_BW_NOT: '~';

// Literals
LIT_DES: '-'? [0-9]+ '.' [0-9]+;
LIT_BUL: '-'? [0-9]+;
LIT_KAR: '\'' ~'\''* '\'';
LIT_TEKS: '"' ~'"'* '"';
LIT_BENAR: 'benar';
LIT_SALAH: 'salah';

// Miscellaneous Tokens
COMMA: ',';
OP_ASSIGN: '=';
SEMICOLON: ';';
IDENTIFIER: [a-zA-Z_][a-zA-Z0-9_]*;