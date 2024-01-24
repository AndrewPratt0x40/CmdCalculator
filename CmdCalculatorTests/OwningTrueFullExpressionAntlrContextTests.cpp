#include "pch.h"

#include "../CmdCalculator/OwningTrueFullExpressionAntlrContext.h"
#include "../CmdCalculator/FullExpressionAntlrContext.h"


namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(OwningTrueFullExpressionAntlrContext, OwningTrueFullExpressionAntlrContext$FullExpressionAntlrContext)
	{
		static_assert
		(
			CmdCalculator::FullExpressionAntlrContext<CmdCalculator::OwningTrueFullExpressionAntlrContext>
		);
	}

#pragma endregion
}