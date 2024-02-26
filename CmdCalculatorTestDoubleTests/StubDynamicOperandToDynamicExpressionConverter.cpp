#include "pch.h"

#include "../CmdCalculator/DynamicOperandToDynamicExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/StubDynamicOperandToDynamicExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpression.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubDynamicOperandToDynamicExpressionConverterTests, StubDynamicOperandToDynamicExpressionConverter$satisfies$DynamicOperandToDynamicExpressionConverter$concept)
	{
		static_assert
		(
			::CmdCalculator::DynamicOperandToDynamicExpressionConverter
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
		);
	}

#pragma endregion
}