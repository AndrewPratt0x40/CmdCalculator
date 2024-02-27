#include "pch.h"

#include "../CmdCalculator/DynamicOperandToDynamicExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/StubTrackingDynamicOperandToDynamicExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpression.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubTrackingDynamicOperandToDynamicExpressionConverterTests, StubTrackingDynamicOperandToDynamicExpressionConverter$satisfies$DynamicOperandToDynamicExpressionConverter$concept)
	{
		static_assert
		(
			CmdCalculator::DynamicOperandToDynamicExpressionConverter
			<
				CmdCalculatorTestDoubles::StubTrackingDynamicOperandToDynamicExpressionConverter
				<
					std::string,
					CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber
				>
			>
		);
	}

#pragma endregion
}