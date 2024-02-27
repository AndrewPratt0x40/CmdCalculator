#include "pch.h"

#include <string_view>

#include "../CmdCalculatorTestDoubles/StubWholefulNumberLiteralAntlrContext.h"
#include "../CmdCalculator/WholefulNumberLiteralAntlrContext.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubWholefulNumberLiteralAntlrContextTests, StubWholefulNumberLiteralAntlrContext$satisfies$WholefulNumberLiteralAntlrContext$concept)
	{
		static_assert
		(
			CmdCalculator::WholefulNumberLiteralAntlrContext
			<
				CmdCalculatorTestDoubles::StubWholefulNumberLiteralAntlrContext
			>
		);
	}

#pragma endregion
}