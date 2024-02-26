#include "pch.h"

#include <string>
#include <string_view>

#include "../CmdCalculatorTestDoubles/StubDynamicExpressionNode.h"
#include "../CmdCalculator/ExpressionNode.h"
#include "../CmdCalculator/dynamic_mathast.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubDynamicExpressionNodeTests, DynamicExpressionNode$satisfies$ExpressionNode$concept)
	{
		static_assert
		(
			::CmdCalculator::MathAst::ExpressionNode
			<
				CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionNode<std::string>
			>
		);
	}

#pragma endregion
}