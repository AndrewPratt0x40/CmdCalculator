#include <iostream>

#include "../submodules/Antlr4CppRuntime/src/antlr4-runtime.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionLexer.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionListener.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"

int main()
{
	antlr4::ANTLRInputStream inputStream{ " 12 + 2 - 9082 *7/3 " };
	/*CmdCalculator::Antlr::CmdCalculatorExpressionLexer lexer{&inputStream};
	antlr4::CommonTokenStream tokenStream{ &lexer };
	CmdCalculator::Antlr::CmdCalculatorExpressionParser parser{ &tokenStream };*/
	//parser.full_expression();

	std::cout << "Hello World!\n";
}