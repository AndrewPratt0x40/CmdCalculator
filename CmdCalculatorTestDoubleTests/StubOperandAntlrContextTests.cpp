#include "pch.h"

#include <string_view>

#include "../CmdCalculatorTestDoubles/StubOperandAntlrContext.h"
#include "../CmdCalculator/OperandAntlrContext.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubOperandAntlrContextTests, StubOperandAntlrContext$satisfies$ExpressionAntlrContext$concept)
	{
		static_assert
		(
			CmdCalculator::OperandAntlrContext
			<
				CmdCalculatorTestDoubles::StubOperandAntlrContext
			>
		);
	}

#pragma endregion
}