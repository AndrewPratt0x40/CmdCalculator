#include "pch.h"

#include "../CmdCalculator/AntlrContextToDynamicMathAstConverter.h"
#include "../CmdCalculator/AntlrContextToMathAstConverter.h"
#include "../CmdCalculatorTestDoubles/StubFullExpressionAntlrContext.h"

#include <algorithm>
#include <string>
#include <string_view>
#include <ranges>
#include <concepts>
#include <assert.h>
#include <vector>
#include <optional>


namespace CmdCalculatorTests
{
#pragma region Stub generation utilities
	static CmdCalculatorTestDoubles::StubAntlrToken<std::string> makeToken(const std::string txt)
	{
		return CmdCalculatorTestDoubles::StubAntlrToken<std::string>
		{
			.text{ txt },
			.startIndex{ 0 },
			.stopIndex{ 1 }
		};
	}


	static std::optional<CmdCalculatorTestDoubles::StubAntlrToken<std::string>> makeOptionalToken(const std::string txt)
	{
		return std::make_optional<CmdCalculatorTestDoubles::StubAntlrToken<std::string>>(makeToken(txt));
	}


	static CmdCalculatorTestDoubles::StubAntlrToken<std::string> makeNumToken(const int num)
	{
		return makeToken(std::to_string(num));
	}


	static std::optional<CmdCalculatorTestDoubles::StubAntlrToken<std::string>> makeOptionalNumToken(const int num)
	{
		return std::make_optional<CmdCalculatorTestDoubles::StubAntlrToken<std::string>>(makeNumToken(num));
	}


	static CmdCalculatorTestDoubles::StubNumberLiteralAntlrContext makeNumLiteralCtx(const int num)
	{
		return CmdCalculatorTestDoubles::StubNumberLiteralAntlrContext
		{
			.numberLiteralAntlrContextKind{ CmdCalculator::ENumberLiteralAntlrContextKind::Wholeful },
			.wholefulNumberLiteral
			{
				std::make_optional<CmdCalculatorTestDoubles::StubWholefulNumberLiteralAntlrContext>
				(
					CmdCalculatorTestDoubles::StubWholefulNumberLiteralAntlrContext
					{
						.wholePart{ makeNumToken(num) },
						.decimalPoint{},
						.fractionalPart{}
					}
				)
			},
			.wholelessNumberLiteral{}
		};
	}


	static CmdCalculatorTestDoubles::StubNonGroupingMultiplicationAntlrContext makeNonGroupMultNumLiteralCtx(const int num)
	{
		return CmdCalculatorTestDoubles::StubNonGroupingMultiplicationAntlrContext
		{
			.nonGroupingMultiplicationKind{ CmdCalculator::ENonGroupingMultiplicationAntlrContextKind::NumberLiteral },
			.numberLiteral
			{
				std::make_optional<CmdCalculatorTestDoubles::StubNumberLiteralAntlrContext>
					(makeNumLiteralCtx(num))
			},
			.signOperation{},
			.sqrtOperation{},
			.grouping{},
			.absoluteValueOperation{}
		};
	}


	static CmdCalculatorTestDoubles::StubOperandAntlrContext makeOperandNumLiteralCtx(const int num)
	{
		return CmdCalculatorTestDoubles::StubOperandAntlrContext
		{
			.isGroupingMultiplicationValue{ false },
			.nonGroupingMultiplicationOperand
			{
				std::make_optional<CmdCalculatorTestDoubles::StubNonGroupingMultiplicationAntlrContext>
				(
					makeNonGroupMultNumLiteralCtx(num)
				)
			},
			.groupingMultiplicationOperand{}
		};
	}


	static std::vector<CmdCalculatorTestDoubles::StubOperationPartPairAntlrContext> makeAdditionChainOpPartPairs(std::ranges::input_range auto nums)
		requires std::same_as<int, std::ranges::range_value_t<decltype(nums)>>
	{
		auto partPairsView
		{
			nums
			| std::views::transform
			(
				[](const int num)
				{
					return CmdCalculatorTestDoubles::StubOperationPartPairAntlrContext
					{
						.operatorLeadingTrivia{},
						.operatorValue
						{
							.binaryOperatorAntlrContextKind{ CmdCalculator::MathAst::EBinaryOperator::Addition },
							.token{ makeToken("+") }
						},
						.operatorTrailingTrivia{},
						.operandValue{ makeOperandNumLiteralCtx(num) }
					};
				}
			)
		};

		return std::vector<CmdCalculatorTestDoubles::StubOperationPartPairAntlrContext>
		{
			std::ranges::begin(partPairsView),
			std::ranges::end(partPairsView)
		};
	}


	static CmdCalculatorTestDoubles::StubExpressionAntlrContext makeNumExprCtx(const int num)
	{
		return CmdCalculatorTestDoubles::StubExpressionAntlrContext
		{
			.headOperand{ makeOperandNumLiteralCtx(num) },
			.operationPartPairs{}
		};
	}


	static CmdCalculatorTestDoubles::StubGroupingAntlrContext makeGroupNumLiteralCtx(const int num)
	{
		return CmdCalculatorTestDoubles::StubGroupingAntlrContext
		{
			.innerLeadingTrivia{},
			.innerExpression
			{
				std::make_shared<CmdCalculatorTestDoubles::StubExpressionAntlrContext>(makeNumExprCtx(num))
			},
			.innerTrailingTrivia{}
		};
	}


	static CmdCalculatorTestDoubles::StubGroupingTailMultiplicandAntlrContext makeGroupMultTailNumLiteralCtx(const std::string innerTrivia, const int num)
	{
		return CmdCalculatorTestDoubles::StubGroupingTailMultiplicandAntlrContext
		{
			.innerTrivia{ makeOptionalToken(innerTrivia) },
			.groupingValue{ makeGroupNumLiteralCtx(num) }
		};
	}


	static CmdCalculatorTestDoubles::StubGroupingTailMultiplicandAntlrContext makeGroupMultTailNumLiteralCtx(const int num)
	{
		return CmdCalculatorTestDoubles::StubGroupingTailMultiplicandAntlrContext
		{
			.innerTrivia{},
			.groupingValue{ makeGroupNumLiteralCtx(num) }
		};
	}


	static CmdCalculatorTestDoubles::StubExpressionAntlrContext makeAdditionChainExprCtx(std::ranges::input_range auto nums)
		requires std::same_as<int, std::ranges::range_value_t<decltype(nums)>>
	{
		assert(!std::ranges::empty(nums));

		return CmdCalculatorTestDoubles::StubExpressionAntlrContext
		{
			.headOperand{ makeOperandNumLiteralCtx(*std::ranges::begin(nums)) },
			.operationPartPairs{ makeAdditionChainOpPartPairs(nums | std::views::drop(1)) }
		};
	}
#pragma endregion


#pragma region Concept satisfaction
	
