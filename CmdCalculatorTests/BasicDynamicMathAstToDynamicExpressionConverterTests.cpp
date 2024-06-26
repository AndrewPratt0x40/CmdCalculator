#include "pch.h"

#include <string>
#include <format>
#include <algorithm>
#include <memory>
#include <concepts>
#include <ranges>
#include <vector>
#include <functional>

#include "../CmdCalculatorTestUtils/common.h"
#include "../CmdCalculator/BasicDynamicMathAstToDynamicExpressionConverter.h"
#include "../CmdCalculator/MathAstToExpressionConverter.h"
#include "../CmdCalculator/DynamicExpressionBox.h"
#include "../CmdCalculator/std_polyfills.h"
#include "../CmdCalculatorTestDoubles/StubTrackingDynamicOperandToDynamicExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/StubTrackingRecursiveSplitResultToDynamicExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/FakeHalfwayDynamicExpressionPartRecursiveSplitter.h"
#include "../CmdCalculatorTestDoubles/StubTrackingDynamicExpression.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionNode.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionPartNode.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"


namespace CmdCalculatorTests
{
#pragma region Concept satisfaction
	
	TEST(BasicDynamicMathAstToDynamicExpressionConverterTests, BasicDynamicMathAstToDynamicExpressionConverter$satisfies$DynamicMathAstToDynamicExpressionConverter$concept)
	{
		static_assert
		(
			CmdCalculator::DynamicMathAstToDynamicExpressionConverter
			<
				CmdCalculator::BasicDynamicMathAstToDynamicExpressionConverter
				<
					CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartRecursiveSplitter
					<
						std::string
					>,
					CmdCalculatorTestDoubles::StubTrackingRecursiveSplitResultToDynamicExpressionConverter
					<
						CmdCalculator::SplitResultType
						<
							CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartRecursiveSplitter
							<
								std::string
							>
						>,
						CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber
					>
				>
			>
		);
	}

#pragma endregion


#pragma region getMathAstAsExpression

	struct BasicDynamicMathAstToDynamicExpressionConverter_getMathAstAsExpression_TestData
	{
		std::vector<std::string> sourceExpressionParts;
		double evaluation;
		// TODO: Consider using a more direct way of comparing results.
		std::string expectedResult;
		
		
		friend std::ostream& operator<<
		(
			std::ostream& ostream,
			const BasicDynamicMathAstToDynamicExpressionConverter_getMathAstAsExpression_TestData& testData
		)
		{
			ostream
				<< "FakeHalfwayDynamicExpressionPartRecursiveSplitter.getMathAstAsExpression("
				<< CmdCalculatorTestUtils::joinStrings(testData.sourceExpressionParts)
				<< ") = {evaluation = "
				<< testData.evaluation
				<< ", result = "
				<< testData.expectedResult
				<< "}"
			;

			return ostream;
		}
	};

	class BasicDynamicMathAstToDynamicExpressionConverter$getMathAstAsExpression$Tests :
		public testing::TestWithParam<BasicDynamicMathAstToDynamicExpressionConverter_getMathAstAsExpression_TestData>
	{};

