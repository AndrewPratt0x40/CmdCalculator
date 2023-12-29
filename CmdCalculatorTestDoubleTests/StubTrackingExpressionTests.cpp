#include "pch.h"

#include <string>

#include "../CmdCalculatorTestDoubles/StubTrackingExpression.h"
#include "../CmdCalculatorTestDoubles/StubMathAstNode.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubTrackingExpressionTests, StubTrackingExpression$satisfies$Expression$concept)
	{
		static_assert
		(
			CmdCalculator::Expressions::Expression
			<
				CmdCalculatorTestDoubles::Expressions::StubTrackingExpression
				<
					CmdCalculatorTestDoubles::MathAst::StubMathAstNode<std::string>
				>
			>
		);
	}

#pragma endregion
}