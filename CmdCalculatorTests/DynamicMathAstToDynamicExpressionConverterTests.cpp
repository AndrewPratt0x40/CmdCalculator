#include "pch.h"

#include "../CmdCalculator/DynamicMathAstToDynamicExpressionConverter.h"
#include "../CmdCalculator/MathAstToExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/StubDynamicOperandToDynamicExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpression.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"

#include <string>


namespace CmdCalculatorTests
{
#pragma region Concept satisfaction
	
	TEST(DynamicMathAstToDynamicExpressionConverterTests, DynamicMathAstToDynamicExpressionConverter$satisfies$MathAstToExpressionConverter$concept)
	{
		static_assert
		(
			CmdCalculator::MathAstToExpressionConverter
			<
				CmdCalculator::DynamicMathAstToDynamicExpressionConverter
				<
					CmdCalculatorTestDoubles::StubDynamicOperandToDynamicExpressionConverter
					<
						std::string,
						CmdCalculatorTestDoubles::Expressions::StubDynamicExpression
						<
							CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber
						>
					>
				>
			>
		);
	}

#pragma endregion


#pragma region getMathAstAsExpression

	

#pragma endregion
}