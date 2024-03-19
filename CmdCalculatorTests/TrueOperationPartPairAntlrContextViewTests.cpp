#include "pch.h"

#include "../CmdCalculator/TrueOperationPartPairAntlrContextView.h"
#include "../CmdCalculator/OperationPartPairAntlrContext.h"


namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(TrueOperationPartPairAntlrContextViewTests, TrueOperationPartPairAntlrContextView$satisfies$OperationPartPairAntlrContext)
	{
		static_assert
		(
			CmdCalculator::OperationPartPairAntlrContext<CmdCalculator::TrueOperationPartPairAntlrContextView>
		);
	}

#pragma endregion
}