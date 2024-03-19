#include "pch.h"

#include <string_view>

#include "../CmdCalculatorTestDoubles/StubGroupingAntlrContext.h"
#include "../CmdCalculator/GroupingAntlrContext.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubGroupingAntlrContextTests, StubGroupingAntlrContext$satisfies$GroupingAntlrContext$concept)
	{
		static_assert
		(
			CmdCalculator::GroupingAntlrContext
			<
				CmdCalculatorTestDoubles::StubGroupingAntlrContext
			>
		);
	}

#pragma endregion
}