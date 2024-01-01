grammar CmdCalculatorInputExpression;

Whitespace: [\p{White_Space}]+;
Foo: 'a';

//expression: Whitespace+;
expression: Foo+;