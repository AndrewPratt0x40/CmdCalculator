#include "pch.h"

#include <string>

#include "../CmdCalculatorTestDoubles/StubTrackingExpressionToStringConverter.h"
#include "../CmdCalculatorTestDoubles/StubExpression.h"
#include "../CmdCalculatorTestDoubles/StubMathAstNode.h"
#include "../CmdCalculator/ExpressionToStringConverter.h"
#include "../CmdCalculator/Expression.h"
#include "../CmdCalculator/MathAstNode.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubTrackingExpressionToStringConverterTests, StubTrackingExpressionToStringConverter$satisfies$ExpressionToStringConverter$concept)
	{
		static_assert
		(
			CmdCalculator::ExpressionToStringConverter
			<
				CmdCalculatorTestDoubles::StubTrackingExpressionToStringConverter
				<
					CmdCalculatorTestDoubles::Expressions::StubExpression,
					std::string
				>
			>
		);
	}

#pragma endregion
}