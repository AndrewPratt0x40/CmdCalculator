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
		ASSERT_TRUE(returnValue);

		const auto* castedReturnValue
		{
			dynamic_cast<CmdCalculator::Expressions::DynamicAbsoluteValueOperation<ConvertedNumberType>*>
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
		ASSERT_TRUE(returnValue);
		const auto* castedReturnValue
		{
			dynamic_cast<CmdCalculator::Expressions::DynamicMultiplicationOperation<ConvertedNumberType>*>
				(returnValue.get())
		};
		ASSERT_TRUE(castedReturnValue);

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
		int wholePart;
		float fractionalPart;
		double expectedConvertedValue;


		friend std::ostream& operator<<
		(
			std::ostream& ostream,
			const getOperandAsExpression_DynamicNumberLiteralNode_TestData& testData
		)
		{
			ostream
				<< "BasicDynamicOperandToDynamicExpressionConverter.getOperandAsExpression(MathAst::DynamicNumberLiteralNode{"
				<< testData.wholePart
				<< '.'
				<< testData.fractionalPart
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

	const getOperandAsExpression_DynamicNumberLiteralNode_TestData getOperandAsExpression_DynamicNumberLiteralNode_TestDataValues[]
	{

		{
			.wholePart{ 0 },
			.fractionalPart{ 0.0 },
			.expectedConvertedValue{ 0.0 }
		},
		{
			.wholePart{ 0 },
			.fractionalPart{ 0.1 },
			.expectedConvertedValue{ 0.1 }
		},
		{
			.wholePart{ 0 },
			.fractionalPart{ 0.2 },
			.expectedConvertedValue{ 0.2 }
		},
		{
			.wholePart{ 0 },
			.fractionalPart{ 0.456 },
			.expectedConvertedValue{ 0.456 }
		},
		{
			.wholePart{ 0 },
			.fractionalPart{ 0.0456 },
			.expectedConvertedValue{ 0.0456 }
		},
		{
			.wholePart{ 0 },
			.fractionalPart{ 0.00456 },
			.expectedConvertedValue{ 0.00456 }
		},
		{
			.wholePart{ 0 },
			.fractionalPart{ 0.000456 },
			.expectedConvertedValue{ 0.000456 }
		},
		{
			.wholePart{ 1 },
			.fractionalPart{ 0.0 },
			.expectedConvertedValue{ 0.0 }
		},
		{
			.wholePart{ 1 },
			.fractionalPart{ 0.1 },
			.expectedConvertedValue{ 0.1 }
		},
		{
			.wholePart{ 1 },
			.fractionalPart{ 0.2 },
			.expectedConvertedValue{ 0.2 }
		},
		{
			.wholePart{ 1 },
			.fractionalPart{ 0.456 },
			.expectedConvertedValue{ 0.456 }
		},
		{
			.wholePart{ 1 },
			.fractionalPart{ 0.0456 },
			.expectedConvertedValue{ 0.0456 }
		},
		{
			.wholePart{ 1 },
			.fractionalPart{ 0.00456 },
			.expectedConvertedValue{ 0.00456 }
		},
		{
			.wholePart{ 1 },
			.fractionalPart{ 0.000456 },
			.expectedConvertedValue{ 1.000456 }
		},
		{
			.wholePart{ 2 },
			.fractionalPart{ 0.0 },
			.expectedConvertedValue{ 0.0 }
		},
		{
			.wholePart{ 2 },
			.fractionalPart{ 0.1 },
			.expectedConvertedValue{ 0.1 }
		},
		{
			.wholePart{ 2 },
			.fractionalPart{ 0.2 },
			.expectedConvertedValue{ 0.2 }
		},
		{
			.wholePart{ 2 },
			.fractionalPart{ 0.456 },
			.expectedConvertedValue{ 0.456 }
		},
		{
			.wholePart{ 2 },
			.fractionalPart{ 0.0456 },
			.expectedConvertedValue{ 0.0456 }
		},
		{
			.wholePart{ 2 },
			.fractionalPart{ 0.00456 },
			.expectedConvertedValue{ 0.00456 }
		},
		{
			.wholePart{ 2 },
			.fractionalPart{ 0.000456 },
			.expectedConvertedValue{ 2.000456 }
		},
		{
			.wholePart{ 123 },
			.fractionalPart{ 0.0 },
			.expectedConvertedValue{ 0.0 }
		},
		{
			.wholePart{ 123 },
			.fractionalPart{ 0.1 },
			.expectedConvertedValue{ 0.1 }
		},
		{
			.wholePart{ 123 },
			.fractionalPart{ 0.2 },
			.expectedConvertedValue{ 0.2 }
		},
		{
			.wholePart{ 123 },
			.fractionalPart{ 0.456 },
			.expectedConvertedValue{ 0.456 }
		},
		{
			.wholePart{ 123 },
			.fractionalPart{ 0.0456 },
			.expectedConvertedValue{ 0.0456 }
		},
		{
			.wholePart{ 123 },
			.fractionalPart{ 0.00456 },
			.expectedConvertedValue{ 0.00456 }
		},
		{
			.wholePart{ 123 },
			.fractionalPart{ 0.000456 },
			.expectedConvertedValue{ 123.000456 }
		},
		{
			.wholePart{ 1230 },
			.fractionalPart{ 0.0 },
			.expectedConvertedValue{ 0.0 }
		},
		{
			.wholePart{ 1230 },
			.fractionalPart{ 0.1 },
			.expectedConvertedValue{ 0.1 }
		},
		{
			.wholePart{ 1230 },
			.fractionalPart{ 0.2 },
			.expectedConvertedValue{ 0.2 }
		},
		{
			.wholePart{ 1230 },
			.fractionalPart{ 0.456 },
			.expectedConvertedValue{ 0.456 }
		},
		{
			.wholePart{ 1230 },
			.fractionalPart{ 0.0456 },
			.expectedConvertedValue{ 0.0456 }
		},
		{
			.wholePart{ 1230 },
			.fractionalPart{ 0.00456 },
			.expectedConvertedValue{ 0.00456 }
		},
		{
			.wholePart{ 1230 },
			.fractionalPart{ 0.000456 },
			.expectedConvertedValue{ 1230.000456 }
		},
		{
			.wholePart{ 12300 },
			.fractionalPart{ 0.0 },
			.expectedConvertedValue{ 0.0 }
		},
		{
			.wholePart{ 12300 },
			.fractionalPart{ 0.1 },
			.expectedConvertedValue{ 0.1 }
		},
		{
			.wholePart{ 12300 },
			.fractionalPart{ 0.2 },
			.expectedConvertedValue{ 0.2 }
		},
		{
			.wholePart{ 12300 },
			.fractionalPart{ 0.456 },
			.expectedConvertedValue{ 0.456 }
		},
		{
			.wholePart{ 12300 },
			.fractionalPart{ 0.0456 },
			.expectedConvertedValue{ 0.0456 }
		},
		{
			.wholePart{ 12300 },
			.fractionalPart{ 0.00456 },
			.expectedConvertedValue{ 0.00456 }
		},
		{
			.wholePart{ 12300 },
			.fractionalPart{ 0.000456 },
			.expectedConvertedValue{ 12300.000456 }
		},
		{
			.wholePart{ 123000 },
			.fractionalPart{ 0.0 },
			.expectedConvertedValue{ 0.0 }
		},
		{
			.wholePart{ 123000 },
			.fractionalPart{ 0.1 },
			.expectedConvertedValue{ 0.1 }
		},
		{
			.wholePart{ 123000 },
			.fractionalPart{ 0.2 },
			.expectedConvertedValue{ 0.2 }
		},
		{
			.wholePart{ 123000 },
			.fractionalPart{ 0.456 },
			.expectedConvertedValue{ 0.456 }
		},
		{
			.wholePart{ 123000 },
			.fractionalPart{ 0.0456 },
			.expectedConvertedValue{ 0.0456 }
		},
		{
			.wholePart{ 123000 },
			.fractionalPart{ 0.00456 },
			.expectedConvertedValue{ 0.00456 }
		},
		{
			.wholePart{ 123000 },
			.fractionalPart{ 0.000456 },
			.expectedConvertedValue{ 123000.000456 }
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		BasicDynamicOperandToDynamicExpressionConverterTests,
		BasicDynamicOperandToDynamicExpressionConverter$getOperandAsExpression$with$DynamicNumberLiteralNode$Tests,
		testing::ValuesIn(getOperandAsExpression_DynamicNumberLiteralNode_TestDataValues)
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
		const CmdCalculator::MathAst::DynamicNumberLiteralNode<std::string, int, float> sourceOperand
		{
			GetParam().wholePart,
			GetParam().fractionalPart,
			CmdCalculator::MathAst::EDynamicNumberLiteralNodePartsConfig::FullDecimal,
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
		ASSERT_TRUE(returnValue);

		const auto* castedReturnValue
		{
			dynamic_cast<CmdCalculator::Expressions::DynamicNumber<ConvertedNumberType>*>
				(returnValue.get())
		};
		ASSERT_TRUE(castedReturnValue);

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
		ASSERT_TRUE(returnValue);

		const auto* castedReturnValue
		{
			dynamic_cast<CmdCalculator::Expressions::DynamicNegationOperation<ConvertedNumberType>*>
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
		ASSERT_TRUE(returnValue);

		const auto* castedReturnValue
		{
			dynamic_cast<CmdCalculator::Expressions::DynamicNthRootOperation<ConvertedNumberType>*>
				(returnValue.get())
		};
		ASSERT_TRUE(castedReturnValue);

		const auto* castedReturnValueRadicand
		{
			dynamic_cast<typename StubInnerConverterType::ExpressionType*>
				(&castedReturnValue->getRadicand())
		};
		ASSERT_TRUE(castedReturnValueRadicand);
		
		EXPECT_EQ
		(
			sourceOperandInnerStringRepresentation,
			castedReturnValueRadicand->mathAstSource.getStringRepresentation()
		);

		const auto* castedReturnValueDegree
		{
			dynamic_cast<CmdCalculator::Expressions::DynamicNumber<ConvertedNumberType>*>
				(&castedReturnValue->getDegree())
		};
		ASSERT_TRUE(castedReturnValueDegree);

		EXPECT_DOUBLE_EQ
		(
			2.0,
			castedReturnValueDegree->getValue().getInnerValue()
		);
	}

#pragma endregion

#pragma endregion
}