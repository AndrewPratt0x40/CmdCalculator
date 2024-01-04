#include <iostream>

#include "../submodules/Antlr4CppRuntime/src/antlr4-runtime.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionLexer.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionBaseListener.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"

int main()
{
	antlr4::ANTLRInputStream inputStream{ " 12 + 2 - 9082 *7/3 " };
	CmdCalculator::Antlr::CmdCalculatorExpressionLexer lexer{&inputStream};
	antlr4::CommonTokenStream tokenStream{ &lexer };
	CmdCalculator::Antlr::CmdCalculatorExpressionParser parser{ &tokenStream };
	auto* fullExpression{ parser.full_expression() };
	CmdCalculator::Antlr::CmdCalculatorExpressionBaseListener listener{};
	antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, fullExpression);

	std::cout << "Hello World!\n";
}