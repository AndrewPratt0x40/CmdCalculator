#include "pch.h"

#include "../CmdCalculator/TrueNumberLiteralAntlrContextView.h"
#include "../CmdCalculator/NumberLiteralAntlrContext.h"


namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(TrueNumberLiteralAntlrContextViewTests, TrueNumberLiteralAntlrContextView$satisfies$NumberLiteralAntlrContext)
	{
		static_assert
		(
			CmdCalculator::NumberLiteralAntlrContext<CmdCalculator::TrueNumberLiteralAntlrContextView>
		);
	}

#pragma endregion
}