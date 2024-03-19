#include "pch.h"

#include "../CmdCalculator/TrueWholefulNumberLiteralAntlrContextView.h"
#include "../CmdCalculator/WholefulNumberLiteralAntlrContext.h"


namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(TrueWholefulNumberLiteralAntlrContextViewTests, TrueWholefulNumberLiteralAntlrContextView$satisfies$WholefulNumberLiteralAntlrContext)
	{
		static_assert
		(
			CmdCalculator::WholefulNumberLiteralAntlrContext<CmdCalculator::TrueWholefulNumberLiteralAntlrContextView>
		);
	}

#pragma endregion
}