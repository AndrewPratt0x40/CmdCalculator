grammar CmdCalculatorExpression;

fragment WHITESPACE_CHAR: [ \t\n\r];
SEP: WHITESPACE_CHAR+;

fragment DIGIT: [0-9];
INT: DIGIT+;

OPERATOR: '+' | '-' | '*' | '/';

operand: INT;

expression: SEP? operand (SEP? OPERATOR SEP? operand)+ SEP?;

full_expression: expression;