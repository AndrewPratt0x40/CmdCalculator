#include "pch.h"

#include <string>
#include <format>
#include <algorithm>
#include <concepts>
#include <ranges>
#include <vector>

#include "../CmdCalculator/DynamicMathAstToDynamicExpressionConverter.h"
#include "../CmdCalculator/MathAstToExpressionConverter.h"
#include "../CmdCalculator/std_polyfills.h"
#include "../CmdCalculatorTestDoubles/StubTrackingDynamicOperandToDynamicExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/StubTrackingRecursiveSplitResultToDynamicExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/FakeHalfwayDynamicExpressionPartRecursiveSplitter.h"
#include "../CmdCalculatorTestDoubles/StubTrackingDynamicExpression.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionPartNode.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"


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

	struct DynamicMathAstToDynamicExpressionConverter_getMathAstAsExpression_TestData
	{
		std::vector<std::string> parts;


		std::string stringifyParts() const
		{
			if (parts.empty())
				return "";

			return
				CmdCalculator::Polyfills::ranges::fold_left
				(
					parts
						|std::views::take(parts.size() - 1)
						|std::views::drop(1)
						| std::views::transform
						(
							[](const std::string& part)
							{ return std::format("\"{}\", ", part); }
						)
					,
					std::format("\"{}\", ", parts.front()),
					std::plus<std::string>()
				)
				+ std::format("\"{}\"", parts.back())
			;
		}
		
		
		friend std::ostream& operator<<
		(
			std::ostream& ostream,
			const DynamicMathAstToDynamicExpressionConverter_getMathAstAsExpression_TestData& testData
		)
		{
			ostream
				<< "FakeHalfwayDynamicExpressionPartRecursiveSplitter.getMathAstAsExpression({"
				<< testData.stringifyParts()
				<< "}) = "
				// TODO: << testData.expectedResult.value_or("{}")
			;

			return ostream;
		}
	};

	class DynamicMathAstToDynamicExpressionConverter$getMathAstAsExpression$Tests :
		public testing::TestWithParam<DynamicMathAstToDynamicExpressionConverter_getMathAstAsExpression_TestData>
	{};

	const DynamicMathAstToDynamicExpressionConverter_getMathAstAsExpression_TestData
		DynamicMathAstToDynamicExpressionConverter_getMathAstAsExpression_TestDataValues[]
	{
		{
			// TODO
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		DynamicMathAstToDynamicExpressionConverter$Tests,
		DynamicMathAstToDynamicExpressionConverter$getMathAstAsExpression$Tests,
		testing::ValuesIn(DynamicMathAstToDynamicExpressionConverter_getMathAstAsExpression_TestDataValues)
	);

	TEST_P(DynamicMathAstToDynamicExpressionConverter$getMathAstAsExpression$Tests, getMathAstAsExpression$returns$the$result$of$splitting$and$converting$the$given$parts)
	{
		// Arrange
		using ExpressionNodePartType = CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>;
		using SplitterType = CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartRecursiveSplitter<std::string>;
		using SplitResultConverterType = CmdCalculatorTestDoubles::StubTrackingRecursiveSplitResultToDynamicExpressionConverter
		<
			CmdCalculator::SplitResultType<SplitterType>,
			CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber
		>;

		SplitterType splitter{};
		SplitResultConverterType splitResultConverter{};

		const std::ranges::common_range auto partsCreationRange
		{
			GetParam().parts
			| std::views::transform
			(
				[](const std::string& part)
				{
					return ExpressionNodePartType{false, "", "", part};
				}
			)
		};
		const std::vector<ExpressionNodePartType> parts
		{
			std::ranges::begin(partsCreationRange),
			std::ranges::end(partsCreationRange)
		};
		const CmdCalculator::MathAst::DynamicExpressionPartNodeRange<std::string> auto partRefsView
		{
			parts
			| std::views::transform
			(
				[](const auto& part)
				{ return std::ref(part); }
			)
		};

		CmdCalculator::DynamicMathAstToDynamicExpressionConverter<SplitterType, SplitResultConverterType> instance
		{
			std::move(splitter),
			std::move(splitResultConverter)
		};

		// Arrange
		instance.getMathAstAsExpression()
	}

#pragma endregion
}