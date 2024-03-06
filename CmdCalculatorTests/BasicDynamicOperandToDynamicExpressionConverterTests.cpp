#include "pch.h"

#include "../CmdCalculatorTestUtils/common.h"
#include "../CmdCalculator/BasicDynamicOperandToDynamicExpressionConverter.h"
#include "../CmdCalculator/DynamicOperandToDynamicExpressionConverter.h"
#include "../CmdCalculator/dynamic_mathast.h"
#include "../CmdCalculator/dynamic_expressions.h"
#include "../CmdCalculatorTestDoubles/StubTrackingMathAstToExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionNode.h"
#include "../CmdCalculatorTestDoubles/StubDynamicOperandNode.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpression.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"

#include <string>
#include <ranges>
#include <concepts>
#include <vector>
#include <optional>
#include <memory>
#include <functional>

// TODO: Don't use RTTI. Instead consider implementing double-dispatch, visitor pattern, something with std::visit, etc.
namespace CmdCalculatorTests
{
#pragma region Shared test data

	using FakeExpressionNumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
	using StubInnerConverterType = CmdCalculatorTestDoubles::StubTrackingMathAstToExpressionConverter
	<
		CmdCalculator::MathAst::DynamicExpressionNode<std::string>
	>;


	static std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionNode<std::string>>
		makeExpressionNode(const std::string str)
	{
		return std::make_unique<CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionNode<std::string>>
			(str, "", "")
		;
	}


	static std::unique_ptr<CmdCalculator::MathAst::DynamicOperandNode<std::string>>
		makeOperandNode(const std::string str)
	{
		return std::make_unique<CmdCalculatorTestDoubles::MathAst::StubDynamicOperandNode<std::string>>
			(CmdCalculator::MathAst::EDerivedDynamicOperandNodeKind::NumberLiteral, str, "", "")
		;
	}


	static StubInnerConverterType makeInnerConverter(const double convertedEvaluation = 0.0)
	{
		return StubInnerConverterType
		{
			.convertedEvaluation{convertedEvaluation}
		};
	}

#pragma endregion


#pragma region Concept satisfaction
	
	TEST(BasicDynamicOperandToDynamicExpressionConverterTests, BasicDynamicOperandToDynamicExpressionConverter$satisfies$the$DynamicOperandToDynamicExpressionConverter$concept)
	{
		static_assert
		(
			CmdCalculator::DynamicOperandToDynamicExpressionConverter
			<
				CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter
				<
					StubInnerConverterType,
					std::string,
					FakeExpressionNumberType
				>
			>
		);
	}

#pragma endregion


#pragma region getOperandAsExpression

#pragma region getOperandAsExpression(DynamicAbsoluteValueNode)

	TEST
	(
		BasicDynamicOperandToDynamicExpressionConverterTests,
		calling$getOperandAsExpression$with$DynamicAbsoluteValueNode$returns$DynamicAbsoluteValueOperation$with$converted$inner$expression
	)
	{
		// Arrange
		const StubInnerConverterType innerConverter{ makeInnerConverter() };
		const std::string sourceOperandInnerStringRepresentation{ "Source" };
		const CmdCalculator::MathAst::DynamicAbsoluteValueNode<std::string> sourceOperand
		{
			makeExpressionNode(sourceOperandInnerStringRepresentation),
			"", ""
		};
		const CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter
		<
			StubInnerConverterType,
			std::string,
			FakeExpressionNumberType
		> instance
		{
			innerConverter
		};

		// Act
		const std::unique_ptr<CmdCalculator::Expressions::DynamicExpression<FakeExpressionNumberType>> returnValue
		{
			instance.getOperandAsExpression(sourceOperand)
		};

		// Assert
		ASSERT_TRUE(returnValue);

		const auto* castedReturnValue
		{
			dynamic_cast<CmdCalculator::Expressions::DynamicAbsoluteValueOperation<FakeExpressionNumberType>*>
				(returnValue.get())
		};
		ASSERT_TRUE(castedReturnValue);

		const auto* castedReturnValueOperand
		{
			dynamic_cast<typename StubInnerConverterType::ExpressionType*>
				(&castedReturnValue->getOperand())
		};
		ASSERT_TRUE(castedReturnValueOperand);
		
		EXPECT_EQ
		(
			sourceOperandInnerStringRepresentation,
			castedReturnValueOperand->mathAstSource.getStringRepresentation()
		);
	}

#pragma endregion


#pragma region getOperandAsExpression(DynamicGroupingNode)

	TEST
	(
		BasicDynamicOperandToDynamicExpressionConverterTests,
		calling$getOperandAsExpression$with$DynamicGroupingNode$returns$converted$inner$expression
	)
	{
		// Arrange
		const StubInnerConverterType innerConverter{ makeInnerConverter() };
		const std::string sourceOperandInnerStringRepresentation{ "Source" };
		const CmdCalculator::MathAst::DynamicGroupingNode<std::string> sourceOperand
		{
			makeExpressionNode(sourceOperandInnerStringRepresentation),
			"", ""
		};
		const CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter
		<
			StubInnerConverterType,
			std::string,
			FakeExpressionNumberType
		> instance
		{
			innerConverter
		};

		// Act
		const std::unique_ptr<CmdCalculator::Expressions::DynamicExpression<FakeExpressionNumberType>> returnValue
		{
			instance.getOperandAsExpression(sourceOperand)
		};

		// Assert
		ASSERT_TRUE(returnValue);

		const auto* castedReturnValue
		{
			dynamic_cast<typename StubInnerConverterType::ExpressionType*>
				(returnValue.get())
		};
		ASSERT_TRUE(castedReturnValue);

		EXPECT_EQ
		(
			sourceOperandInnerStringRepresentation,
			castedReturnValue->mathAstSource.getStringRepresentation()
		);
	}

#pragma endregion


#pragma region getOperandAsExpression(DynamicGroupingMultiplicationNode)

