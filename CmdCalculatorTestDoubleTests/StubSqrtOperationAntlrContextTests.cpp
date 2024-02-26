#include "pch.h"

#include <string_view>

#include "../CmdCalculatorTestDoubles/StubSqrtOperationAntlrContext.h"
#include "../CmdCalculator/SqrtOperationAntlrContext.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubSqrtOperationAntlrContextTests, StubSqrtOperationAntlrContext$satisfies$SqrtOperationAntlrContext$concept)
	{
		static_assert
		(
			::CmdCalculator::SqrtOperationAntlrContext
			<
				CmdCalculatorTestDoubles::StubSqrtOperationAntlrContext
			>
		);
	}

#pragma endregion
}