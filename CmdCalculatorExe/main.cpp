#include <iostream>
#include <memory>

#include "../submodules/Antlr4CppRuntime/src/antlr4-runtime.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionLexer.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"

int main()
{
	antlr4::ANTLRInputStream inputStream{ " A12 + 2 - 9082 *7/3 " };
	CmdCalculator::Antlr::CmdCalculatorExpressionLexer lexer{&inputStream};
	lexer.removeErrorListeners();

	antlr4::CommonTokenStream tokenStream{ &lexer };

	CmdCalculator::Antlr::CmdCalculatorExpressionParser parser{ &tokenStream };
	const auto parserErrorHandler{ std::make_shared<antlr4::BailErrorStrategy>() };
	parser.setErrorHandler(parserErrorHandler);
	parser.removeErrorListeners();

	auto* fullExpression{ parser.full_expression() };
	//const std::string foo{ expression->operation_parts[0]->};

	//std::cout << "The first operand is: " << foo;
}