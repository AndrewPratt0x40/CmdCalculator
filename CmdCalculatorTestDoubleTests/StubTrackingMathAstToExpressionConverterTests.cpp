#include "pch.h"

#include <string>

#include "../CmdCalculatorTestDoubles/StubTrackingMathAstToExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/StubMathAstNode.h"
#include "../CmdCalculatorTestDoubles/StubExpression.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubTrackingMathAstToExpressionConverterTests, StubTrackingMathAstToExpressionConverter$satisfies$MathAstToExpressionConverter$concept)
	{
		static_assert
		(
			CmdCalculator::MathAstToExpressionConverter
			<
				CmdCalculatorTestDoubles::StubTrackingMathAstToExpressionConverter
				<
					CmdCalculatorTestDoubles::MathAst::StubMathAstNode<std::string>
				>
			>
		);
	}

#pragma endregion
}