	TEST(AntlrContextToDynamicMathAstConverterTests, AntlrContextToDynamicMathAstConverter$satisfies$AntlrContextToMathAstConverter$concept)
	{
		static_assert
		(
			CmdCalculator::AntlrContextToMathAstConverter
			<
				CmdCalculator::AntlrContextToDynamicMathAstConverter
				<
					CmdCalculatorTestDoubles::StubFullExpressionAntlrContext<>,
					char,
					int,
					float
				>
			>
		);
	}

#pragma endregion


#pragma region getConvertedFullExpressionContext

	struct getConvertedFullExpressionContext_Params
	{
		CmdCalculatorTestDoubles::StubFullExpressionAntlrContext<> context;
		std::string expectedExpressionStringRepresentation;
		std::string expectedLeadingTrivia;
		std::string expectedTrailingTrivia;
		std::string expectedStringRepresentation;
	};

	class getConvertedFullExpressionContextTests :
		public testing::TestWithParam<getConvertedFullExpressionContext_Params>
	{};

	const getConvertedFullExpressionContext_Params getConvertedFullExpressionContext_ParamsValues[]
	{
		{
			.context
			{
				.leadingTrivia{},
				.expressionValue{ makeAdditionChainExprCtx(std::views::single(0)) },
				.trailingTrivia{}
			},
			.expectedExpressionStringRepresentation{ "0" },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "0" }
		},
		{
			.context
			{
				.leadingTrivia{ makeOptionalToken("") },
				.expressionValue{ makeAdditionChainExprCtx(std::views::single(0)) },
				.trailingTrivia{ makeOptionalToken("") },
			},
			.expectedExpressionStringRepresentation{ "0" },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "0" }
		},
		{
			.context
			{
				.leadingTrivia{ makeOptionalToken("  ") },
				.expressionValue{ makeAdditionChainExprCtx(std::views::single(0)) },
				.trailingTrivia{ makeOptionalToken("   ") },
			},
			.expectedExpressionStringRepresentation{ "0" },
			.expectedLeadingTrivia{ "  " },
			.expectedTrailingTrivia{ "   " },
			.expectedStringRepresentation{ "  0   " }
		},
		{
			.context
			{
				.leadingTrivia{},
				.expressionValue{ makeAdditionChainExprCtx(std::views::iota(0, 4)) },
				.trailingTrivia{}
			},
			.expectedExpressionStringRepresentation{ "0+1+2+3" },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "0+1+2+3" }
		},
		{
			.context
			{
				.leadingTrivia{ makeOptionalToken("  ") },
				.expressionValue{ makeAdditionChainExprCtx(std::views::iota(0, 4)) },
				.trailingTrivia{ makeOptionalToken("   ") }
			},
			.expectedExpressionStringRepresentation{ "0+1+2+3" },
			.expectedLeadingTrivia{ "  " },
			.expectedTrailingTrivia{ "   " },
			.expectedStringRepresentation{ "  0+1+2+3   " }
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		AntlrContextToDynamicMathAstConverterTests,
		getConvertedFullExpressionContextTests,
		testing::ValuesIn(getConvertedFullExpressionContext_ParamsValues)
	);

	TEST_P(getConvertedFullExpressionContextTests, getConvertedFullExpressionContext$returns$expected$value)
	{
		// Arrange
		const CmdCalculator::AntlrContextToDynamicMathAstConverter<decltype(GetParam().context), char, int, float>
			instance{}
		;
		const CmdCalculator::FullExpressionAntlrContext auto context{ GetParam().context };

		// Act
		const CmdCalculator::UniquePtr auto returnValue{ instance.getConvertedFullExpressionContext(context) };
		
		// Assert
		EXPECT_TRUE(returnValue);
		EXPECT_EQ(GetParam().expectedLeadingTrivia, returnValue->getLeadingTrivia());
		EXPECT_EQ(GetParam().expectedTrailingTrivia, returnValue->getTrailingTrivia());
		EXPECT_EQ(GetParam().expectedStringRepresentation, returnValue->getStringRepresentation());
	}

#pragma endregion


