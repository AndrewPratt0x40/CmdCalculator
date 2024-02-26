#include "pch.h"

#include <string>
#include <string_view>

#include "../CmdCalculatorTestDoubles/StubTrackingDynamicExpressionNode.h"
#include "../CmdCalculator/ExpressionNode.h"
#include "../CmdCalculator/dynamic_mathast.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubTrackingDynamicExpressionNodeTests, TrackingDynamicExpressionNode$satisfies$ExpressionNode$concept)
	{
		static_assert
		(
			::CmdCalculator::MathAst::ExpressionNode
			<
				CmdCalculatorTestDoubles::MathAst::StubTrackingDynamicExpressionNode
				<
					std::string,
					std::string_view
				>
			>
		);
	}

#pragma endregion
}