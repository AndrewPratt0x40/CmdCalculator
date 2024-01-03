#include <iostream>

#include "../Antlr4CppRuntime/src/antlr4-runtime.h"
#include "../CmdCalculator/antlr_output/CmdCalculatorExpressionLexer.h"
#include "../CmdCalculator/antlr_output/CmdCalculatorExpressionListener.h"
#include "../CmdCalculator/antlr_output/CmdCalculatorExpressionParser.h"

int main()
{
	antlr4::ANTLRInputStream inputStream{ " 12 + 2 - 9082 *7/3 " };
	CmdCalculatorExpressionLexer lexer{ &inputStream };
	antlr4::CommonTokenStream tokenStream{ &lexer };
	CmdCalculatorExpressionParser parser{ &tokenStream };
	parser.full_expression();

	std::cout << "Hello World!\n";
}