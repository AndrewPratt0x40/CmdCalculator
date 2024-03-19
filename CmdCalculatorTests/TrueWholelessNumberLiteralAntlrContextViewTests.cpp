#include "pch.h"

#include "../CmdCalculator/TrueWholelessNumberLiteralAntlrContextView.h"
#include "../CmdCalculator/WholelessNumberLiteralAntlrContext.h"


namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(TrueWholelessNumberLiteralAntlrContextViewTests, TrueWholelessNumberLiteralAntlrContextView$satisfies$WholelessNumberLiteralAntlrContext)
	{
		static_assert
		(
			CmdCalculator::WholelessNumberLiteralAntlrContext<CmdCalculator::TrueWholelessNumberLiteralAntlrContextView>
		);
	}

#pragma endregion
}