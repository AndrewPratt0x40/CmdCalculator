#include "pch.h"

#include <string>

#include "../CmdCalculatorTestDoubles/StubMathAstNode.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubMathAstNodeTests, StubMathAstNode$satisfies$MathAstNode$concept)
	{
		static_assert
		(
			::CmdCalculator::MathAst::MathAstNode<CmdCalculatorTestDoubles::MathAst::StubMathAstNode<std::string>>
		);
	}

#pragma endregion
}