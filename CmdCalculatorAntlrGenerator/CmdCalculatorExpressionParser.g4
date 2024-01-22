parser grammar CmdCalculatorExpressionParser;
options
{
	tokenVocab=CmdCalculatorExpressionLexer;
}

wholeful_number_literal:
	whole_part=INTEGER
	decimal_point=DECIMAL_POINT?
	fractional_part=INTEGER?
;

wholeless_number_literal:
	decimal_point=DECIMAL_POINT
	fractional_part=INTEGER
;

number_literal:
	wholeful_number_literal
	| wholeless_number_literal
;

sign_operator:
	ADDITION_OR_POSITIVE_OPERATOR #PositiveSignOperator
	| SUBTRACTION_OR_NEGATIVE_OPERATOR #NegativeSignOperator
;

sign_operation:
	sign_operator_value=sign_operator
	inner_trivia=TRIVIA?
	operand_value=operand
;

sqrt_operation:
	SQRT_OPERATOR
	inner_trivia=TRIVIA?
	operand_value=operand
;

grouping:
	GROUPING_START_BRACKET
	inner_leading_trivia=TRIVIA?
	inner_expression=expression
	inner_trailing_trivia=TRIVIA?
	GROUPING_END_BRACKET
;

grouping_tail_multiplicand:
	inner_trivia=TRIVIA?
	grouping_value=grouping
;

grouping_multiplication:
	head_multiplicand=non_grouping_multiplication_operand
	tail_multiplicands+=grouping_tail_multiplicand
;

absolute_value_operation:
	ABSOLUTE_VALUE_BRACKET
	inner_leading_trivia=TRIVIA?
	inner_expression=expression
	inner_trailing_trivia=TRIVIA?
	ABSOLUTE_VALUE_BRACKET
;

non_grouping_multiplication_operand:
	number_literal
	| sign_operation
	| sqrt_operation
	| grouping
	| absolute_value_operation
;

operand:
	non_grouping_multiplication_operand
	| grouping_multiplication
;

binary_operator:
	ADDITION_OR_POSITIVE_OPERATOR #AdditionOperator
	| SUBTRACTION_OR_NEGATIVE_OPERATOR #SubtractionOperator
	| MULTIPLICATION_OPERATOR #MultiplicationOperator
	| DIVISION_OPERATOR #DivisionOperator
	| EXPONENTIATION_OPERATOR #ExponentiationOperator
	| NTH_ROOT_OPERATOR #NthRootOperator
	| MODULO_OPERATOR #ModuloOperator
;

operation_part_pair:
	operator_leading_trivia=TRIVIA?
	operator_value=binary_operator
	operator_trailing_trivia=TRIVIA?
	operand_value=operand
;

expression:
	head_operand=operand
	operation_part_pairs+=operation_part_pair*
;

full_expression:
	leading_trivia=TRIVIA?
	expression_value=expression
	trailing_trivia=TRIVIA?
	EOF
;