#include "pch.h"

#include <string>
#include <string_view>

#include "../CmdCalculatorTestDoubles/StubDynamicExpressionPartNode.h"
#include "../CmdCalculator/ExpressionNode.h"
#include "../CmdCalculator/dynamic_mathast.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubDynamicExpressionPartNodeTests, DynamicExpressionPartNode$satisfies$ExpressionPartNode$concept)
	{
		static_assert
		(
			::CmdCalculator::MathAst::ExpressionPartNode
			<
				CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>
			>
		);
	}

#pragma endregion
}