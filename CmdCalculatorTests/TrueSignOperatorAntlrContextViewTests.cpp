#include "pch.h"

#include "../CmdCalculator/TrueSignOperatorAntlrContextView.h"
#include "../CmdCalculator/SignOperatorAntlrContext.h"


namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(TrueSignOperatorAntlrContextViewTests, TrueSignOperatorAntlrContextView$satisfies$SignOperatorAntlrContext)
	{
		static_assert
		(
			CmdCalculator::SignOperatorAntlrContext<CmdCalculator::TrueSignOperatorAntlrContextView>
		);
	}

#pragma endregion
}