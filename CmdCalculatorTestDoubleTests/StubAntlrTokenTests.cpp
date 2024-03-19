#include "pch.h"

#include <string>

#include "../CmdCalculatorTestDoubles/StubAntlrToken.h"
#include "../CmdCalculator/AntlrToken.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubAntlrTokenTests, StubAntlrToken$satisfies$AntlrToken$concept)
	{
		static_assert
		(
			CmdCalculator::AntlrToken
			<
				CmdCalculatorTestDoubles::StubAntlrToken<std::string>
			>
		);
	}

#pragma endregion
}