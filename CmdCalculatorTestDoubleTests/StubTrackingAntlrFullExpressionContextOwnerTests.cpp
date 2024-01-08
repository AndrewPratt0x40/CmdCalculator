#include "pch.h"

#include <string>

#include "../CmdCalculatorTestDoubles/StubTrackingAntlrFullExpressionContextOwner.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubTrackingAntlrFullExpressionContextOwnerTests, StubTrackingAntlrFullExpressionContextOwner$satisfies$AntlrFullExpressionContextOwner$concept)
	{
		static_assert
		(
			CmdCalculator::AntlrFullExpressionContextOwner<CmdCalculatorTestDoubles::StubTrackingAntlrFullExpressionContextOwner<std::string_view>>
		);
	}

#pragma endregion
}