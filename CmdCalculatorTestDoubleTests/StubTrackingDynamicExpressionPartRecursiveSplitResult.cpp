#include "pch.h"

#include <string>
#include <ranges>

#include "../CmdCalculator/DynamicExpressionPartRecursiveSplitResult.h"
#include "../CmdCalculatorTestDoubles/StubTrackingDynamicExpressionPartRecursiveSplitResult.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubTrackingDynamicExpressionPartRecursiveSplitResultTests, StubTrackingDynamicExpressionPartRecursiveSplitResult$satisfies$DynamicExpressionPartRecursiveSplitResult$concept)
	{
		static_assert
		(
			CmdCalculator::DynamicExpressionPartRecursiveSplitResult
			<
				CmdCalculatorTestDoubles::StubTrackingDynamicExpressionPartRecursiveSplitResult
				<
					std::ranges::empty_view<std::reference_wrapper<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>>>,
					std::string
				>
			>
		);
	}

#pragma endregion
}