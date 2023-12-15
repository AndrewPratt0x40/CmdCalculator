#include "pch.h"

#include <string>
#include <initializer_list>
#include <ranges>
#include <algorithm>

#include "../CmdCalculatorTestDoubles/StubExpression.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubExpressionTests, StubExpression$satisfies$Expression$concept)
	{
		static_assert
		(
			CmdCalculator::Expressions::Expression<CmdCalculatorTestDoubles::Expressions::StubExpression>
		);
	}

#pragma endregion
}