#pragma region getConvertedExpressionContext

	struct getConvertedExpressionContext_Params
	{
		CmdCalculatorTestDoubles::StubExpressionAntlrContext context;
		std::vector<std::string> expectedPartStringRepresentations;
		std::string expectedStringRepresentation;
	};

	class getConvertedExpressionContextTests :
		public testing::TestWithParam<getConvertedExpressionContext_Params>
	{};

	const getConvertedExpressionContext_Params getConvertedExpressionContext_ParamsValues[]
	{
		{
			.context
			{
				.headOperand{ makeOperandNumLiteralCtx(0) },
				.operationPartPairs{}
			},
			.expectedPartStringRepresentations{ "0" },
			.expectedStringRepresentation{ "0" }
		},
		{
			.context
			{
				.headOperand{ makeOperandNumLiteralCtx(5) },
				.operationPartPairs{}
			},
			.expectedPartStringRepresentations{ "5" },
			.expectedStringRepresentation{ "5" }
		},
		{
			.context
			{
				.headOperand{ makeOperandNumLiteralCtx(0) },
				.operationPartPairs{ makeAdditionChainOpPartPairs(std::views::single(1)) }
			},
			.expectedPartStringRepresentations{ "0", "+", "1" },
			.expectedStringRepresentation{ "0+1" }
		},
		{
			.context
			{
				.headOperand{ makeOperandNumLiteralCtx(0) },
				.operationPartPairs{ makeAdditionChainOpPartPairs(std::views::iota(1, 4)) }
			},
			.expectedPartStringRepresentations{ "0", "+", "1", "+", "2", "+", "3" },
			.expectedStringRepresentation{ "0+1+2+3" }
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		AntlrContextToDynamicMathAstConverterTests,
		getConvertedExpressionContextTests,
		testing::ValuesIn(getConvertedExpressionContext_ParamsValues)
	);

	TEST_P(getConvertedExpressionContextTests, getConvertedExpressionContext$returns$expected$value)
	{
		// Arrange
		const CmdCalculator::AntlrContextToDynamicMathAstConverter<CmdCalculatorTestDoubles::StubFullExpressionAntlrContext<>, char, int, float>
			instance{}
		;
		const CmdCalculator::ExpressionAntlrContext auto context{ GetParam().context };

		// Act
		const CmdCalculator::UniquePtr auto returnValue{ instance.getConvertedExpressionContext(context) };
		
		// Assert
		EXPECT_TRUE(returnValue);
		EXPECT_TRUE
		(
			std::ranges::equal
			(
				GetParam().expectedPartStringRepresentations,
				returnValue->getParts()
				| std::views::transform
				(
					[](const CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>& part)
					{ return part.getStringRepresentation(); }
				)
			)
		);
		EXPECT_EQ(GetParam().expectedStringRepresentation, returnValue->getStringRepresentation());
	}

#pragma endregion


#pragma region getConvertedOperandContext

	struct getConvertedOperandContext_Params
	{
		CmdCalculatorTestDoubles::StubOperandAntlrContext context;
		std::string expectedStringRepresentation;
	};

	class getConvertedOperandContextTests :
		public testing::TestWithParam<getConvertedOperandContext_Params>
	{};

	const getConvertedOperandContext_Params getConvertedOperandContext_ParamsValues[]
	{
		{
			.context{ makeOperandNumLiteralCtx(0) },
			.expectedStringRepresentation{ "0" }
		},
		{
			.context{ makeOperandNumLiteralCtx(5) },
			.expectedStringRepresentation{ "5" }
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		AntlrContextToDynamicMathAstConverterTests,
		getConvertedOperandContextTests,
		testing::ValuesIn(getConvertedOperandContext_ParamsValues)
	);

	TEST_P(getConvertedOperandContextTests, getConvertedOperandContext$returns$expected$value)
	{
		// Arrange
		const CmdCalculator::AntlrContextToDynamicMathAstConverter<CmdCalculatorTestDoubles::StubFullExpressionAntlrContext<>, char, int, float>
			instance{}
		;
		const CmdCalculator::OperandAntlrContext auto context{ GetParam().context };

		// Act
		const CmdCalculator::UniquePtr auto returnValue{ instance.getConvertedOperandContext(context) };
		
		// Assert
		EXPECT_TRUE(returnValue);
		EXPECT_EQ(GetParam().expectedStringRepresentation, returnValue->getStringRepresentation());
	}

#pragma endregion


#pragma region getConvertedOperationPartPairsContext

	struct getConvertedOperationPartPairsContext_Params
	{
		CmdCalculatorTestDoubles::StubOperationPartPairAntlrContext context;
		std::string expectedOperatorLeadingTrivia;
		std::string expectedOperatorValueStringRepresentation;
		std::string expectedOperatorTrailingTrivia;
		std::string expectedOperandValueStringRepresentation;
		std::string expectedStringRepresentation;
	};

	class getConvertedOperationPartPairsContextTests :
		public testing::TestWithParam<getConvertedOperationPartPairsContext_Params>
	{};

	const getConvertedOperationPartPairsContext_Params getConvertedOperationPartPairsContext_ParamsValues[]
	{
		{
			.context
			{
				.operatorLeadingTrivia{},
				.operatorValue
				{
					CmdCalculatorTestDoubles::StubBinaryOperatorAntlrContext
					{
						.binaryOperatorAntlrContextKind{ CmdCalculator::MathAst::EBinaryOperator::Addition },
						.token
						{
							CmdCalculatorTestDoubles::StubAntlrToken<std::string>
							{
								.text{ "+" },
								.startIndex{ 0 },
								.stopIndex{ 0 }
							}
						}
					}
				},
				.operatorTrailingTrivia{},
				.operandValue{ makeOperandNumLiteralCtx(0) }
			},
			.expectedStringRepresentation{ "+0" }
		},
		{
			.context
			{
				.operatorLeadingTrivia{},
				.operatorValue
				{
					CmdCalculatorTestDoubles::StubBinaryOperatorAntlrContext
					{
						.binaryOperatorAntlrContextKind{ CmdCalculator::MathAst::EBinaryOperator::Subtraction },
						.token
						{
							CmdCalculatorTestDoubles::StubAntlrToken<std::string>
							{
								.text{ "-" },
								.startIndex{ 0 },
								.stopIndex{ 0 }
							}
						}
					}
				},
				.operatorTrailingTrivia{},
				.operandValue{ makeOperandNumLiteralCtx(0) }
			},
			.expectedStringRepresentation{ "-0" }
		},
		{
			.context
			{
				.operatorLeadingTrivia{},
				.operatorValue
				{
					CmdCalculatorTestDoubles::StubBinaryOperatorAntlrContext
					{
						.binaryOperatorAntlrContextKind{ CmdCalculator::MathAst::EBinaryOperator::Multiplication },
						.token
						{
							CmdCalculatorTestDoubles::StubAntlrToken<std::string>
							{
								.text{ "*" },
								.startIndex{ 0 },
								.stopIndex{ 0 }
							}
						}
					}
				},
				.operatorTrailingTrivia{},
				.operandValue{ makeOperandNumLiteralCtx(0) }
			},
			.expectedStringRepresentation{ "*0" }
		},
		{
			.context
			{
				.operatorLeadingTrivia{},
				.operatorValue
				{
					CmdCalculatorTestDoubles::StubBinaryOperatorAntlrContext
					{
						.binaryOperatorAntlrContextKind{ CmdCalculator::MathAst::EBinaryOperator::Division },
						.token
						{
							CmdCalculatorTestDoubles::StubAntlrToken<std::string>
							{
								.text{ "/" },
								.startIndex{ 0 },
								.stopIndex{ 0 }
							}
						}
					}
				},
				.operatorTrailingTrivia{},
				.operandValue{ makeOperandNumLiteralCtx(0) }
			},
			.expectedStringRepresentation{ "/0" }
		},
		{
			.context
			{
				.operatorLeadingTrivia{},
				.operatorValue
				{
					CmdCalculatorTestDoubles::StubBinaryOperatorAntlrContext
					{
						.binaryOperatorAntlrContextKind{ CmdCalculator::MathAst::EBinaryOperator::Exponentiation },
						.token
						{
							CmdCalculatorTestDoubles::StubAntlrToken<std::string>
							{
								.text{ "^" },
								.startIndex{ 0 },
								.stopIndex{ 0 }
							}
						}
					}
				},
				.operatorTrailingTrivia{},
				.operandValue{ makeOperandNumLiteralCtx(0) }
			},
			.expectedStringRepresentation{ "^0" }
		},
		{
			.context
			{
				.operatorLeadingTrivia{},
				.operatorValue
				{
					CmdCalculatorTestDoubles::StubBinaryOperatorAntlrContext
					{
						.binaryOperatorAntlrContextKind{ CmdCalculator::MathAst::EBinaryOperator::NthRoot },
						.token
						{
							CmdCalculatorTestDoubles::StubAntlrToken<std::string>
							{
								.text{ "_" },
								.startIndex{ 0 },
								.stopIndex{ 0 }
							}
						}
					}
				},
				.operatorTrailingTrivia{},
				.operandValue{ makeOperandNumLiteralCtx(0) }
			},
			.expectedStringRepresentation{ "_0" }
		},
		{
			.context
			{
				.operatorLeadingTrivia{},
				.operatorValue
				{
					CmdCalculatorTestDoubles::StubBinaryOperatorAntlrContext
					{
						.binaryOperatorAntlrContextKind{ CmdCalculator::MathAst::EBinaryOperator::Modulo },
						.token
						{
							CmdCalculatorTestDoubles::StubAntlrToken<std::string>
							{
								.text{ "%" },
								.startIndex{ 0 },
								.stopIndex{ 0 }
							}
						}
					}
				},
				.operatorTrailingTrivia{},
				.operandValue{ makeOperandNumLiteralCtx(0) }
			},
			.expectedStringRepresentation{ "%0" }
		},
		{
			.context
			{
				.operatorLeadingTrivia{ makeOptionalToken("  ") },
				.operatorValue
				{
					CmdCalculatorTestDoubles::StubBinaryOperatorAntlrContext
					{
						.binaryOperatorAntlrContextKind{ CmdCalculator::MathAst::EBinaryOperator::Multiplication },
						.token
						{
							CmdCalculatorTestDoubles::StubAntlrToken<std::string>
							{
								.text{ "*" },
								.startIndex{ 0 },
								.stopIndex{ 0 }
							}
						}
					}
				},
				.operatorTrailingTrivia{ makeOptionalToken("   ") },
				.operandValue{ makeOperandNumLiteralCtx(5) }
			},
			.expectedStringRepresentation{ "  *   5" }
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		AntlrContextToDynamicMathAstConverterTests,
		getConvertedOperationPartPairsContextTests,
		testing::ValuesIn(getConvertedOperationPartPairsContext_ParamsValues)
	);

	TEST_P(getConvertedOperationPartPairsContextTests, getConvertedOperationPartPairsContext$returns$expected$value)
	{
		// Arrange
		const CmdCalculator::AntlrContextToDynamicMathAstConverter<CmdCalculatorTestDoubles::StubFullExpressionAntlrContext<>, char, int, float>
			instance{}
		;
		const CmdCalculator::OperationPartPairAntlrContext auto context{ GetParam().context };

		// Act
		const CmdCalculator::UniquePtr auto returnValue{ instance.getConvertedOperationPartPairContext(context) };
		
		// Assert
		EXPECT_TRUE(returnValue);
		EXPECT_EQ
		(
			GetParam().expectedStringRepresentation,
			returnValue->binaryOperator->getStringRepresentation()
			+ returnValue->operand->getStringRepresentation()
		);
	}

#pragma endregion


#pragma region getConvertedBinaryOperatorContext

	struct getConvertedBinaryOperatorContext_Params
	{
		std::shared_ptr<CmdCalculatorTestDoubles::StubAntlrToken<std::string>> leadingTrivia;
		CmdCalculatorTestDoubles::StubBinaryOperatorAntlrContext context;
		std::shared_ptr<CmdCalculatorTestDoubles::StubAntlrToken<std::string>> trailingTrivia;
		CmdCalculator::MathAst::EBinaryOperator expectedOperatorKind;
		std::string expectedLeadingTrivia;
		std::string expectedTrailingTrivia;
		std::string expectedStringRepresentation;
	};

	class getConvertedBinaryOperatorContextTests :
		public testing::TestWithParam<getConvertedBinaryOperatorContext_Params>
	{};

	const getConvertedBinaryOperatorContext_Params getConvertedBinaryOperatorContext_ParamsValues[]
	{
		{
			.leadingTrivia{},
			.context
			{
				.binaryOperatorAntlrContextKind{ CmdCalculator::MathAst::EBinaryOperator::Addition },
				.token
				{
					.text{ "+" },
					.startIndex{ 0 },
					.stopIndex{ 0 }
				},
			},
			.trailingTrivia{},
			.expectedOperatorKind{ CmdCalculator::MathAst::EBinaryOperator::Addition },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "+" }
		},
		{
			.leadingTrivia{},
			.context
			{
				.binaryOperatorAntlrContextKind{ CmdCalculator::MathAst::EBinaryOperator::Subtraction },
				.token
				{
					.text{ "-" },
					.startIndex{ 0 },
					.stopIndex{ 0 }
				},
			},
			.trailingTrivia{},
			.expectedOperatorKind{ CmdCalculator::MathAst::EBinaryOperator::Subtraction },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "-" }
		},
		{
			.leadingTrivia{},
			.context
			{
				.binaryOperatorAntlrContextKind{ CmdCalculator::MathAst::EBinaryOperator::Multiplication },
				.token
				{
					.text{ "*" },
					.startIndex{ 0 },
					.stopIndex{ 0 }
				},
			},
			.trailingTrivia{},
			.expectedOperatorKind{ CmdCalculator::MathAst::EBinaryOperator::Multiplication },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "*" }
		},
		{
			.leadingTrivia{},
			.context
			{
				.binaryOperatorAntlrContextKind{ CmdCalculator::MathAst::EBinaryOperator::Division },
				.token
				{
					.text{ "/" },
					.startIndex{ 0 },
					.stopIndex{ 0 }
				},
			},
			.trailingTrivia{},
			.expectedOperatorKind{ CmdCalculator::MathAst::EBinaryOperator::Division },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "/" }
		},
		{
			.leadingTrivia{},
			.context
			{
				.binaryOperatorAntlrContextKind{ CmdCalculator::MathAst::EBinaryOperator::Exponentiation },
				.token
				{
					.text{ "^" },
					.startIndex{ 0 },
					.stopIndex{ 0 }
				},
			},
			.trailingTrivia{},
			.expectedOperatorKind{ CmdCalculator::MathAst::EBinaryOperator::Exponentiation },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "^" }
		},
		{
			.leadingTrivia{},
			.context
			{
				.binaryOperatorAntlrContextKind{ CmdCalculator::MathAst::EBinaryOperator::NthRoot },
				.token
				{
					.text{ "_" },
					.startIndex{ 0 },
					.stopIndex{ 0 }
				},
			},
			.trailingTrivia{},
			.expectedOperatorKind{ CmdCalculator::MathAst::EBinaryOperator::NthRoot },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "_" }
		},
		{
			.leadingTrivia{},
			.context
			{
				.binaryOperatorAntlrContextKind{ CmdCalculator::MathAst::EBinaryOperator::Modulo },
				.token
				{
					.text{ "%" },
					.startIndex{ 0 },
					.stopIndex{ 0 }
				},
			},
			.trailingTrivia{},
			.expectedOperatorKind{ CmdCalculator::MathAst::EBinaryOperator::Modulo },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "%" }
		},
		{
			.leadingTrivia
			{
				std::make_shared<CmdCalculatorTestDoubles::StubAntlrToken<std::string>>(makeToken("  "))
			},
			.context
			{
				.binaryOperatorAntlrContextKind{ CmdCalculator::MathAst::EBinaryOperator::Multiplication },
				.token
				{
					.text{ "*" },
					.startIndex{ 0 },
					.stopIndex{ 0 }
				},
			},
			.trailingTrivia
			{
				std::make_shared<CmdCalculatorTestDoubles::StubAntlrToken<std::string>>(makeToken("   "))
			},
			.expectedOperatorKind{ CmdCalculator::MathAst::EBinaryOperator::Multiplication },
			.expectedLeadingTrivia{ "  " },
			.expectedTrailingTrivia{ "   " },
			.expectedStringRepresentation{ "  *   " }
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		AntlrContextToDynamicMathAstConverterTests,
		getConvertedBinaryOperatorContextTests,
		testing::ValuesIn(getConvertedBinaryOperatorContext_ParamsValues)
	);

	TEST_P(getConvertedBinaryOperatorContextTests, getConvertedBinaryOperatorContext$returns$expected$value)
	{
		// Arrange
		const CmdCalculator::AntlrContextToDynamicMathAstConverter<CmdCalculatorTestDoubles::StubFullExpressionAntlrContext<>, char, int, float>
			instance{}
		;
		const CmdCalculator::AntlrToken auto* leadingTrivia{ GetParam().leadingTrivia.get() };
		const CmdCalculator::BinaryOperatorAntlrContext auto context{ GetParam().context };
		const CmdCalculator::AntlrToken auto* trailingTrivia{ GetParam().trailingTrivia.get() };

		// Act
		const CmdCalculator::UniquePtr auto returnValue
		{
			instance.getConvertedBinaryOperatorContext(leadingTrivia, context, trailingTrivia)
		};
		
		// Assert
		EXPECT_TRUE(returnValue);
		EXPECT_EQ(GetParam().expectedOperatorKind, returnValue->getOperatorKind());
		EXPECT_EQ(GetParam().expectedLeadingTrivia, returnValue->getLeadingTrivia());
		EXPECT_EQ(GetParam().expectedTrailingTrivia, returnValue->getTrailingTrivia());
		EXPECT_EQ(GetParam().expectedStringRepresentation, returnValue->getStringRepresentation());
	}

