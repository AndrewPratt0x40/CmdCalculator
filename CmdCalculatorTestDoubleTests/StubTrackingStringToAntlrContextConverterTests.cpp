#include "pch.h"

#include <string>

#include "../CmdCalculatorTestDoubles/StubTrackingStringToAntlrContextConverter.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubTrackingStringToAntlrContextConverterTests, StubTrackingStringToAntlrContextConverter$satisfies$StringToAntlrContextConverter$concept)
	{
		EXPECT_TRUE(false); // TODO
		static_assert
		(
			true//CmdCalculator::StringToAntlrContextConverter<CmdCalculatorTestDoubles::StubTrackingStringToAntlrContextConverter<std::string_view>>
		);
	}

#pragma endregion
}