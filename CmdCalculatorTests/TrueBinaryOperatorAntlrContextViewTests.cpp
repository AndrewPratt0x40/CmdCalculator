#include "pch.h"

#include "../CmdCalculator/TrueBinaryOperatorAntlrContextView.h"
#include "../CmdCalculator/BinaryOperatorAntlrContext.h"


namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(TrueBinaryOperatorAntlrContextViewTests, TrueBinaryOperatorAntlrContextView$satisfies$BinaryOperatorAntlrContext)
	{
		static_assert
		(
			CmdCalculator::BinaryOperatorAntlrContext<CmdCalculator::TrueBinaryOperatorAntlrContextView>
		);
	}

#pragma endregion
}