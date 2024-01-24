#include "pch.h"

#include "../CmdCalculator/TrueOperandAntlrContextView.h"
#include "../CmdCalculator/OperandAntlrContext.h"


namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(TrueOperandAntlrContextViewTests, TrueOperandAntlrContextView$satisfies$OperandAntlrContext)
	{
		static_assert
		(
			CmdCalculator::OperandAntlrContext<CmdCalculator::TrueOperandAntlrContextView>
		);
	}

#pragma endregion
}