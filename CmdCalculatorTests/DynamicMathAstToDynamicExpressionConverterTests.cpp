#include "pch.h"

#include <string>
#include <format>
#include <algorithm>
#include <memory>
#include <concepts>
#include <ranges>
#include <vector>
#include <functional>

#include "../CmdCalculator/DynamicMathAstToDynamicExpressionConverter.h"
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
		std::string desc;
		std::function<std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionNode<std::string>>()> sourceExpression;
		
		
		friend std::ostream& operator<<
		(
			std::ostream& ostream,
			const DynamicMathAstToDynamicExpressionConverter_getMathAstAsExpression_TestData& testData
		)
		{
			ostream
				<< "FakeHalfwayDynamicExpressionPartRecursiveSplitter.getMathAstAsExpression("
				<< testData.desc
				<< ") = "
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
			.sourceExpression{}
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
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using SplitterType = CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartRecursiveSplitter<std::string>;
		using SplitResultConverterType = CmdCalculatorTestDoubles::StubTrackingRecursiveSplitResultToDynamicExpressionConverter
		<
			CmdCalculator::SplitResultType<SplitterType>,
			NumberType
		>;

		std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionNode<std::string>> rootSourceNode
		{
			GetParam().sourceExpression()
		};
		SplitterType splitter{};
		SplitResultConverterType splitResultConverter{};

		CmdCalculator::DynamicMathAstToDynamicExpressionConverter<SplitterType, SplitResultConverterType> instance
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
		/*static_assert
		(
			std::same_as
			<
				decltype(returnValue.getInnerValue()),
				const decltype(instance)::OutputExpressionInnerType&
			>
		);
		const typename decltype(instance)::OutputExpressionInnerType& actualExpression
		{
			returnValue.getInnerValue()
		};*/
		//actualExpression.source.get().sourceParts.front().get()
	}

#pragma endregion
}