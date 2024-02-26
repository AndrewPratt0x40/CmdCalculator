#include "pch.h"

#include <string_view>

#include "../CmdCalculatorTestDoubles/StubExpressionAntlrContext.h"
#include "../CmdCalculator/ExpressionAntlrContext.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubExpressionAntlrContextTests, StubExpressionAntlrContext$satisfies$ExpressionAntlrContext$concept)
	{
		static_assert
		(
			::CmdCalculator::ExpressionAntlrContext
			<
				CmdCalculatorTestDoubles::StubExpressionAntlrContext
			>
		);
	}

#pragma endregion
}