#include "pch.h"

#include <string>
#include <memory>
#include <span>

#include "../CmdCalculator/DynamicSignOperationNode.h"
#include "../CmdCalculatorTestDoubles/StubDynamicOperandNode.h"

namespace CmdCalculatorTestDoubleTests
{
	struct DynamicSignOperationNode_TestParams
	{
		CmdCalculatorTestDoubles::MathAst::StubDynamicOperandNode<std::string> operand;
		bool isPositive;
		std::string innerTrivia;
		std::string leadingTrivia;
		std::string trailingTrivia;
		std::string stringRepresentation;
	};

	class DynamicSignOperationNodeWithCtorParamsTests :
		public testing::TestWithParam<DynamicSignOperationNode_TestParams>
	{};

#pragma region Instantiate DynamicSignOperationNodeWithCtorParamsTests
	INSTANTIATE_TEST_CASE_P
	(
		DynamicSignOperationNodeTests,
		DynamicSignOperationNodeWithCtorParamsTests,
		testing::Values
		(
			DynamicSignOperationNode_TestParams
			{
				.operand{ "", "", "Operand" },
				.isPositive{ false },
				.innerTrivia{ "" },
				.leadingTrivia{ "" },
				.trailingTrivia{ "" },
				.stringRepresentation{ "-Operand" }
			},
			DynamicSignOperationNode_TestParams
			{
				.operand{ "", "", "Operand" },
				.isPositive{ true },
				.innerTrivia{ "" },
				.leadingTrivia{ "" },
				.trailingTrivia{ "" },
				.stringRepresentation{ "+Operand" }
			},
			DynamicSignOperationNode_TestParams
			{
				.operand{ "", "", "Operand" },
				.isPositive{ true },
				.innerTrivia{ "  " },
				.leadingTrivia{ "   " },
				.trailingTrivia{ "    " },
				.stringRepresentation{ "   +  Operand    " }
			}
		)
	);
#pragma endregion


	TEST_P(DynamicSignOperationNodeWithCtorParamsTests, DISABLED_DynamicSignOperationNode$has$expected$state)
	{
		// Arrange
		auto operandToPass
		{
			std::make_unique<CmdCalculatorTestDoubles::MathAst::StubDynamicOperandNode<std::string>>
				(GetParam().operand)
		};
		const bool isPositiveToPass{ GetParam().isPositive };
		const std::string innerTriviaToPass{ GetParam().innerTrivia };
		const std::string leadingTriviaToPass{ GetParam().leadingTrivia };
		const std::string trailingTriviaToPass{ GetParam().trailingTrivia };

		const std::string expectedOperandStringRepresentation{ GetParam().operand.getStringRepresentation() };
		const bool expectedIsPositive{ GetParam().isPositive };
		const std::string expectedInnerTrivia{ GetParam().innerTrivia };
		const std::string expectedLeadingTrivia{ GetParam().leadingTrivia };
		const std::string expectedTrailingTrivia{ GetParam().trailingTrivia };
		const std::string expectedStringRepresentation{ GetParam().stringRepresentation };
		
		// Act
		CmdCalculator::MathAst::DynamicSignOperationNode<std::string> instance
		{
			std::move(operandToPass),
			isPositiveToPass,
			innerTriviaToPass,
			leadingTriviaToPass,
			trailingTriviaToPass
		};

		// Assert
		EXPECT_EQ(expectedOperandStringRepresentation, instance.getOperand()->getStringRepresentation());
		EXPECT_EQ(expectedIsPositive, instance.isPositive());
		EXPECT_EQ(expectedInnerTrivia, instance.getInnerTrivia());
		EXPECT_EQ(expectedLeadingTrivia, instance.getLeadingTrivia());
		EXPECT_EQ(expectedTrailingTrivia, instance.getTrailingTrivia());
		EXPECT_EQ(expectedStringRepresentation, instance.getStringRepresentation());
	}
}