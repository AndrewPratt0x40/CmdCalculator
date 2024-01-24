#include "pch.h"

#include "../CmdCalculator/TrueGroupingAntlrContextView.h"
#include "../CmdCalculator/GroupingAntlrContext.h"


namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(TrueGroupingAntlrContextViewTests, TrueGroupingAntlrContextView$satisfies$GroupingAntlrContext)
	{
		static_assert
		(
			CmdCalculator::GroupingAntlrContext<CmdCalculator::TrueGroupingAntlrContextView>
		);
	}

#pragma endregion
}