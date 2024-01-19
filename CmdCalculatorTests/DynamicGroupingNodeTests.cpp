#include "pch.h"

#include <string>
#include <memory>
#include <span>

#include "../CmdCalculator/DynamicGroupingNode.h"
#include "../CmdCalculator/DynamicExpressionNode.h"
#include "../CmdCalculator/DynamicExpressionPartNode.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionNode.h"

namespace CmdCalculatorTestDoubleTests
{
	struct DynamicGroupingNode_TestParams
	{
		std::string containedExpressionStringRepresentation;
		std::string leadingTrivia;
		std::string trailingTrivia;
		std::string stringRepresentation;
	};

	class DynamicGroupingNodeWithCtorParamsTests :
		public testing::TestWithParam<DynamicGroupingNode_TestParams>
	{};

	const DynamicGroupingNode_TestParams DynamicGroupingNode_TestParamsValues[]
	{
		DynamicGroupingNode_TestParams
		{
			.containedExpressionStringRepresentation{ "ContainedExpression" },
			.leadingTrivia{ "" },
			.trailingTrivia{ "" },
			.stringRepresentation{ "(ContainedExpression)" }
		},
		DynamicGroupingNode_TestParams
		{
			.containedExpressionStringRepresentation{ "ContainedExpression" },
			.leadingTrivia{ " " },
			.trailingTrivia{ "  " },
			.stringRepresentation{ " (ContainedExpression)  " }
		}
	};

#pragma region Instantiate DynamicGroupingNodeWithCtorParamsTests
	INSTANTIATE_TEST_CASE_P
	(
		DynamicGroupingNodeTests,
		DynamicGroupingNodeWithCtorParamsTests,
		testing::ValuesIn(DynamicGroupingNode_TestParamsValues)
	);
#pragma endregion


	TEST_P(DynamicGroupingNodeWithCtorParamsTests, DynamicGroupingNode$has$expected$state)
	{
		// Arrange
		auto containedExpressionToPass
		{
			std::make_unique<CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionNode<std::string>>
				(GetParam().containedExpressionStringRepresentation, "", "")
		};
		const std::string leadingTriviaToPass{ GetParam().leadingTrivia };
		const std::string trailingTriviaToPass{ GetParam().trailingTrivia };

		const std::string expectedContainedExpressionStringRepresentation{ GetParam().containedExpressionStringRepresentation };
		const std::string expectedLeadingTrivia{ GetParam().leadingTrivia };
		const std::string expectedTrailingTrivia{ GetParam().trailingTrivia };
		const std::string expectedStringRepresentation{ GetParam().stringRepresentation };
		
		// Act
		CmdCalculator::MathAst::DynamicGroupingNode<std::string> instance
		{
			std::move(containedExpressionToPass),
			leadingTriviaToPass,
			trailingTriviaToPass
		};

		// Assert
		EXPECT_EQ(expectedContainedExpressionStringRepresentation, instance.getContainedExpression()->getStringRepresentation());
		EXPECT_EQ(expectedLeadingTrivia, instance.getLeadingTrivia());
		EXPECT_EQ(expectedTrailingTrivia, instance.getTrailingTrivia());
		EXPECT_EQ(expectedStringRepresentation, instance.getStringRepresentation());
	}
}