#include "pch.h"

#include <string_view>

#include "../CmdCalculatorTestDoubles/StubTrackingFullExpressionAntlrContext.h"
#include "../CmdCalculator/FullExpressionAntlrContext.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubTrackingFullExpressionAntlrContextTests, StubTrackingFullExpressionAntlrContext$satisfies$FullExpressionAntlrContext$concept)
	{
		static_assert
		(
			CmdCalculator::FullExpressionAntlrContext
			<
				CmdCalculatorTestDoubles::StubTrackingFullExpressionAntlrContext<std::string_view>
			>
		);
	}

#pragma endregion
}