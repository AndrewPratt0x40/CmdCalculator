#include "pch.h"

#include <string_view>

#include "../CmdCalculatorTestDoubles/StubNumberLiteralAntlrContext.h"
#include "../CmdCalculator/NumberLiteralAntlrContext.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubNumberLiteralAntlrContextTests, StubNumberLiteralAntlrContext$satisfies$NumberLiteralAntlrContext$concept)
	{
		static_assert
		(
			CmdCalculator::NumberLiteralAntlrContext
			<
				CmdCalculatorTestDoubles::StubNumberLiteralAntlrContext
			>
		);
	}

#pragma endregion
}