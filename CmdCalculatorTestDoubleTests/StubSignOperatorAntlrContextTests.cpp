#include "pch.h"

#include <string_view>

#include "../CmdCalculatorTestDoubles/StubSignOperatorAntlrContext.h"
#include "../CmdCalculator/SignOperatorAntlrContext.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubSignOperatorAntlrContextTests, StubSignOperatorAntlrContext$satisfies$SignOperatorAntlrContext$concept)
	{
		static_assert
		(
			::CmdCalculator::SignOperatorAntlrContext
			<
				CmdCalculatorTestDoubles::StubSignOperatorAntlrContext
			>
		);
	}

#pragma endregion
}