#pragma endregion


#pragma region getConvertedNumberLiteralContext

	struct getConvertedNumberLiteralContext_Params
	{
		CmdCalculatorTestDoubles::StubNumberLiteralAntlrContext context;
		int expectedWholePart;
		int expectedFractionalPart;
		bool expectWholePartVisible;
		bool expectDecimalPointVisible;
		bool expectFractionalPartVisible;
		std::string expectedLeadingTrivia;
		std::string expectedTrailingTrivia;
		std::string expectedStringRepresentation;
	};

	class getConvertedNumberLiteralContextTests :
		public testing::TestWithParam<getConvertedNumberLiteralContext_Params>
	{};

	const getConvertedNumberLiteralContext_Params getConvertedNumberLiteralContext_ParamsValues[]
	{
		{
			.context
			{
				.numberLiteralAntlrContextKind{ CmdCalculator::ENumberLiteralAntlrContextKind::Wholeful },
				.wholefulNumberLiteral
				{
					std::make_optional<CmdCalculatorTestDoubles::StubWholefulNumberLiteralAntlrContext>
					(
						CmdCalculatorTestDoubles::StubWholefulNumberLiteralAntlrContext
						{
							.wholePart{ makeNumToken(0) },
							.decimalPoint{},
							.fractionalPart{}
						}
					)
				},
				.wholelessNumberLiteral{}
			},
			.expectedWholePart{ 0 },
			.expectedFractionalPart{ 0 },
			.expectWholePartVisible{ true },
			.expectDecimalPointVisible{ false },
			.expectFractionalPartVisible{ false },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "0" }
		},
		{
			.context
			{
				.numberLiteralAntlrContextKind{ CmdCalculator::ENumberLiteralAntlrContextKind::Wholeful },
				.wholefulNumberLiteral
				{
					std::make_optional<CmdCalculatorTestDoubles::StubWholefulNumberLiteralAntlrContext>
					(
						CmdCalculatorTestDoubles::StubWholefulNumberLiteralAntlrContext
						{
							.wholePart{ makeNumToken(123) },
							.decimalPoint{},
							.fractionalPart{}
						}
					)
				},
				.wholelessNumberLiteral{}
			},
			.expectedWholePart{ 123 },
			.expectedFractionalPart{ 0 },
			.expectWholePartVisible{ true },
			.expectDecimalPointVisible{ false },
			.expectFractionalPartVisible{ false },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "123" }
		},
		{
			.context
			{
				.numberLiteralAntlrContextKind{ CmdCalculator::ENumberLiteralAntlrContextKind::Wholeful },
				.wholefulNumberLiteral
				{
					std::make_optional<CmdCalculatorTestDoubles::StubWholefulNumberLiteralAntlrContext>
					(
						CmdCalculatorTestDoubles::StubWholefulNumberLiteralAntlrContext
						{
							.wholePart{ makeNumToken(123) },
							.decimalPoint{ makeOptionalToken(".") },
							.fractionalPart{}
						}
					)
				},
				.wholelessNumberLiteral{}
			},
			.expectedWholePart{ 123 },
			.expectedFractionalPart{ 0 },
			.expectWholePartVisible{ true },
			.expectDecimalPointVisible{ true },
			.expectFractionalPartVisible{ false },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "123." }
		},
		{
			.context
			{
				.numberLiteralAntlrContextKind{ CmdCalculator::ENumberLiteralAntlrContextKind::Wholeful },
				.wholefulNumberLiteral
				{
					std::make_optional<CmdCalculatorTestDoubles::StubWholefulNumberLiteralAntlrContext>
					(
						CmdCalculatorTestDoubles::StubWholefulNumberLiteralAntlrContext
						{
							.wholePart{ makeNumToken(123) },
							.decimalPoint{ makeOptionalToken(".") },
							.fractionalPart{ makeOptionalNumToken(456) }
						}
					)
				},
				.wholelessNumberLiteral{}
			},
			.expectedWholePart{ 123 },
			.expectedFractionalPart{ 456 },
			.expectWholePartVisible{ true },
			.expectDecimalPointVisible{ true },
			.expectFractionalPartVisible{ true },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "123.456" }
		},
		{
			.context
			{
				.numberLiteralAntlrContextKind{ CmdCalculator::ENumberLiteralAntlrContextKind::Wholeless },
				.wholefulNumberLiteral{},
				.wholelessNumberLiteral
				{
					std::make_optional<CmdCalculatorTestDoubles::StubWholelessNumberLiteralAntlrContext>
					(
						CmdCalculatorTestDoubles::StubWholelessNumberLiteralAntlrContext
						{
							.decimalPoint{ makeToken(".") },
							.fractionalPart{ makeNumToken(0) }
						}
					)
				}
			},
			.expectedWholePart{ 0 },
			.expectedFractionalPart{ 0 },
			.expectWholePartVisible{ false },
			.expectDecimalPointVisible{ true },
			.expectFractionalPartVisible{ true },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ ".0" }
		},
		{
			.context
			{
				.numberLiteralAntlrContextKind{ CmdCalculator::ENumberLiteralAntlrContextKind::Wholeless },
				.wholefulNumberLiteral{},
				.wholelessNumberLiteral
				{
					std::make_optional<CmdCalculatorTestDoubles::StubWholelessNumberLiteralAntlrContext>
					(
						CmdCalculatorTestDoubles::StubWholelessNumberLiteralAntlrContext
						{
							.decimalPoint{ makeToken(".") },
							.fractionalPart{ makeNumToken(123) }
						}
					)
				}
			},
			.expectedWholePart{ 0 },
			.expectedFractionalPart{ 123 },
			.expectWholePartVisible{ false },
			.expectDecimalPointVisible{ true },
			.expectFractionalPartVisible{ true },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ ".123" }
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		AntlrContextToDynamicMathAstConverterTests,
		getConvertedNumberLiteralContextTests,
		testing::ValuesIn(getConvertedNumberLiteralContext_ParamsValues)
	);

	TEST_P(getConvertedNumberLiteralContextTests, getConvertedNumberLiteralContext$returns$expected$value)
	{
		// Arrange
		const CmdCalculator::AntlrContextToDynamicMathAstConverter<CmdCalculatorTestDoubles::StubFullExpressionAntlrContext<>, char, int, float>
			instance{}
		;
		const CmdCalculator::NumberLiteralAntlrContext auto context{ GetParam().context };

		// Act
		const CmdCalculator::UniquePtr auto returnValue{ instance.getConvertedNumberLiteralContext(context) };
		
		// Assert
		EXPECT_TRUE(returnValue);
		EXPECT_EQ(GetParam().expectedWholePart, returnValue->getWholePart());
		EXPECT_EQ(GetParam().expectedFractionalPart, returnValue->getFractionalPart());
		EXPECT_EQ(GetParam().expectWholePartVisible, returnValue->isWholePartVisible());
		EXPECT_EQ(GetParam().expectDecimalPointVisible, returnValue->isDecimalPointVisible());
		EXPECT_EQ(GetParam().expectFractionalPartVisible, returnValue->isFractionalPartVisible());
		EXPECT_EQ(GetParam().expectedLeadingTrivia, returnValue->getLeadingTrivia());
		EXPECT_EQ(GetParam().expectedTrailingTrivia, returnValue->getTrailingTrivia());
		EXPECT_EQ(GetParam().expectedStringRepresentation, returnValue->getStringRepresentation());
	}

