#include "pch.h"

#include "../CmdCalculator/AntlrInvokingStringToAntlrContextConverter.h"
#include "../CmdCalculator/StringToAntlrContextConverter.h"

#include <string_view>


namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(AntlrInvokingStringToAntlrContextConverterTests, AntlrInvokingStringToAntlrContextConverter$satisfies$StringToAntlrContextConverter$concept)
	{
		static_assert
		(
			CmdCalculator::StringToAntlrContextConverter<CmdCalculator::AntlrInvokingStringToAntlrContextConverter<std::string_view>>
		);
	}

#pragma endregion
}