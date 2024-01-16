#include "pch.h"

#include <string>
#include <memory>
#include <span>

#include "../CmdCalculator/DynamicSqrtOperationNode.h"
#include "../CmdCalculatorTestDoubles/StubDynamicOperandNode.h"

namespace CmdCalculatorTestDoubleTests
{
	struct DynamicSqrtOperationNode_TestParams
	{
		CmdCalculatorTestDoubles::MathAst::StubDynamicOperandNode<std::string> operand;
		std::string innerTrivia;
		std::string leadingTrivia;
		std::string trailingTrivia;
		std::string stringRepresentation;
	};

	class DynamicSqrtOperationNodeWithCtorParamsTests :
		public testing::TestWithParam<DynamicSqrtOperationNode_TestParams>
	{};

#pragma region Instantiate DynamicSqrtOperationNodeWithCtorParamsTests
	INSTANTIATE_TEST_CASE_P
	(
		DynamicSqrtOperationNodeTests,
		DynamicSqrtOperationNodeWithCtorParamsTests,
		testing::Values
		(
			DynamicSqrtOperationNode_TestParams
			{
				.operand{ "", "", "Operand" },
				.innerTrivia{ "" },
				.leadingTrivia{ "" },
				.trailingTrivia{ "" },
				.stringRepresentation{ "sqrtOperand" }
			},
			DynamicSqrtOperationNode_TestParams
			{
				.operand{ "", "", "Operand" },
				.isPositive{ true },
				.innerTrivia{ "  " },
				.leadingTrivia{ "   " },
				.trailingTrivia{ "    " },
				.stringRepresentation{ "   sqrt  Operand    " }
			}
		)
	);
#pragma endregion


	TEST_P(DynamicSqrtOperationNodeWithCtorParamsTests, DynamicSqrtOperationNode$has$expected$state)
	{
		// Arrange
		auto operandToPass
		{
			std::make_unique<CmdCalculatorTestDoubles::MathAst::StubDynamicOperandNode<std::string>>
				(GetParam().operand)
		};
		const std::string innerTriviaToPass{ GetParam().innerTrivia };
		const std::string leadingTriviaToPass{ GetParam().leadingTrivia };
		const std::string trailingTriviaToPass{ GetParam().trailingTrivia };

		const std::string expectedOperandStringRepresentation{ GetParam().operand.getStringRepresentation() };
		const std::string expectedInnerTrivia{ GetParam().innerTrivia };
		const std::string expectedLeadingTrivia{ GetParam().leadingTrivia };
		const std::string expectedTrailingTrivia{ GetParam().trailingTrivia };
		const std::string expectedStringRepresentation{ GetParam().stringRepresentation };
		
		// Act
		CmdCalculator::MathAst::DynamicSqrtOperationNode<std::string> instance
		{
			std::move(operandToPass),
			innerTriviaToPass,
			leadingTriviaToPass,
			trailingTriviaToPass
		};

		// Assert
		EXPECT_EQ(expectedOperandStringRepresentation, instance.getOperand()->getStringRepresentation());
		EXPECT_EQ(expectedInnerTrivia, instance.getInnerTrivia());
		EXPECT_EQ(expectedLeadingTrivia, instance.getLeadingTrivia());
		EXPECT_EQ(expectedTrailingTrivia, instance.getTrailingTrivia());
		EXPECT_EQ(expectedStringRepresentation, instance.getStringRepresentation());
	}
}