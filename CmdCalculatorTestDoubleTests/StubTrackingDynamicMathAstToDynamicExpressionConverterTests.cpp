#include "pch.h"

#include <string>

#include "../CmdCalculatorTestDoubles/StubTrackingDynamicMathAstToDynamicExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/StubMathAstNode.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubTrackingDynamicMathAstToDynamicExpressionConverterTests, StubTrackingDynamicMathAstToDynamicExpressionConverter$satisfies$DynamicMathAstToDynamicExpressionConverter$concept)
	{
		static_assert
		(
			CmdCalculator::DynamicMathAstToDynamicExpressionConverter
			<
				CmdCalculatorTestDoubles::StubTrackingDynamicMathAstToDynamicExpressionConverter
				<
					CmdCalculatorTestDoubles::MathAst::StubMathAstNode<std::string>,
					CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber
				>
			>
		);
	}

#pragma endregion
}