#pragma endregion


#pragma region getConvertedSignOperationContext

	struct getConvertedSignOperationContext_Params
	{
		CmdCalculatorTestDoubles::StubSignOperationAntlrContext context;
		bool expectIsPositive;
		std::string expectedOperandStringRepresentation;
		std::string expectedLeadingTrivia;
		std::string expectedInnerTrivia;
		std::string expectedTrailingTrivia;
		std::string expectedStringRepresentation;
	};

	class getConvertedSignOperationContextTests :
		public testing::TestWithParam<getConvertedSignOperationContext_Params>
	{};

	const getConvertedSignOperationContext_Params getConvertedSignOperationContext_ParamsValues[]
	{
		{
			.context
			{
				.signOperator
				{
					CmdCalculatorTestDoubles::StubSignOperatorAntlrContext
					{
						.signOperatorAntlrContextKind{ CmdCalculator::ESignOperatorAntlrContextKind::Negative },
						.token{ makeToken("-") }
					}
				},
				.innerTrivia{},
				.operandValue
				{
					std::make_shared<CmdCalculatorTestDoubles::StubOperandAntlrContext>(makeOperandNumLiteralCtx(5))
				}
			},
			.expectIsPositive{ false },
			.expectedOperandStringRepresentation{ "5" },
			.expectedLeadingTrivia{ "" },
			.expectedInnerTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "-5" }
		},
		{
			.context
			{
				.signOperator
				{
					CmdCalculatorTestDoubles::StubSignOperatorAntlrContext
					{
						.signOperatorAntlrContextKind{ CmdCalculator::ESignOperatorAntlrContextKind::Negative },
						.token{ makeToken("-") }
					}
				},
				.innerTrivia{ makeOptionalToken("  ") },
				.operandValue
				{
					std::make_shared<CmdCalculatorTestDoubles::StubOperandAntlrContext>(makeOperandNumLiteralCtx(5))
				}
			},
			.expectIsPositive{ false },
			.expectedOperandStringRepresentation{ "5" },
			.expectedLeadingTrivia{ "" },
			.expectedInnerTrivia{ "  " },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "-  5" }
		},
		{
			.context
			{
				.signOperator
				{
					CmdCalculatorTestDoubles::StubSignOperatorAntlrContext
					{
						.signOperatorAntlrContextKind{ CmdCalculator::ESignOperatorAntlrContextKind::Positive },
						.token{ makeToken("+") }
					}
				},
				.innerTrivia{},
				.operandValue
				{
					std::make_shared<CmdCalculatorTestDoubles::StubOperandAntlrContext>(makeOperandNumLiteralCtx(5))
				}
			},
			.expectIsPositive{ true },
			.expectedOperandStringRepresentation{ "5" },
			.expectedLeadingTrivia{ "" },
			.expectedInnerTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "+5" }
		},
		{
			.context
			{
				.signOperator
				{
					CmdCalculatorTestDoubles::StubSignOperatorAntlrContext
					{
						.signOperatorAntlrContextKind{ CmdCalculator::ESignOperatorAntlrContextKind::Positive },
						.token{ makeToken("+") }
					}
				},
				.innerTrivia{ makeOptionalToken("  ") },
				.operandValue
				{
					std::make_shared<CmdCalculatorTestDoubles::StubOperandAntlrContext>(makeOperandNumLiteralCtx(5))
				}
			},
			.expectIsPositive{ true },
			.expectedOperandStringRepresentation{ "5" },
			.expectedLeadingTrivia{ "" },
			.expectedInnerTrivia{ "  " },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "+  5" }
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		AntlrContextToDynamicMathAstConverterTests,
		getConvertedSignOperationContextTests,
		testing::ValuesIn(getConvertedSignOperationContext_ParamsValues)
	);

	TEST_P(getConvertedSignOperationContextTests, getConvertedSignOperationContext$returns$expected$value)
	{
		// Arrange
		const CmdCalculator::AntlrContextToDynamicMathAstConverter<CmdCalculatorTestDoubles::StubFullExpressionAntlrContext<>, char, int, float>
			instance{}
		;
		const CmdCalculator::SignOperationAntlrContext auto context{ GetParam().context };

		// Act
		const CmdCalculator::UniquePtr auto returnValue{ instance.getConvertedSignOperationContext(context) };
		
		// Assert
		EXPECT_TRUE(returnValue);
		EXPECT_EQ(GetParam().expectIsPositive, returnValue->isPositive());
		EXPECT_EQ(GetParam().expectedOperandStringRepresentation, returnValue->getOperand()->getStringRepresentation());
		EXPECT_EQ(GetParam().expectedLeadingTrivia, returnValue->getLeadingTrivia());
		EXPECT_EQ(GetParam().expectedInnerTrivia, returnValue->getInnerTrivia());
		EXPECT_EQ(GetParam().expectedTrailingTrivia, returnValue->getTrailingTrivia());
		EXPECT_EQ(GetParam().expectedStringRepresentation, returnValue->getStringRepresentation());
	}

