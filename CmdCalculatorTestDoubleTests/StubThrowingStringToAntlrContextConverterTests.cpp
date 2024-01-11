#include "pch.h"

#include <string>
#include <exception>

#include "../CmdCalculator/StringToAntlrContextConverter.h"
#include "../CmdCalculatorTestDoubles/StubThrowingStringToAntlrContextConverter.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubThrowingStringToAntlrContextConverterTests, StubThrowingStringToAntlrContextConverter$satisfies$StringToAntlrContextConverter$concept)
	{
		EXPECT_TRUE(false); // TODO
		static_assert
		(
			true//CmdCalculator::StringToAntlrContextConverter<CmdCalculatorTestDoubles::StubThrowingStringToAntlrContextConverter<std::string_view, std::exception>>
		);
	}

#pragma endregion
}