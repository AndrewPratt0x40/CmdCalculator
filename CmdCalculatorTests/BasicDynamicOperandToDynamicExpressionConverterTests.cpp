#include "pch.h"

#include "../CmdCalculatorTestUtils/common.h"
#include "../CmdCalculator/BasicDynamicOperandToDynamicExpressionConverter.h"
#include "../CmdCalculator/DynamicOperandToDynamicExpressionConverter.h"
#include "../CmdCalculator/FundamentallyBackedRealNumber.h"
#include "../CmdCalculator/dynamic_mathast.h"
#include "../CmdCalculator/dynamic_expressions.h"
#include "../CmdCalculatorTestDoubles/StubTrackingDynamicMathAstToDynamicExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionNode.h"
#include "../CmdCalculatorTestDoubles/StubDynamicOperandNode.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpression.h"

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

	using ExpressionNumberType = CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<long double>;
	using StubInnerConverterType = CmdCalculatorTestDoubles::StubTrackingDynamicMathAstToDynamicExpressionConverter
	<
		CmdCalculator::MathAst::DynamicExpressionNode<std::string>,
		ExpressionNumberType
	>;
	using StubInnerConverterExpressionType = typename StubInnerConverterType::ExpressionType;
	using StubInnerConverterBoxedExpressionType = typename StubInnerConverterType::BoxedExpressionType;


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
			.sourceRootNodeFunc
			{
				[](const StubInnerConverterType::RootMathAstNodeType& sourceRootNode)
				{ return sourceRootNode.getStringRepresentation(); }
			},
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
					std::string
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
			std::string
		> instance
		{
			innerConverter
		};
		using ConvertedNumberType = decltype(instance)::ExpressionNumberType;

		// Act
		const std::unique_ptr<CmdCalculator::Expressions::DynamicExpression<ConvertedNumberType>> returnValue
		{
			instance.getOperandAsExpression(sourceOperand)
		};

		// Assert
		ASSERT_NE(nullptr, returnValue.get());

		const auto* castedReturnValue
		{
			dynamic_cast<CmdCalculator::Expressions::DynamicAbsoluteValueOperation<ConvertedNumberType>*>
				(returnValue.get())
		};
		ASSERT_NE(nullptr, castedReturnValue);

		const auto* castedReturnValueOperand
		{
			dynamic_cast<StubInnerConverterBoxedExpressionType*>
				(&castedReturnValue->getOperand())
		};
		ASSERT_NE(nullptr, castedReturnValueOperand);
		
		EXPECT_EQ
		(
			sourceOperandInnerStringRepresentation,
			castedReturnValueOperand->source
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
			std::string
		> instance
		{
			innerConverter
		};
		using ConvertedNumberType = decltype(instance)::ExpressionNumberType;

		// Act
		const std::unique_ptr<CmdCalculator::Expressions::DynamicExpression<ConvertedNumberType>> returnValue
		{
			instance.getOperandAsExpression(sourceOperand)
		};

		// Assert
		ASSERT_NE(nullptr, returnValue.get());

		const auto* castedReturnValue
		{
			dynamic_cast<StubInnerConverterBoxedExpressionType*>
				(returnValue.get())
		};
		ASSERT_NE(nullptr, castedReturnValue);

		EXPECT_EQ
		(
			sourceOperandInnerStringRepresentation,
			castedReturnValue->source
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
			std::string
		> instance
		{
			innerConverter
		};
		using ConvertedNumberType = decltype(instance)::ExpressionNumberType;

		// Act
		const std::unique_ptr<CmdCalculator::Expressions::DynamicExpression<ConvertedNumberType>> returnValue
		{
			instance.getOperandAsExpression(sourceOperand)
		};

		// Assert
		ASSERT_NE(nullptr, returnValue.get());
		const auto* castedReturnValue
		{
			dynamic_cast<CmdCalculator::Expressions::DynamicMultiplicationOperation<ConvertedNumberType>*>
				(returnValue.get())
		};
		ASSERT_NE(nullptr, castedReturnValue);

		std::function
		<
			void
			(
				const CmdCalculator::Expressions::DynamicMultiplicationOperation<ConvertedNumberType>&,
				const size_t
			)
		> validateReturnValue;
		validateReturnValue = [&validateReturnValue, &multiplicandStrs]
		(
			const CmdCalculator::Expressions::DynamicMultiplicationOperation<ConvertedNumberType>& actual,
			const size_t offset
		)
		{
			const std::string expectedMultiplier{ multiplicandStrs.at(offset) };
			const auto* actualMultiplier
			{
				dynamic_cast<StubInnerConverterBoxedExpressionType*>
					(&actual.getMultiplier())
			};
			ASSERT_TRUE(actualMultiplier);

			EXPECT_EQ
			(
				expectedMultiplier,
				actualMultiplier->source
			);

			const std::string expectedMultiplicand{ multiplicandStrs.at(offset + 1) };
			if (offset == multiplicandStrs.size() - 2)
			{
				const auto* actualMultiplicand
				{
					dynamic_cast<StubInnerConverterBoxedExpressionType*>
						(&actual.getMultiplicand())
				};
				ASSERT_TRUE(actualMultiplicand);

				EXPECT_EQ
				(
					expectedMultiplicand,
					actualMultiplicand->source
				);
			}
			else
			{
				const auto* actualMultiplicand
				{
					dynamic_cast<CmdCalculator::Expressions::DynamicMultiplicationOperation<ConvertedNumberType>*>
						(&actual.getMultiplicand())
				};
				ASSERT_TRUE(actualMultiplicand);

				validateReturnValue(*actualMultiplicand, offset + 1);
			}
		};

		validateReturnValue(*castedReturnValue, 0);
	}

#pragma endregion


#pragma region getOperandAsExpression(DynamicNumberLiteralNode)

	struct getOperandAsExpression_DynamicNumberLiteralNode_TestData
	{
		std::optional<std::string> wholePart;
		std::optional<std::string> fractionalPart;
		bool isDecimalPointVisible;
		double expectedConvertedValue;


		friend std::ostream& operator<<
		(
			std::ostream& ostream,
			const getOperandAsExpression_DynamicNumberLiteralNode_TestData& testData
		)
		{
			ostream
				<< "BasicDynamicOperandToDynamicExpressionConverter.getOperandAsExpression(MathAst::DynamicNumberLiteralNode{"
				<< (testData.wholePart.has_value() ? testData.wholePart.value() : "")
				<< (testData.isDecimalPointVisible ? "." : "")
				<< (testData.fractionalPart.has_value() ? testData.fractionalPart.value() : "")
				<< "}) = Expressions::DynamicNumber{"
				<< testData.expectedConvertedValue
				<< '}'
			;

			return ostream;
		}
	};



	class BasicDynamicOperandToDynamicExpressionConverter$getOperandAsExpression$with$DynamicNumberLiteralNode$Tests :
		public testing::TestWithParam<getOperandAsExpression_DynamicNumberLiteralNode_TestData>
	{};


	struct NumberPartTestData
	{
		std::string str;
		int asWholePart;
		float asFractionalPart;
	};

	const std::initializer_list<NumberPartTestData> numberPartTestDataValues
	{
		{
			.str{ "0" },
			.asWholePart{ 0 },
			.asFractionalPart{ 0.0 }
		},
		{
			.str{ "1" },
			.asWholePart{ 1 },
			.asFractionalPart{ 0.1 }
		},
		{
			.str{ "5" },
			.asWholePart{ 5 },
			.asFractionalPart{ 0.5 }
		},
		{
			.str{ "00" },
			.asWholePart{ 0 },
			.asFractionalPart{ 0.0 }
		},
		{
			.str{ "01" },
			.asWholePart{ 1 },
			.asFractionalPart{ 0.01 }
		},
		{
			.str{ "05" },
			.asWholePart{ 5 },
			.asFractionalPart{ 0.05 }
		},
		{
			.str{ "10" },
			.asWholePart{ 10 },
			.asFractionalPart{ 0.1 }
		},
		{
			.str{ "11" },
			.asWholePart{ 11 },
			.asFractionalPart{ 0.11 }
		},
		{
			.str{ "15" },
			.asWholePart{ 15 },
			.asFractionalPart{ 0.15 }
		},
		{
			.str{ "50" },
			.asWholePart{ 5 },
			.asFractionalPart{ 0.5 }
		},
		{
			.str{ "51" },
			.asWholePart{ 51 },
			.asFractionalPart{ 0.51 }
		},
		{
			.str{ "55" },
			.asWholePart{ 55 },
			.asFractionalPart{ 0.55 }
		},
		{
			.str{ "000" },
			.asWholePart{ 0 },
			.asFractionalPart{ 0.0 }
		},
		{
			.str{ "001" },
			.asWholePart{ 1 },
			.asFractionalPart{ 0.001 }
		},
		{
			.str{ "005" },
			.asWholePart{ 5 },
			.asFractionalPart{ 0.005 }
		},
		{
			.str{ "010" },
			.asWholePart{ 10 },
			.asFractionalPart{ 0.01 }
		},
		{
			.str{ "011" },
			.asWholePart{ 11 },
			.asFractionalPart{ 0.011 }
		},
		{
			.str{ "015" },
			.asWholePart{ 15 },
			.asFractionalPart{ 0.015 }
		},
		{
			.str{ "050" },
			.asWholePart{ 50 },
			.asFractionalPart{ 0.05 }
		},
		{
			.str{ "051" },
			.asWholePart{ 51 },
			.asFractionalPart{ 0.051 }
		},
		{
			.str{ "055" },
			.asWholePart{ 55 },
			.asFractionalPart{ 0.055 }
		},
		{
			.str{ "100" },
			.asWholePart{ 100 },
			.asFractionalPart{ 0.1 }
		},
		{
			.str{ "101" },
			.asWholePart{ 101 },
			.asFractionalPart{ 0.101 }
		},
		{
			.str{ "105" },
			.asWholePart{ 105 },
			.asFractionalPart{ 0.105 }
		},
		{
			.str{ "110" },
			.asWholePart{ 110 },
			.asFractionalPart{ 0.11 }
		},
		{
			.str{ "111" },
			.asWholePart{ 111 },
			.asFractionalPart{ 0.111 }
		},
		{
			.str{ "115" },
			.asWholePart{ 115 },
			.asFractionalPart{ 0.115 }
		}
	};


	const std::ranges::forward_range auto getOperandAsExpression_DynamicNumberLiteralNode_TestDataValues
	{
		[]()
		{
			std::vector<getOperandAsExpression_DynamicNumberLiteralNode_TestData> testDataValues
			{
				{
					.wholePart{},
					.fractionalPart{ std::make_optional<std::string>("456") },
					.isDecimalPointVisible{ true },
					.expectedConvertedValue{ 0.456 }
				},
				{
					.wholePart{ std::make_optional<std::string>("123") },
					.fractionalPart{},
					.isDecimalPointVisible{ true },
					.expectedConvertedValue{ 123.0 }
				},
				{
					.wholePart{ std::make_optional<std::string>("123") },
					.fractionalPart{},
					.isDecimalPointVisible{ false },
					.expectedConvertedValue{ 123.0 }
				},
				{
					.wholePart{ std::make_optional<std::string>("123") },
					.fractionalPart{ std::make_optional<std::string>("456") },
					.isDecimalPointVisible{ true },
					.expectedConvertedValue{ 123.456 }
				}
			};

			for (const NumberPartTestData& wholePartData : numberPartTestDataValues)
			{
				for (const NumberPartTestData& fractionalPartData : numberPartTestDataValues)
				{
					testDataValues.push_back
					(
						getOperandAsExpression_DynamicNumberLiteralNode_TestData
						{
							.wholePart{ std::make_optional<std::string>(wholePartData.str) },
							.fractionalPart{ std::make_optional<std::string>(fractionalPartData.str) },
							.isDecimalPointVisible{ true },
							.expectedConvertedValue{ wholePartData.asWholePart + fractionalPartData.asFractionalPart }
						}
					);
				}
			}

			return testDataValues;
		}()
	};

	INSTANTIATE_TEST_CASE_P
	(
		BasicDynamicOperandToDynamicExpressionConverterTests,
		BasicDynamicOperandToDynamicExpressionConverter$getOperandAsExpression$with$DynamicNumberLiteralNode$Tests,
		CmdCalculatorTestUtils::ValuesInRange(getOperandAsExpression_DynamicNumberLiteralNode_TestDataValues)
	);


	TEST_P
	(
		BasicDynamicOperandToDynamicExpressionConverter$getOperandAsExpression$with$DynamicNumberLiteralNode$Tests,
		calling$getOperandAsExpression$with$DynamicNumberLiteralNode$returns$DynamicNumber
	)
	{
		// Arrange
		const StubInnerConverterType innerConverter{ makeInnerConverter() };
		const std::string sourceOperandInnerStringRepresentation{ "Source" };
		const CmdCalculator::MathAst::DynamicNumberLiteralNode<std::string> sourceOperand
		{
			GetParam().wholePart,
			GetParam().fractionalPart,
			GetParam().isDecimalPointVisible,
			"",
			""
		};

		const double expectedConvertedValue{ GetParam().expectedConvertedValue };

		const CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter
		<
			StubInnerConverterType,
			std::string
		> instance
		{
			innerConverter
		};
		using ConvertedNumberType = decltype(instance)::ExpressionNumberType;

		// Act
		const std::unique_ptr<CmdCalculator::Expressions::DynamicExpression<ConvertedNumberType>> returnValue
		{
			instance.getOperandAsExpression(sourceOperand)
		};

		// Assert
		ASSERT_NE(nullptr, returnValue.get());

		const auto* castedReturnValue
		{
			dynamic_cast<CmdCalculator::Expressions::DynamicNumber<ConvertedNumberType>*>
				(returnValue.get())
		};
		ASSERT_NE(nullptr, castedReturnValue);

		EXPECT_DOUBLE_EQ
		(
			expectedConvertedValue,
			castedReturnValue->getValue().getInnerValue()
		);
	}

#pragma endregion


#pragma region getOperandAsExpression(DynamicSignOperationNode)

	TEST
	(
		BasicDynamicOperandToDynamicExpressionConverterTests,
		calling$getOperandAsExpression$with$DynamicSignOperationNode$with$positive$sign$returns$converted$inner$expression
	)
	{
		// Arrange
		const StubInnerConverterType innerConverter{ makeInnerConverter() };
		const std::string sourceOperandInnerStringRepresentation{ "Source" };
		const CmdCalculator::MathAst::DynamicSignOperationNode<std::string> sourceOperand
		{
			makeOperandNode(sourceOperandInnerStringRepresentation),
			true,
			"", "", ""
		};
		const CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter
		<
			StubInnerConverterType,
			std::string
		> instance
		{
			innerConverter
		};
		using ConvertedNumberType = decltype(instance)::ExpressionNumberType;

		// Act
		const std::unique_ptr<CmdCalculator::Expressions::DynamicExpression<ConvertedNumberType>> returnValue
		{
			instance.getOperandAsExpression(sourceOperand)
		};

		// Assert
		ASSERT_NE(nullptr, returnValue.get());

		const auto* castedReturnValue
		{
			dynamic_cast<StubInnerConverterBoxedExpressionType*>
				(returnValue.get())
		};
		ASSERT_NE(nullptr, castedReturnValue);

		EXPECT_EQ
		(
			sourceOperandInnerStringRepresentation,
			castedReturnValue->source
		);
	}


	TEST
	(
		BasicDynamicOperandToDynamicExpressionConverterTests,
		calling$getOperandAsExpression$with$DynamicSignOperationNode$with$negative$sign$returns$DynamicNegationExpression
	)
	{
		// Arrange
		const StubInnerConverterType innerConverter{ makeInnerConverter() };
		const std::string sourceOperandInnerStringRepresentation{ "Source" };
		const CmdCalculator::MathAst::DynamicSignOperationNode<std::string> sourceOperand
		{
			makeOperandNode(sourceOperandInnerStringRepresentation),
			false,
			"", "", ""
		};
		const CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter
		<
			StubInnerConverterType,
			std::string
		> instance
		{
			innerConverter
		};
		using ConvertedNumberType = decltype(instance)::ExpressionNumberType;

		// Act
		const std::unique_ptr<CmdCalculator::Expressions::DynamicExpression<ConvertedNumberType>> returnValue
		{
			instance.getOperandAsExpression(sourceOperand)
		};

		// Assert
		ASSERT_NE(nullptr, returnValue.get());

		const auto* castedReturnValue
		{
			dynamic_cast<CmdCalculator::Expressions::DynamicNegationOperation<ConvertedNumberType>*>
				(returnValue.get())
		};
		ASSERT_NE(nullptr, castedReturnValue);

		const auto* castedReturnValueOperand
		{
			dynamic_cast<StubInnerConverterBoxedExpressionType*>
				(&castedReturnValue->getOperand())
		};
		ASSERT_NE(nullptr, castedReturnValueOperand);

		EXPECT_EQ
		(
			sourceOperandInnerStringRepresentation,
			castedReturnValueOperand->source
		);
	}

#pragma endregion


#pragma region getOperandAsExpression(DynamicSqrtOperationNode)

	TEST
	(
		BasicDynamicOperandToDynamicExpressionConverterTests,
		calling$getOperandAsExpression$with$DynamicSqrtOperationNode$returns$DynamicNthRootOperation
	)
	{
		// Arrange
		const StubInnerConverterType innerConverter{ makeInnerConverter() };
		const std::string sourceOperandInnerStringRepresentation{ "Source" };
		const CmdCalculator::MathAst::DynamicSqrtOperationNode<std::string> sourceOperand
		{
			makeOperandNode(sourceOperandInnerStringRepresentation),
			"", "", ""
		};
		const CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter
		<
			StubInnerConverterType,
			std::string
		> instance
		{
			innerConverter
		};
		using ConvertedNumberType = decltype(instance)::ExpressionNumberType;

		// Act
		const std::unique_ptr<CmdCalculator::Expressions::DynamicExpression<ConvertedNumberType>> returnValue
		{
			instance.getOperandAsExpression(sourceOperand)
		};

		// Assert
		ASSERT_NE(nullptr, returnValue.get());

		const auto* castedReturnValue
		{
			dynamic_cast<CmdCalculator::Expressions::DynamicNthRootOperation<ConvertedNumberType>*>
				(returnValue.get())
		};
		ASSERT_NE(nullptr, castedReturnValue);

		const auto* castedReturnValueRadicand
		{
			dynamic_cast<StubInnerConverterBoxedExpressionType*>
				(&castedReturnValue->getRadicand())
		};
		ASSERT_NE(nullptr, castedReturnValueRadicand);
		
		EXPECT_EQ
		(
			sourceOperandInnerStringRepresentation,
			castedReturnValueRadicand->source
		);

		const auto* castedReturnValueDegree
		{
			dynamic_cast<CmdCalculator::Expressions::DynamicNumber<ConvertedNumberType>*>
				(&castedReturnValue->getDegree())
		};
		ASSERT_NE(nullptr, castedReturnValueDegree);

		EXPECT_DOUBLE_EQ
		(
			2.0,
			castedReturnValueDegree->getValue().getInnerValue()
		);
	}

#pragma endregion

#pragma endregion
}