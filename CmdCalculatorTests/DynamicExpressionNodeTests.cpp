#include "pch.h"

#include <string>

#include "../CmdCalculator/DynamicExpressionNode.h"
#include "../CmdCalculator/ExpressionNode.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(DynamicExpressionNodeTests, DynamicExpressionNode$satisfies$ExpressionNode$concept)
	{
		static_assert
		(
			CmdCalculator::MathAst::ExpressionNode<CmdCalculator::MathAst::DynamicExpressionNode<std::string>>
		);
	}

#pragma endregion
}