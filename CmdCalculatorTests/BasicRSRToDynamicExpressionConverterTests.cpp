#include "pch.h"

#include <string>
#include <concepts>
#include <ranges>
#include <functional>
#include <vector>

#include "../CmdCalculator/BasicRSRToDynamicExpressionConverter.h"
#include "../CmdCalculator/RecursiveSplitResultToDynamicExpressionConverter.h"
#include "../CmdCalculator/dynamic_mathast.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionPartRecursiveSplitResult.h"
#include "../CmdCalculatorTestDoubles/StubDynamicOperandToDynamicExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionNode.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"


namespace CmdCalculatorTests
{
#pragma region Shared test data

	using ExpressionNumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
	using StubInnerOperandConverterType = CmdCalculatorTestDoubles::StubDynamicOperandToDynamicExpressionConverter
	<
		std::string,
		ExpressionNumberType
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
		return std::make_unique<CmdCalculator::MathAst::DynamicNumberLiteralNode<std::string>>
		(
			std::make_optional<std::string>(str),
			std::optional<std::string>{},
			false, "", ""
		);
	}


	static StubInnerOperandConverterType makeInnerOperandConverter(const double err = -1.0)
	{
		return StubInnerOperandConverterType
		{
			.convertedOperandEvaluation
			{
				[&err](const CmdCalculator::MathAst::DynamicOperandNode<std::string>& sourceOperand)
				{
					double eval;
					try
					{
						eval = std::stod(sourceOperand.getStringRepresentation());
					}
					catch (const std::invalid_argument&)
					{
						return err;
					}
					return eval;
				}
			}
		};
	}

#pragma endregion


#pragma region Concept satisfaction
	
	TEST(BasicRSRToDynamicExpressionConverterTests, BasicRSRToDynamicExpressionConverter$satisfies$the$RecursiveSplitResultToDynamicExpressionConverter$concept)
	{
		static_assert
		(
			CmdCalculator::RecursiveSplitResultToDynamicExpressionConverter
			<
				CmdCalculator::BasicRSRToDynamicExpressionConverter
				<
					CmdCalculatorTestDoubles::StubDynamicExpressionPartRecursiveSplitResult
					<
						std::string
					>,
					CmdCalculatorTestDoubles::StubDynamicOperandToDynamicExpressionConverter
					<
						std::string,
						CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber
					>,
					std::string
				>
			>
		);
	}

#pragma endregion


#pragma region getSplitResultAsExpression

