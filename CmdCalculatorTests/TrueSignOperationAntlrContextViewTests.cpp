#include "pch.h"

#include "../CmdCalculator/TrueSignOperationAntlrContextView.h"
#include "../CmdCalculator/SignOperationAntlrContext.h"


namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(TrueSignOperationAntlrContextViewTests, TrueSignOperationAntlrContextView$satisfies$SignOperationAntlrContext)
	{
		static_assert
		(
			CmdCalculator::SignOperationAntlrContext<CmdCalculator::TrueSignOperationAntlrContextView>
		);
	}

#pragma endregion
}