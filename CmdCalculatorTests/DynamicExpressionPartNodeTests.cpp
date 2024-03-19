#include "pch.h"

#include <string>

#include "../CmdCalculator/DynamicExpressionPartNode.h"
#include "../CmdCalculator/ExpressionPartNode.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(DynamicExpressionPartNodeTests, DynamicExpressionPartNode$satisfies$ExpressionPartNode$concept)
	{
		static_assert
		(
			CmdCalculator::MathAst::ExpressionPartNode<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>>
		);
	}

#pragma endregion
}