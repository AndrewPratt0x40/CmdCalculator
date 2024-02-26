#include "pch.h"

#include <string_view>

#include "../CmdCalculatorTestDoubles/StubWholelessNumberLiteralAntlrContext.h"
#include "../CmdCalculator/WholelessNumberLiteralAntlrContext.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubWholelessNumberLiteralAntlrContextTests, StubWholelessNumberLiteralAntlrContext$satisfies$WholelessNumberLiteralAntlrContext$concept)
	{
		static_assert
		(
			::CmdCalculator::WholelessNumberLiteralAntlrContext
			<
				CmdCalculatorTestDoubles::StubWholelessNumberLiteralAntlrContext
			>
		);
	}

#pragma endregion
}