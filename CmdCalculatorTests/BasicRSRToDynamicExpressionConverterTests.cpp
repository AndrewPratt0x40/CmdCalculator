#include "pch.h"

#include <string>
#include <concepts>
#include <ranges>
#include <functional>
#include <vector>

#include "../CmdCalculator/BasicRSRToDynamicExpressionConverter.h"
#include "../CmdCalculator/RecursiveSplitResultToDynamicExpressionConverter.h"
#include "../CmdCalculator/dynamic_mathast.h"
#include "../CmdCalculator/dynamic_expressions.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionPartRecursiveSplitResult.h"
#include "../CmdCalculatorTestDoubles/StubDynamicOperandToDynamicExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/StubTrackingDynamicOperandToDynamicExpressionConverter.h"
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
	using StubTrackingInnerOperandConverterType = CmdCalculatorTestDoubles::StubTrackingDynamicOperandToDynamicExpressionConverter
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


	static StubInnerOperandConverterType makeTrackingInnerOperandConverter()
	{
		return StubInnerOperandConverterType
		{
			.convertedOperandEvaluation{ 0.0 }
		};
	}


	class CompositeSplitResultTestData
	{
	public:
		using SplitResultType = CmdCalculatorTestDoubles::StubDynamicExpressionPartRecursiveSplitResult<std::string>;


	private:
		
		std::string m_leftSplitPartStr;
		std::string m_rightSplitPartStr;

		std::unique_ptr<CmdCalculator::MathAst::DynamicOperandNode<std::string>> m_leftSplitPart;
		std::unique_ptr<CmdCalculator::MathAst::DynamicOperandNode<std::string>> m_rightSplitPart;

		SplitResultType m_splitResult;


	public:

		CompositeSplitResultTestData
		(
			const std::string leftSplitPartStr,
			const CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>& splitPart,
			const std::string rightSplitPartStr
		) :
			m_leftSplitPartStr{ leftSplitPartStr },
			m_rightSplitPartStr{ rightSplitPartStr },
			m_leftSplitPart{ makeOperandNode(leftSplitPartStr) },
			m_rightSplitPart{ makeOperandNode(rightSplitPartStr) },
			m_splitResult
			{
				.leftPart
				{
					std::make_unique<SplitResultType>
					(
						SplitResultType
						{
							.leftPart{},
							.splitPart{ std::ref(*m_leftSplitPart) },
							.rightPart{}
						}
					)
				},
				.splitPart{ std::ref(splitPart) },
				.rightPart
				{
					std::make_unique<SplitResultType>
					(
						SplitResultType
						{
							.leftPart{},
							.splitPart{ std::ref(*m_rightSplitPart) },
							.rightPart{}
						}
					)
				}
			}
		{
			assert(m_leftSplitPart);
			assert(m_rightSplitPart);

			assert(m_splitResult.leftPart);
			assert(m_splitResult.rightPart);

			assert(std::addressof(m_splitResult.leftPart->splitPart.get()) == m_leftSplitPart.get());
			assert(std::addressof(m_splitResult.rightPart->splitPart.get()) == m_rightSplitPart.get());

			assert(m_leftSplitPart->getStringRepresentation() == m_leftSplitPartStr);
			assert(m_rightSplitPart->getStringRepresentation() == m_rightSplitPartStr);
		}


		const SplitResultType& getSplitResult() const
		{
			return m_splitResult;
		}
	};

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

		StubTrackingInnerOperandConverterType innerOperandConverter{ makeTrackingInnerOperandConverter() };

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

		const auto* castedReturnValue
		{
			dynamic_cast<typename StubTrackingInnerOperandConverterType::ExpressionType*>
				(returnValue.get())
		};
		ASSERT_NE(nullptr, castedReturnValue);

		EXPECT_EQ
		(
			splitPart->getStringRepresentation(),
			castedReturnValue->source.get().getStringRepresentation()
		);
	}

#pragma endregion


#pragma region getSplitResultAsExpression(splitPart=Addition)

	TEST
	(
		BasicRSRToDynamicExpressionConverterTests,
		calling$getSplitResultAsExpression$with$addition$DynamicBinaryOperatorNode$returns$DynamicAbsoluteValueOperation
	)
	{
		const std::string leftSplitPartStr{ "12.34" };
		const std::string rightSplitPartStr{ "56.78" };
		
		const CmdCalculator::MathAst::DynamicBinaryOperatorNode<std::string> splitPart
		{
			CmdCalculator::MathAst::EBinaryOperator::Addition,
			"", ""
		};

		const CompositeSplitResultTestData splitResultData
		{
			leftSplitPartStr,
			splitPart,
			rightSplitPartStr
		};

		StubTrackingInnerOperandConverterType innerOperandConverter{ makeTrackingInnerOperandConverter() };

		CmdCalculator::BasicRSRToDynamicExpressionConverter
		<
			CompositeSplitResultTestData::SplitResultType,
			std::remove_cv_t<decltype(innerOperandConverter)>,
			std::string
		> instance
		{
			innerOperandConverter
		};

		// Act
		const CmdCalculator::UniquePtr auto returnValue
		{
			instance.getSplitResultAsExpression(splitResultData.getSplitResult())
		};

		// Assert
		ASSERT_NE(nullptr, returnValue.get());

		const auto* castedReturnValue
		{
			dynamic_cast<CmdCalculator::Expressions::DynamicAdditionOperation<ExpressionNumberType>*>
				(returnValue.get())
		};
		ASSERT_NE(nullptr, castedReturnValue);

		const auto& castedReturnValueAugend
		{
			dynamic_cast<typename StubTrackingInnerOperandConverterType::ExpressionType*>
				(&castedReturnValue->getAugend())
		};
		ASSERT_NE(nullptr, castedReturnValueAugend);

		const auto& castedReturnValueAddend
		{
			dynamic_cast<typename StubTrackingInnerOperandConverterType::ExpressionType*>
				(&castedReturnValue->getAddend())
		};
		ASSERT_NE(nullptr, castedReturnValueAddend);

		EXPECT_EQ
		(
			leftSplitPartStr,
			castedReturnValueAugend->source.get().getStringRepresentation()
		);

		EXPECT_EQ
		(
			rightSplitPartStr,
			castedReturnValueAddend->source.get().getStringRepresentation()
		);
	}

#pragma endregion
}