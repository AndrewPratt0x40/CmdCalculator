#include "pch.h"

#include "../CmdCalculator/TrueSqrtOperationAntlrContextView.h"
#include "../CmdCalculator/SqrtOperationAntlrContext.h"


namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(TrueSqrtOperationAntlrContextViewTests, TrueSqrtOperationAntlrContextView$satisfies$SqrtOperationAntlrContext)
	{
		static_assert
		(
			CmdCalculator::SqrtOperationAntlrContext<CmdCalculator::TrueSqrtOperationAntlrContextView>
		);
	}

#pragma endregion
}