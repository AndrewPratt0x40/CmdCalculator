#include "pch.h"

#include <string>

#include "../CmdCalculator/DynamicExpressionPartSingleSplitResult.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionPartSingleSplitResult.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubDynamicExpressionPartSingleSplitResultTests, StubDynamicExpressionPartSingleSplitResult$satisfies$DynamicExpressionPartSingleSplitResult$concept)
	{
		static_assert
		(
			::CmdCalculator::DynamicExpressionPartSingleSplitResult
			<
				CmdCalculatorTestDoubles::StubDynamicExpressionPartSingleSplitResult
				<
					std::string
				>
			>
		);
	}

#pragma endregion
}