grammar CmdCalculatorExpression;

fragment WhitespaceChar: [ \t\n\r];
Trivia: WhitespaceChar+;

fragment Digit: [0-9];
Integer: Digit+;

BinaryOperator: '+' | '-' | '*' | '/';

operand: Integer;

mid_operation_part: operator_leading_trivia=Trivia? BinaryOperator operator_trailing_trivia=Trivia? operand;

expression: leading_trivia=Trivia? head_operand=operand operation_parts+=mid_operation_part* trailing_trivia=Trivia?;