#pragma endregion


#pragma region getConvertedSqrtOperationContext

	struct getConvertedSqrtOperationContext_Params
	{
		CmdCalculatorTestDoubles::StubSqrtOperationAntlrContext context;
		std::string expectedOperandStringRepresentation;
		std::string expectedLeadingTrivia;
		std::string expectedInnerTrivia;
		std::string expectedTrailingTrivia;
		std::string expectedStringRepresentation;
	};

	class getConvertedSqrtOperationContextTests :
		public testing::TestWithParam<getConvertedSqrtOperationContext_Params>
	{};

	const getConvertedSqrtOperationContext_Params getConvertedSqrtOperationContext_ParamsValues[]
	{
		{
			.context
			{
				.innerTrivia{},
				.operandValue
				{
					std::make_shared<CmdCalculatorTestDoubles::StubOperandAntlrContext>(makeOperandNumLiteralCtx(5))
				}
			},
			.expectedOperandStringRepresentation{ "5" },
			.expectedLeadingTrivia{ "" },
			.expectedInnerTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "sqrt5" }
		},
		{
			.context
			{
				.innerTrivia{ makeOptionalToken("  ")},
				.operandValue
				{
					std::make_shared<CmdCalculatorTestDoubles::StubOperandAntlrContext>(makeOperandNumLiteralCtx(5))
				}
			},
			.expectedOperandStringRepresentation{ "5" },
			.expectedLeadingTrivia{ "" },
			.expectedInnerTrivia{ "  " },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "sqrt  5" }
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		AntlrContextToDynamicMathAstConverterTests,
		getConvertedSqrtOperationContextTests,
		testing::ValuesIn(getConvertedSqrtOperationContext_ParamsValues)
	);

	TEST_P(getConvertedSqrtOperationContextTests, getConvertedSqrtOperationContext$returns$expected$value)
	{
		// Arrange
		const CmdCalculator::AntlrContextToDynamicMathAstConverter<CmdCalculatorTestDoubles::StubFullExpressionAntlrContext<>, char, int, float>
			instance{}
		;
		const CmdCalculator::SqrtOperationAntlrContext auto context{ GetParam().context };

		// Act
		const CmdCalculator::UniquePtr auto returnValue{ instance.getConvertedSqrtOperationContext(context) };
		
		// Assert
		EXPECT_TRUE(returnValue);
		EXPECT_EQ(GetParam().expectedOperandStringRepresentation, returnValue->getOperand()->getStringRepresentation());
		EXPECT_EQ(GetParam().expectedLeadingTrivia, returnValue->getLeadingTrivia());
		EXPECT_EQ(GetParam().expectedInnerTrivia, returnValue->getInnerTrivia());
		EXPECT_EQ(GetParam().expectedTrailingTrivia, returnValue->getTrailingTrivia());
		EXPECT_EQ(GetParam().expectedStringRepresentation, returnValue->getStringRepresentation());
	}

