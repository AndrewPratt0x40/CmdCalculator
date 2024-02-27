#include "pch.h"

#include <string_view>

#include "../CmdCalculatorTestDoubles/StubAbsoluteValueOperationAntlrContext.h"
#include "../CmdCalculator/AbsoluteValueOperationAntlrContext.h"
#include "../CmdCalculator/utilities.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubAbsoluteValueOperationAntlrContextTests, StubAbsoluteValueOperationAntlrContext$satisfies$AbsoluteValueOperationAntlrContext$concept)
	{
		static_assert
		(
			CmdCalculator::AbsoluteValueOperationAntlrContext
			<
				CmdCalculatorTestDoubles::StubAbsoluteValueOperationAntlrContext
			>
		);
	}

#pragma endregion
}