#include "pch.h"

#include <string>

#include "../CmdCalculator/DynamicExpressionPartRecursiveSplitResult.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionPartRecursiveSplitResult.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubDynamicExpressionPartRecursiveSplitResultTests, StubDynamicExpressionPartRecursiveSplitResult$satisfies$DynamicExpressionPartRecursiveSplitResult$concept)
	{
		static_assert
		(
			CmdCalculator::DynamicExpressionPartRecursiveSplitResult
			<
				CmdCalculatorTestDoubles::StubDynamicExpressionPartRecursiveSplitResult
				<
					std::string
				>
			>
		);
	}

#pragma endregion
}