#pragma region getSplitResultAsExpression(splitPart=DynamicOperandNode)

	struct getSplitResultAsExpression_with_DynamicOperandNode_TestData
	{
		std::string splitPartDerivedTypeName;
		std::function<std::unique_ptr<CmdCalculator::MathAst::DynamicOperandNode<std::string>>()> splitPart;


		friend std::ostream& operator<<
		(
			std::ostream& ostream,
			const getSplitResultAsExpression_with_DynamicOperandNode_TestData& testData
		)
		{
			ostream
				<< "BasicRSRToDynamicExpressionConverter.getSplitResultAsExpression("
				<< testData.splitPartDerivedTypeName
				<< ')'
			;

			return ostream;
		}
	};

	class BasicRSRToDynamicExpressionConverter$with$DynamicOperandNode$Tests :
		public testing::TestWithParam<getSplitResultAsExpression_with_DynamicOperandNode_TestData>
	{};

	const getSplitResultAsExpression_with_DynamicOperandNode_TestData getSplitResultAsExpression_with_DynamicOperandNode_TestDataValues[]
	{
		{
			.splitPartDerivedTypeName{ "DynamicAbsoluteValueNode" },
			.splitPart
			{
				[]()
				{
					return std::make_unique<CmdCalculator::MathAst::DynamicAbsoluteValueNode<std::string>>
					(
						makeExpressionNode("123.456"), "", ""
					);
				}
			}
		},
		{
			.splitPartDerivedTypeName{ "DynamicGroupingNode" },
			.splitPart
			{
				[]()
				{
					return std::make_unique<CmdCalculator::MathAst::DynamicGroupingNode<std::string>>
					(
						makeExpressionNode("123.456"), "", ""
					);
				}
			}
		},
		{
			.splitPartDerivedTypeName{ "DynamicGroupingMultiplicationNode" },
			.splitPart
			{
				[]()
				{
#if __cplusplus >= 202302L
					std::ranges::single_view<std::unique_ptr<CmdCalculator::MathAst::DynamicGroupingNode<std::string>>> tailMultiplicands
					{
						std::move
						(
							std::make_unique<CmdCalculator::MathAst::DynamicGroupingNode<std::string>>
								(makeExpressionNode("789.10"), "", "")
						)
					};
#else
					std::vector<std::unique_ptr<CmdCalculator::MathAst::DynamicGroupingNode<std::string>>> tailMultiplicands{};
					tailMultiplicands.emplace_back
					(
						std::move
						(
							std::make_unique<CmdCalculator::MathAst::DynamicGroupingNode<std::string>>
								(makeExpressionNode("789.10"), "", "")
						)
					);
#endif

					return std::make_unique<CmdCalculator::MathAst::DynamicGroupingMultiplicationNode<std::string>>
					(
						makeOperandNode("123.456"),
						std::move
						(
							std::ranges::owning_view<decltype(tailMultiplicands)>
							{
								std::move(tailMultiplicands)
							}
						),
						"", ""
					);
				}
			}
		},
		{
			.splitPartDerivedTypeName{ "DynamicNumberLiteralNode" },
			.splitPart
			{
				[]()
				{
					return std::make_unique<CmdCalculator::MathAst::DynamicNumberLiteralNode<std::string>>
					(
						std::make_optional<std::string>("123"),
						std::make_optional<std::string>("456"),
						true, "", ""
					);
				}
			}
		},
		{
			.splitPartDerivedTypeName{ "DynamicSignOperationNode" },
			.splitPart
			{
				[]()
				{
					return std::make_unique<CmdCalculator::MathAst::DynamicSignOperationNode<std::string>>
					(
						makeOperandNode("123.456"),
						true, "", "", ""
					);
				}
			}
		},
		{
			.splitPartDerivedTypeName{ "DynamicSqrtOperationNode" },
			.splitPart
			{
				[]()
				{
					return std::make_unique<CmdCalculator::MathAst::DynamicSqrtOperationNode<std::string>>
					(
						makeOperandNode("123.456"),
						"", "", ""
					);
				}
			}
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		BasicRSRToDynamicExpressionConverterTests,
		BasicRSRToDynamicExpressionConverter$with$DynamicOperandNode$Tests,
		testing::ValuesIn(getSplitResultAsExpression_with_DynamicOperandNode_TestDataValues)
	);

	TEST_P
	(
		BasicRSRToDynamicExpressionConverter$with$DynamicOperandNode$Tests,
		calling$getSplitResultAsExpression$with$a$DynamicOperandNode$split$part$returns$the$result$of$invoking$the$inner$operand$converter
	)
	{
		// Arrange
		const std::unique_ptr<CmdCalculator::MathAst::DynamicOperandNode<std::string>> splitPart
		{
			GetParam().splitPart()
		};
		ASSERT_NE(nullptr, splitPart.get());

		const CmdCalculatorTestDoubles::StubDynamicExpressionPartRecursiveSplitResult<std::string> splitResult
		{
			.leftPart{},
			.splitPart{ std::ref(*splitPart) },
			.rightPart{}
		};

		StubInnerOperandConverterType innerOperandConverter{ makeInnerOperandConverter() };

		const ExpressionNumberType expectedEvaluation
		{
			innerOperandConverter.getOperandAsExpression(*splitPart)->getEvaluation()
		};

		CmdCalculator::BasicRSRToDynamicExpressionConverter
		<
			std::remove_cv_t<decltype(splitResult)>,
			std::remove_cv_t<decltype(innerOperandConverter)>,
			std::string
		> instance
		{
			innerOperandConverter
		};

		// Act
		const CmdCalculator::UniquePtr auto returnValue
		{
			instance.getSplitResultAsExpression(splitResult)
		};

		// Assert
		ASSERT_NE(nullptr, returnValue.get());

		EXPECT_EQ(expectedEvaluation, returnValue->getEvaluation());
	}

#pragma endregion

#pragma endregion
}