#include "pch.h"

#include <string_view>

#include "../CmdCalculatorTestDoubles/StubBinaryOperatorAntlrContext.h"
#include "../CmdCalculator/BinaryOperatorAntlrContext.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubBinaryOperatorAntlrContextTests, StubBinaryOperatorAntlrContext$satisfies$BinaryOperatorAntlrContext$concept)
	{
		static_assert
		(
			::CmdCalculator::BinaryOperatorAntlrContext
			<
				CmdCalculatorTestDoubles::StubBinaryOperatorAntlrContext
			>
		);
	}

#pragma endregion
}