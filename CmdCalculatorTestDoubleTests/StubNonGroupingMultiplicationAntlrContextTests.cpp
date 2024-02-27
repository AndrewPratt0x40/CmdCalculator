#include "pch.h"

#include <string_view>

#include "../CmdCalculatorTestDoubles/StubNonGroupingMultiplicationAntlrContext.h"
#include "../CmdCalculator/NonGroupingMultiplicationAntlrContext.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubNonGroupingMultiplicationAntlrContextTests, StubNonGroupingMultiplicationAntlrContext$satisfies$NonGroupingMultiplicationAntlrContext$concept)
	{
		static_assert
		(
			CmdCalculator::NonGroupingMultiplicationAntlrContext
			<
				CmdCalculatorTestDoubles::StubNonGroupingMultiplicationAntlrContext
			>
		);
	}

#pragma endregion
}