	struct getOperandAsExpression_DynamicGroupingMultiplicationNode_TestData
	{
		std::vector<std::string> multiplicands;


		friend std::ostream& operator<<
		(
			std::ostream& ostream,
			const getOperandAsExpression_DynamicGroupingMultiplicationNode_TestData& testData
		)
		{
			ostream
				<< "BasicDynamicOperandToDynamicExpressionConverter.getOperandAsExpression(MathAst::DynamicGroupingMultiplicationNode{"
				<< CmdCalculatorTestUtils::joinStrings(testData.multiplicands)
				<< "})"
			;

			return ostream;
		}
	};

	class BasicDynamicOperandToDynamicExpressionConverter$getOperandAsExpression$with$DynamicGroupingMultiplicationNode$Tests :
		public testing::TestWithParam<getOperandAsExpression_DynamicGroupingMultiplicationNode_TestData>
	{};

	const getOperandAsExpression_DynamicGroupingMultiplicationNode_TestData getOperandAsExpression_DynamicGroupingMultiplicationNode_TestDataValues[]
	{
		{
			.multiplicands{ "Head", "Tail" }
		},
		{
			.multiplicands{ "Head", "Tail1", "Tail2" }
		},
		{
			.multiplicands{ "Head", "Tail1", "Tail2", "Tail3" }
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		BasicDynamicOperandToDynamicExpressionConverterTests,
		BasicDynamicOperandToDynamicExpressionConverter$getOperandAsExpression$with$DynamicGroupingMultiplicationNode$Tests,
		testing::ValuesIn(getOperandAsExpression_DynamicGroupingMultiplicationNode_TestDataValues)
	);


	TEST_P
	(
		BasicDynamicOperandToDynamicExpressionConverter$getOperandAsExpression$with$DynamicGroupingMultiplicationNode$Tests,
		calling$getOperandAsExpression$with$DynamicAbsoluteValueOperation$returns$DynamicMultiplicationOperation$with$expected$operands
	)
	{
		// Arrange
		ASSERT_TRUE(GetParam().multiplicands.size() > 1);

		const std::vector<std::string> multiplicandStrs{ GetParam().multiplicands };
		const StubInnerConverterType innerConverter{ makeInnerConverter() };

		std::vector<std::unique_ptr<CmdCalculator::MathAst::DynamicGroupingNode<std::string>>> tailMultiplicands
		{
			CmdCalculatorTestUtils::moveRangeToVector
			(
				multiplicandStrs
				| std::views::drop(1)
				| std::views::transform
				(
					[](const std::string& str)
					{
						return std::move
						(
							std::make_unique<CmdCalculator::MathAst::DynamicGroupingNode<std::string>>
								(makeExpressionNode(str), "", "")
						);
					}
				)
			)
		};

		const CmdCalculator::MathAst::DynamicGroupingMultiplicationNode<std::string> sourceOperand
		{
			makeOperandNode(*std::ranges::begin(multiplicandStrs)),
			std::move(std::ranges::owning_view<decltype(tailMultiplicands)>{ std::move(tailMultiplicands) }),
			"",
			""
		};
		const CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter
		<
			StubInnerConverterType,
			std::string,
			FakeExpressionNumberType
		> instance
		{
			innerConverter
		};

		// Act
		const std::unique_ptr<CmdCalculator::Expressions::DynamicExpression<FakeExpressionNumberType>> returnValue
		{
			instance.getOperandAsExpression(sourceOperand)
		};

		// Assert
		ASSERT_TRUE(returnValue);
		const auto* castedReturnValue
		{
			dynamic_cast<CmdCalculator::Expressions::DynamicMultiplicationOperation<FakeExpressionNumberType>*>
				(returnValue.get())
		};
		ASSERT_TRUE(castedReturnValue);

		std::function
		<
			void
			(
				const CmdCalculator::Expressions::DynamicMultiplicationOperation<FakeExpressionNumberType>&,
				const size_t
			)
		> validateReturnValue;
		validateReturnValue = [&validateReturnValue, &multiplicandStrs]
		(
			const CmdCalculator::Expressions::DynamicMultiplicationOperation<FakeExpressionNumberType>& actual,
			const size_t offset
		)
		{
			const std::string expectedMultiplier{ multiplicandStrs.at(offset) };
			const auto* actualMultiplier
			{
				dynamic_cast<typename StubInnerConverterType::ExpressionType*>
					(&actual.getMultiplier())
			};
			ASSERT_TRUE(actualMultiplier);

			EXPECT_EQ
			(
				expectedMultiplier,
				actualMultiplier->mathAstSource.getStringRepresentation()
			);

			const std::string expectedMultiplicand{ multiplicandStrs.at(offset + 1) };
			if (offset == multiplicandStrs.size() - 2)
			{
				const auto* actualMultiplicand
				{
					dynamic_cast<typename StubInnerConverterType::ExpressionType*>
						(&actual.getMultiplicand())
				};
				ASSERT_TRUE(actualMultiplicand);

				EXPECT_EQ
				(
					expectedMultiplicand,
					actualMultiplicand->mathAstSource.getStringRepresentation()
				);
			}
			else
			{
				const auto* actualMultiplicand
				{
					dynamic_cast<CmdCalculator::Expressions::DynamicMultiplicationOperation<FakeExpressionNumberType>*>
						(&actual.getMultiplicand())
				};
				ASSERT_TRUE(actualMultiplicand);

				validateReturnValue(*actualMultiplicand, offset + 1);
			}
		};

		validateReturnValue(*castedReturnValue, 0);
	}

#pragma endregion

#pragma endregion
}