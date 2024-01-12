#include "pch.h"

#include <string>

#include "../CmdCalculatorTestDoubles/StubTrackingAntlrContextToMathAstConverter.h"
#include "../CmdCalculator/AntlrContextToMathAstConverter.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubTrackingAntlrContextToMathAstConverterTests, StubAntlrContextToMathAstConverter$satisfies$ContextToMathAstConverter$concept)
	{
		static_assert
		(
			CmdCalculator::AntlrContextToMathAstConverter
			<
				CmdCalculatorTestDoubles::StubTrackingAntlrContextToMathAstConverter<std::string, int, std::string_view>
			>
		);
	}

#pragma endregion
}