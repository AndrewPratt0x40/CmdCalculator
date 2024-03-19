#include "pch.h"

#include "../CmdCalculator/TrueAbsoluteValueOperationAntlrContextView.h"
#include "../CmdCalculator/AbsoluteValueOperationAntlrContext.h"


namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(TrueAbsoluteValueOperationAntlrContextViewTests, TrueAbsoluteValueOperationAntlrContextView$satisfies$AbsoluteValueOperationAntlrContext)
	{
		static_assert
		(
			CmdCalculator::AbsoluteValueOperationAntlrContext<CmdCalculator::TrueAbsoluteValueOperationAntlrContextView>
		);
	}

#pragma endregion
}