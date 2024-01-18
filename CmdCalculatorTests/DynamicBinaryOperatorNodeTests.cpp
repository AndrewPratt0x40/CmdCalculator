#include "pch.h"

#include <string>

#include "../CmdCalculator/DynamicBinaryOperatorNode.h"

namespace CmdCalculatorTestDoubleTests
{
	struct DynamicBinaryOperatorNode_TestParams
	{
		CmdCalculator::MathAst::EBinaryOperator operatorKind;
		std::string leadingTrivia;
		std::string trailingTrivia;
		std::string stringRepresentation;
	};

	class DynamicBinaryOperatorNodeWithCtorParamsTests :
		public testing::TestWithParam<DynamicBinaryOperatorNode_TestParams>
	{};

#pragma region Instantiate DynamicBinaryOperatorNodeWithCtorParamsTests
	INSTANTIATE_TEST_CASE_P
	(
		DynamicBinaryOperatorNodeTests,
		DynamicBinaryOperatorNodeWithCtorParamsTests,
		testing::Values
		(
			DynamicBinaryOperatorNode_TestParams
			{
				.operatorKind{ CmdCalculator::MathAst::EBinaryOperator::Addition },
				.leadingTrivia{},
				.trailingTrivia{},
				.stringRepresentation{ "+" }
			},
			DynamicBinaryOperatorNode_TestParams
			{
				.operatorKind{ CmdCalculator::MathAst::EBinaryOperator::Subtraction },
				.leadingTrivia{},
				.trailingTrivia{},
				.stringRepresentation{ "-" }
			},
			DynamicBinaryOperatorNode_TestParams
			{
				.operatorKind{ CmdCalculator::MathAst::EBinaryOperator::Multiplication },
				.leadingTrivia{},
				.trailingTrivia{},
				.stringRepresentation{ "*" }
			},
			DynamicBinaryOperatorNode_TestParams
			{
				.operatorKind{ CmdCalculator::MathAst::EBinaryOperator::Division },
				.leadingTrivia{},
				.trailingTrivia{},
				.stringRepresentation{ "/" }
			},
			DynamicBinaryOperatorNode_TestParams
			{
				.operatorKind{ CmdCalculator::MathAst::EBinaryOperator::Exponentiation },
				.leadingTrivia{},
				.trailingTrivia{},
				.stringRepresentation{ "^" }
			},
			DynamicBinaryOperatorNode_TestParams
			{
				.operatorKind{ CmdCalculator::MathAst::EBinaryOperator::NthRoot },
				.leadingTrivia{},
				.trailingTrivia{},
				.stringRepresentation{ "_" }
			},
			DynamicBinaryOperatorNode_TestParams
			{
				.operatorKind{ CmdCalculator::MathAst::EBinaryOperator::Modulo },
				.leadingTrivia{},
				.trailingTrivia{},
				.stringRepresentation{ "%" }
			},
			DynamicBinaryOperatorNode_TestParams
			{
				.operatorKind{ CmdCalculator::MathAst::EBinaryOperator::Multiplication },
				.leadingTrivia{ " " },
				.trailingTrivia{ "  " },
				.stringRepresentation{ " *  " }
			}
		)
	);
#pragma endregion


	TEST_P(DynamicBinaryOperatorNodeWithCtorParamsTests, DISABLED_DynamicBinaryOperatorNode$has$expected$state)
	{
		// Arrange
		CmdCalculator::MathAst::DynamicBinaryOperatorNode<std::string> instance
		{
			GetParam().operatorKind,
			GetParam().leadingTrivia,
			GetParam().trailingTrivia
		};

		// Assert
		EXPECT_EQ(instance.getOperatorKind(), GetParam().operatorKind);
		EXPECT_EQ(instance.getLeadingTrivia(), GetParam().leadingTrivia);
		EXPECT_EQ(instance.getTrailingTrivia(), GetParam().trailingTrivia);
		EXPECT_EQ(instance.getStringRepresentation(), GetParam().stringRepresentation);
	}
}