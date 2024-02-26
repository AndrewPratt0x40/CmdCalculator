#include "pch.h"

#include <string>

#include "../CmdCalculatorTestDoubles/StubTrackingMathAstNode.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubTrackingMathAstNodeTests, StubTrackingMathAstNode$satisfies$MathAstNode$concept)
	{
		static_assert
		(
			::CmdCalculator::MathAst::MathAstNode<CmdCalculatorTestDoubles::MathAst::StubTrackingMathAstNode<std::string, std::string_view>>
		);
	}

#pragma endregion
}