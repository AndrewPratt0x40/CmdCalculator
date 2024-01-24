#include "pch.h"

#include "../CmdCalculator/TrueGroupingMultiplicationAntlrContextView.h"
#include "../CmdCalculator/GroupingMultiplicationAntlrContext.h"


namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(TrueGroupingMultiplicationAntlrContextViewTests, TrueGroupingMultiplicationAntlrContextView$satisfies$GroupingMultiplicationAntlrContext)
	{
		static_assert
		(
			CmdCalculator::GroupingMultiplicationAntlrContext<CmdCalculator::TrueGroupingMultiplicationAntlrContextView>
		);
	}

#pragma endregion
}