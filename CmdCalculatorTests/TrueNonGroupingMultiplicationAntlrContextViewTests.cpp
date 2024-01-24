#include "pch.h"

#include "../CmdCalculator/TrueNonGroupingMultiplicationAntlrContextView.h"
#include "../CmdCalculator/NonGroupingMultiplicationAntlrContext.h"


namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(TrueNonGroupingMultiplicationAntlrContextViewTests, TrueNonGroupingMultiplicationAntlrContextView$satisfies$NonGroupingMultiplicationAntlrContext)
	{
		static_assert
		(
			CmdCalculator::NonGroupingMultiplicationAntlrContext<CmdCalculator::TrueNonGroupingMultiplicationAntlrContextView>
		);
	}

#pragma endregion
}