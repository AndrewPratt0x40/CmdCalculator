#include "pch.h"

#include "../CmdCalculator/TrueGroupingTailMultiplicandAntlrContextView.h"
#include "../CmdCalculator/GroupingTailMultiplicandAntlrContext.h"


namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(TrueGroupingTailMultiplicandAntlrContextViewTests, TrueGroupingTailMultiplicandAntlrContextView$satisfies$GroupingTailMultiplicandAntlrContext)
	{
		static_assert
		(
			CmdCalculator::GroupingTailMultiplicandAntlrContext<CmdCalculator::TrueGroupingTailMultiplicandAntlrContextView>
		);
	}

#pragma endregion
}