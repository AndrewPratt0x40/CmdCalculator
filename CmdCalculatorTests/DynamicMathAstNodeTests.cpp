#include "pch.h"

#include <string>

#include "../CmdCalculator/DynamicMathAstNode.h"
#include "../CmdCalculator/MathAstNode.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(DynamicMathAstNodeTests, DynamicMathAstNode$satisfies$MathAstNode$concept)
	{
		static_assert
		(
			CmdCalculator::MathAst::MathAstNode<CmdCalculator::MathAst::DynamicMathAstNode<std::string>>
		);
	}

#pragma endregion
}