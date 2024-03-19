#include "pch.h"

#include "../CmdCalculator/TrueExpressionAntlrContextView.h"
#include "../CmdCalculator/ExpressionAntlrContext.h"


namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(TrueExpressionAntlrContextViewTests, TrueExpressionAntlrContextView$satisfies$ExpressionAntlrContext)
	{
		static_assert
		(
			CmdCalculator::ExpressionAntlrContext<CmdCalculator::TrueExpressionAntlrContextView>
		);
	}

#pragma endregion
}