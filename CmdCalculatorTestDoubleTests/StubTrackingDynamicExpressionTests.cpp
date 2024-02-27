#include "pch.h"

#include "../CmdCalculator/Expression.h"
#include "../CmdCalculatorTestDoubles/StubTrackingDynamicExpression.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubTrackingDynamicExpressionTests, StubTrackingDynamicExpression$satisfies$Expression$concept)
	{
		static_assert
		(
			CmdCalculator::Expressions::Expression
			<
				CmdCalculatorTestDoubles::Expressions::StubTrackingDynamicExpression
				<
					CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber,
					int
				>
			>
		);
	}

#pragma endregion
}