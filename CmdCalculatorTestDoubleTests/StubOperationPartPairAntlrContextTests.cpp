#include "pch.h"

#include <string_view>

#include "../CmdCalculatorTestDoubles/StubOperationPartPairAntlrContext.h"
#include "../CmdCalculator/OperationPartPairAntlrContext.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubOperationPartPairAntlrContextTests, StubOperationPartPairAntlrContext$satisfies$OperationPartPairAntlrContext$concept)
	{
		static_assert
		(
			CmdCalculator::OperationPartPairAntlrContext
			<
				CmdCalculatorTestDoubles::StubOperationPartPairAntlrContext
			>
		);
	}

#pragma endregion
}