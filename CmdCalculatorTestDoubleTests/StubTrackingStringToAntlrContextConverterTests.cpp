#include "pch.h"

#include <string>

#include "../CmdCalculatorTestDoubles/StubTrackingStringToAntlrContextConverter.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubTrackingStringToAntlrContextConverterTests, StubTrackingStringToAntlrContextConverter$satisfies$StringToAntlrContextConverter$concept)
	{
		static_assert
		(
			::CmdCalculator::StringToAntlrContextConverter<CmdCalculatorTestDoubles::StubTrackingStringToAntlrContextConverter<std::string_view>>
		);
	}

#pragma endregion
}