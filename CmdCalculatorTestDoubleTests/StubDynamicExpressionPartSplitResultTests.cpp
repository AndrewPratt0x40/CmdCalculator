#include "pch.h"

#include <string>

#include "../CmdCalculator/DynamicExpressionPartSplitResult.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionPartSplitResult.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubDynamicExpressionPartSplitResultTests, StubDynamicExpressionPartSplitResult$satisfies$DynamicExpressionPartSplitResult$concept)
	{
		static_assert
		(
			CmdCalculator::DynamicExpressionPartSplitResult
			<
				CmdCalculatorTestDoubles::StubDynamicExpressionPartSplitResult
				<
					std::string
				>
			>
		);
	}

#pragma endregion
}