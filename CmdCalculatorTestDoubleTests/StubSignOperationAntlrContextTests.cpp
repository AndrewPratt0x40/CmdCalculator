#include "pch.h"

#include <string_view>

#include "../CmdCalculatorTestDoubles/StubSignOperationAntlrContext.h"
#include "../CmdCalculator/SignOperationAntlrContext.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubSignOperationAntlrContextTests, StubSignOperationAntlrContext$satisfies$SignOperationAntlrContext$concept)
	{
		static_assert
		(
			::CmdCalculator::SignOperationAntlrContext
			<
				CmdCalculatorTestDoubles::StubSignOperationAntlrContext
			>
		);
	}

#pragma endregion
}