	const BasicDynamicMathAstToDynamicExpressionConverter_getMathAstAsExpression_TestData
		BasicDynamicMathAstToDynamicExpressionConverter_getMathAstAsExpression_TestDataValues[]
	{
		{
			.sourceExpressionParts{ "Part1" },
			.evaluation{ 0.0 },
			.expectedResult{ "{[Part1]->null<Part1>null}" }
		},
		{
			.sourceExpressionParts{ "Part1" },
			.evaluation{ 1.0 },
			.expectedResult{ "{[Part1]->null<Part1>null}" }
		},
		{
			.sourceExpressionParts{ "Part1", "Part2", "Part3" },
			.evaluation{ 0.0 },
			.expectedResult{ "{[Part1,Part2,Part3]->{[Part1]->null<Part1>null}<Part2>{[Part3]->null<Part3>null}}" }
		},
		{
			.sourceExpressionParts{ "Part1", "Part2", "Part3", "Part4", "Part5" },
			.evaluation{ 0.0 },
			.expectedResult{ "{[Part1,Part2,Part3,Part4,Part5]->{[Part1]->null<Part1>null}<Part2>{[Part3,Part4,Part5]->{[Part3]->null<Part3>null}<Part4>{[Part5]->null<Part5>null}}}" }
		},
		{
			.sourceExpressionParts{ "Part1", "Part2", "Part3", "Part4", "Part5", "Part6", "Part7" },
			.evaluation{ 0.0 },
			.expectedResult{ "{[Part1,Part2,Part3,Part4,Part5,Part6,Part7]->{[Part1,Part2,Part3]->{[Part1]->null<Part1>null}<Part2>{[Part3]->null<Part3>null}}<Part4>{[Part5,Part6,Part7]->{[Part5]->null<Part5>null}<Part6>{[Part7]->null<Part7>null}}}" }
		},
		{
			.sourceExpressionParts{ "Part1", "Part2", "Part3", "Part4", "Part5", "Part6", "Part7", "Part8", "Part9" },
			.evaluation{ 0.0 },
			.expectedResult{ "{[Part1,Part2,Part3,Part4,Part5,Part6,Part7,Part8,Part9]->{[Part1,Part2,Part3]->{[Part1]->null<Part1>null}<Part2>{[Part3]->null<Part3>null}}<Part4>{[Part5,Part6,Part7,Part8,Part9]->{[Part5]->null<Part5>null}<Part6>{[Part7,Part8,Part9]->{[Part7]->null<Part7>null}<Part8>{[Part9]->null<Part9>null}}}}" }
		},
		{
			.sourceExpressionParts{ "Part1", "Part2", "Part3", "Part4", "Part5", "Part6", "Part7", "Part8", "Part9", "Part10", "Part11" },
			.evaluation{ 0.0 },
			.expectedResult{ "{[Part1,Part2,Part3,Part4,Part5,Part6,Part7,Part8,Part9,Part10,Part11]->{[Part1,Part2,Part3,Part4,Part5]->{[Part1]->null<Part1>null}<Part2>{[Part3,Part4,Part5]->{[Part3]->null<Part3>null}<Part4>{[Part5]->null<Part5>null}}}<Part6>{[Part7,Part8,Part9,Part10,Part11]->{[Part7]->null<Part7>null}<Part8>{[Part9,Part10,Part11]->{[Part9]->null<Part9>null}<Part10>{[Part11]->null<Part11>null}}}}" }
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		BasicDynamicMathAstToDynamicExpressionConverter$Tests,
		BasicDynamicMathAstToDynamicExpressionConverter$getMathAstAsExpression$Tests,
		testing::ValuesIn(BasicDynamicMathAstToDynamicExpressionConverter_getMathAstAsExpression_TestDataValues)
	);

	TEST_P(BasicDynamicMathAstToDynamicExpressionConverter$getMathAstAsExpression$Tests, getMathAstAsExpression$returns$the$result$of$splitting$and$converting$the$given$parts)
	{
		// Arrange
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using SplitterType = CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartRecursiveSplitter<std::string>;
		using SplitResultConverterType = CmdCalculatorTestDoubles::StubTrackingRecursiveSplitResultToDynamicExpressionConverter
		<
			CmdCalculator::SplitResultType<SplitterType>,
			NumberType
		>;

		const double expectedEvaluation{ GetParam().evaluation };
		const std::string expectedResult{ GetParam().expectedResult };

		const std::ranges::range auto expressionPartsRange
		{
			GetParam().sourceExpressionParts
			| std::views::transform
			(
				[](const std::string& part)
				{
					return std::move
					(
						std::make_unique<CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>>
						(
							false, "", "", part
						)
					);
				}
			)
		};
		const CmdCalculator::UniquePtr auto rootSourceNode
		{
			std::make_unique<CmdCalculator::MathAst::DynamicExpressionNode<std::string>>
			(
				"", "",
				std::move
				(
					std::ranges::owning_view<std::vector<std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>>>>
					{
						std::move
						(
							std::vector<std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>>>
							{
								std::ranges::begin(expressionPartsRange),
								std::ranges::end(expressionPartsRange)
							}
						)
					}
				)
			)
		};
		ASSERT_TRUE(rootSourceNode);

		SplitterType splitter{};
		SplitResultConverterType splitResultConverter
		{
			.sourceSplitResultStringFunc
			{
				[](const CmdCalculator::SplitResultType<SplitterType>& sourceSplitResult)
				{ return sourceSplitResult.STUB_getStringRepresentation(); }
			},
			.convertedSplitResultEvaluation{ GetParam().evaluation }
		};

		CmdCalculator::BasicDynamicMathAstToDynamicExpressionConverter<SplitterType, SplitResultConverterType> instance
		{
			std::move(splitter),
			std::move(splitResultConverter)
		};

		// Act
		const decltype(instance)::OutputExpressionType returnValue
		{
			instance.getMathAstAsExpression(*rootSourceNode)
		};

		// Assert
		static_assert
		(
			std::same_as
			<
				decltype(returnValue.getInnerValue()),
				const decltype(instance)::OutputExpressionInnerType&
			>
		);
		const typename decltype(instance)::OutputExpressionInnerType& returnedInnerExpression
		{
			returnValue.getInnerValue()
		};
		EXPECT_EQ(expectedEvaluation, returnedInnerExpression.getEvaluation().FAKE_getValue());
		EXPECT_EQ(expectedResult, returnedInnerExpression.source);
	}

#pragma endregion
}