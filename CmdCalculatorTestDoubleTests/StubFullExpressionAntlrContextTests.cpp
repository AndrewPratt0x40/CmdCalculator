#include "pch.h"

#include <string_view>

#include "../CmdCalculatorTestDoubles/StubFullExpressionAntlrContext.h"
#include "../CmdCalculator/FullExpressionAntlrContext.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubFullExpressionAntlrContextTests, StubFullExpressionAntlrContext$satisfies$FullExpressionAntlrContext$concept)
	{
		static_assert
		(
			CmdCalculator::FullExpressionAntlrContext
			<
				CmdCalculatorTestDoubles::StubFullExpressionAntlrContext<>
			>
		);
	}

#pragma endregion
}