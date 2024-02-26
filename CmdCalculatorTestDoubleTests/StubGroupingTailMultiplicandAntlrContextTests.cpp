#include "pch.h"

#include <string_view>

#include "../CmdCalculatorTestDoubles/StubGroupingTailMultiplicandAntlrContext.h"
#include "../CmdCalculator/GroupingTailMultiplicandAntlrContext.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubGroupingTailMultiplicandAntlrContextTests, StubGroupingTailMultiplicandAntlrContext$satisfies$GroupingTailMultiplicandAntlrContext$concept)
	{
		static_assert
		(
			::CmdCalculator::GroupingTailMultiplicandAntlrContext
			<
				CmdCalculatorTestDoubles::StubGroupingTailMultiplicandAntlrContext
			>
		);
	}

#pragma endregion
}