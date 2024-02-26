#include "pch.h"

#include <string_view>

#include "../CmdCalculatorTestDoubles/StubGroupingMultiplicationAntlrContext.h"
#include "../CmdCalculator/GroupingMultiplicationAntlrContext.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubGroupingMultiplicationAntlrContextTests, StubGroupingMultiplicationAntlrContext$satisfies$GroupingMultiplicationAntlrContext$concept)
	{
		static_assert
		(
			::CmdCalculator::GroupingMultiplicationAntlrContext
			<
				CmdCalculatorTestDoubles::StubGroupingMultiplicationAntlrContext
			>
		);
	}

#pragma endregion
}