#pragma endregion


#pragma region getConvertedGroupingContext

	struct getConvertedGroupingContext_Params
	{
		CmdCalculatorTestDoubles::StubGroupingAntlrContext context;
		std::string expectedContainedExpressionStringRepresentation;
		std::string expectedLeadingTrivia;
		std::string expectedTrailingTrivia;
		std::string expectedStringRepresentation;
	};

	class getConvertedGroupingContextTests :
		public testing::TestWithParam<getConvertedGroupingContext_Params>
	{};

	const getConvertedGroupingContext_Params getConvertedGroupingContext_ParamsValues[]
	{
		{
			.context
			{
				.innerLeadingTrivia{},
				.innerExpression
				{
					std::make_shared<CmdCalculatorTestDoubles::StubExpressionAntlrContext>(makeNumExprCtx(5))
				},
				.innerTrailingTrivia{}
			},
			.expectedContainedExpressionStringRepresentation{ "5" },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "(5)" }
		},
		{
			.context
			{
				.innerLeadingTrivia{ makeOptionalToken("  ")},
				.innerExpression
				{
					std::make_shared<CmdCalculatorTestDoubles::StubExpressionAntlrContext>(makeNumExprCtx(5))
				},
				.innerTrailingTrivia{ makeOptionalToken("   ")}
			},
			.expectedContainedExpressionStringRepresentation{ "  5   " },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "(  5   )" }
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		AntlrContextToDynamicMathAstConverterTests,
		getConvertedGroupingContextTests,
		testing::ValuesIn(getConvertedGroupingContext_ParamsValues)
	);

	TEST_P(getConvertedGroupingContextTests, getConvertedGroupingContext$returns$expected$value)
	{
		// Arrange
		const CmdCalculator::AntlrContextToDynamicMathAstConverter<CmdCalculatorTestDoubles::StubFullExpressionAntlrContext<>, char, int, float>
			instance{}
		;
		const CmdCalculator::GroupingAntlrContext auto context{ GetParam().context };

		// Act
		const CmdCalculator::UniquePtr auto returnValue{ instance.getConvertedGroupingContext(context) };
		
		// Assert
		EXPECT_TRUE(returnValue);
		EXPECT_EQ(GetParam().expectedContainedExpressionStringRepresentation, returnValue->getContainedExpression()->getStringRepresentation());
		EXPECT_EQ(GetParam().expectedLeadingTrivia, returnValue->getLeadingTrivia());
		EXPECT_EQ(GetParam().expectedTrailingTrivia, returnValue->getTrailingTrivia());
		EXPECT_EQ(GetParam().expectedStringRepresentation, returnValue->getStringRepresentation());
	}

#pragma endregion


