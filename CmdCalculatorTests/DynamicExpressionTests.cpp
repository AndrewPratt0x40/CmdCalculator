#include "pch.h"

#include <string>

#include "../CmdCalculator/DynamicExpression.h"
#include "../CmdCalculator/Expression.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(DynamicExpressionTests, DynamicExpression$satisfies$Expression$concept)
	{
		static_assert
		(
			CmdCalculator::Expressions::Expression<CmdCalculator::Expressions::DynamicExpression<std::string>>
		);
	}

#pragma endregion
}