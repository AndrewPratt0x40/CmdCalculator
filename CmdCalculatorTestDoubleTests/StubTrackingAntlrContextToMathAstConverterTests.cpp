#include "pch.h"

#include <string>

#include "../CmdCalculatorTestDoubles/StubTrackingAntlrContextToMathAstConverter.h"
#include "../CmdCalculator/AntlrContextToMathAstConverter.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubTrackingAntlrContextToMathAstConverterTests, StubAntlrContextToMathAstConverter$satisfies$ContextToMathAstConverter$concept)
	{
		EXPECT_TRUE(false); // TODO
		static_assert
		(
			true//CmdCalculator::AntlrContextToMathAstConverter<CmdCalculatorTestDoubles::StubTrackingAntlrContextToMathAstConverter<std::string, int>>
		);
	}

#pragma endregion
}