#pragma region getConvertedGroupingMultiplicationContext

	struct getConvertedGroupingMultiplicationContext_Params
	{
		CmdCalculatorTestDoubles::StubGroupingMultiplicationAntlrContext context;
		std::string expectedHeadMultiplicandStringRepresentation;
		std::vector<std::string> expectedTailMultiplicandStringRepresentations;
		std::string expectedLeadingTrivia;
		std::string expectedTrailingTrivia;
		std::string expectedStringRepresentation;
	};

	class getConvertedGroupingMultiplicationContextTests :
		public testing::TestWithParam<getConvertedGroupingMultiplicationContext_Params>
	{};

	const getConvertedGroupingMultiplicationContext_Params getConvertedGroupingMultiplicationContext_ParamsValues[]
	{
		{
			.context
			{
				.headMultiplicand{ makeNonGroupMultNumLiteralCtx(5) },
				.tailMultiplicands{}
			},
			.expectedHeadMultiplicandStringRepresentation{ "5" },
			.expectedTailMultiplicandStringRepresentations{},
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "5" }
		},
		{
			.context
			{
				.headMultiplicand{ makeNonGroupMultNumLiteralCtx(0) },
				.tailMultiplicands
				{
					makeGroupMultTailNumLiteralCtx(1)
				}
			},
			.expectedHeadMultiplicandStringRepresentation{ "0" },
			.expectedTailMultiplicandStringRepresentations{ "(1)" },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "0(1)" }
		},
		{
			.context
			{
				.headMultiplicand{ makeNonGroupMultNumLiteralCtx(0) },
				.tailMultiplicands
				{
					makeGroupMultTailNumLiteralCtx("  ", 1)
				}
			},
			.expectedHeadMultiplicandStringRepresentation{ "0" },
			.expectedTailMultiplicandStringRepresentations{ "  (1)" },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "0  (1)" }
		},
		{
			.context
			{
				.headMultiplicand{ makeNonGroupMultNumLiteralCtx(0) },
				.tailMultiplicands
				{
					makeGroupMultTailNumLiteralCtx(1),
					makeGroupMultTailNumLiteralCtx(2),
					makeGroupMultTailNumLiteralCtx(3)
				}
			},
			.expectedHeadMultiplicandStringRepresentation{ "0" },
			.expectedTailMultiplicandStringRepresentations{ "(1)", "(2)", "(3)" },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "0(1)(2)(3)" }
		},
		{
			.context
			{
				.headMultiplicand{ makeNonGroupMultNumLiteralCtx(0) },
				.tailMultiplicands
				{
					makeGroupMultTailNumLiteralCtx("   ", 1),
					makeGroupMultTailNumLiteralCtx(" ", 2),
					makeGroupMultTailNumLiteralCtx("  ", 3)
				}
			},
			.expectedHeadMultiplicandStringRepresentation{ "0" },
			.expectedTailMultiplicandStringRepresentations{ "   (1)", " (2)", "  (3)" },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "0   (1) (2)  (3)" }
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		AntlrContextToDynamicMathAstConverterTests,
		getConvertedGroupingMultiplicationContextTests,
		testing::ValuesIn(getConvertedGroupingMultiplicationContext_ParamsValues)
	);

	TEST_P(getConvertedGroupingMultiplicationContextTests, getConvertedGroupingMultiplicationContext$returns$expected$value)
	{
		// Arrange
		const CmdCalculator::AntlrContextToDynamicMathAstConverter<CmdCalculatorTestDoubles::StubFullExpressionAntlrContext<>, char, int, float>
			instance{}
		;
		const CmdCalculator::GroupingMultiplicationAntlrContext auto context{ GetParam().context };

		// Act
		const CmdCalculator::UniquePtr auto returnValue{ instance.getConvertedGroupingMultiplicationContext(context) };
		
		// Assert
		EXPECT_TRUE(returnValue);
		EXPECT_EQ(GetParam().expectedHeadMultiplicandStringRepresentation, returnValue->getHeadMultiplicand()->getStringRepresentation());
		EXPECT_TRUE
		(
			std::ranges::equal
			(
				GetParam().expectedTailMultiplicandStringRepresentations,
				returnValue->getTailMultiplicands()
				| std::views::transform
				(
					[](const auto* tailMultiplicand)
					{ return tailMultiplicand->getStringRepresentation(); }
				)
			)
		);
		EXPECT_EQ(GetParam().expectedLeadingTrivia, returnValue->getLeadingTrivia());
		EXPECT_EQ(GetParam().expectedTrailingTrivia, returnValue->getTrailingTrivia());
		EXPECT_EQ(GetParam().expectedStringRepresentation, returnValue->getStringRepresentation());
	}

#pragma endregion


#pragma region getConvertedAbsoluteValueOperationContext

	struct getConvertedAbsoluteValueOperationContext_Params
	{
		CmdCalculatorTestDoubles::StubAbsoluteValueOperationAntlrContext context;
		std::string expectedContainedExpressionStringRepresentation;
		std::string expectedLeadingTrivia;
		std::string expectedTrailingTrivia;
		std::string expectedStringRepresentation;
	};

	class getConvertedAbsoluteValueOperationContextTests :
		public testing::TestWithParam<getConvertedAbsoluteValueOperationContext_Params>
	{};

	const getConvertedAbsoluteValueOperationContext_Params getConvertedAbsoluteValueOperationContext_ParamsValues[]
	{
		{
			.context
			{
				.innerLeadingTrivia{},
				.innerExpression
				{
					std::make_shared<CmdCalculatorTestDoubles::StubExpressionAntlrContext>(makeNumExprCtx(5))
				},
				.innerTrailingTrivia{}
			},
			.expectedContainedExpressionStringRepresentation{ "5" },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "|5|" }
		},
		{
			.context
			{
				.innerLeadingTrivia{ makeOptionalToken("  ")},
				.innerExpression
				{
					std::make_shared<CmdCalculatorTestDoubles::StubExpressionAntlrContext>(makeNumExprCtx(5))
				},
				.innerTrailingTrivia{ makeOptionalToken("   ")}
			},
			.expectedContainedExpressionStringRepresentation{ "  5   " },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "|  5   |" }
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		AntlrContextToDynamicMathAstConverterTests,
		getConvertedAbsoluteValueOperationContextTests,
		testing::ValuesIn(getConvertedAbsoluteValueOperationContext_ParamsValues)
	);

	TEST_P(getConvertedAbsoluteValueOperationContextTests, getConvertedAbsoluteValueOperationContext$returns$expected$value)
	{
		// Arrange
		const CmdCalculator::AntlrContextToDynamicMathAstConverter<CmdCalculatorTestDoubles::StubFullExpressionAntlrContext<>, char, int, float>
			instance{}
		;
		const CmdCalculator::AbsoluteValueOperationAntlrContext auto context{ GetParam().context };

		// Act
		const CmdCalculator::UniquePtr auto returnValue{ instance.getConvertedAbsoluteValueOperationContext(context) };
		
		// Assert
		EXPECT_TRUE(returnValue);
		EXPECT_EQ(GetParam().expectedContainedExpressionStringRepresentation, returnValue->getContainedExpression()->getStringRepresentation());
		EXPECT_EQ(GetParam().expectedLeadingTrivia, returnValue->getLeadingTrivia());
		EXPECT_EQ(GetParam().expectedTrailingTrivia, returnValue->getTrailingTrivia());
		EXPECT_EQ(GetParam().expectedStringRepresentation, returnValue->getStringRepresentation());
	}

#pragma endregion
}