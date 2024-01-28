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


	static CmdCalculatorTestDoubles::StubOperandAntlrContext makeOperandNumLiteralCtx(const int num)
	{
		return CmdCalculatorTestDoubles::StubOperandAntlrContext
		{
			.isGroupingMultiplicationValue{ false },
			.nonGroupingMultiplicationOperand
			{
				std::make_optional<CmdCalculatorTestDoubles::StubNonGroupingMultiplicationAntlrContext>
				(
					CmdCalculatorTestDoubles::StubNonGroupingMultiplicationAntlrContext
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
					}
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
							.binaryOperatorAntlrContextKind{ CmdCalculator::EBinaryOperatorAntlrContextKind::Addition },
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
					int
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
				.leadingTrivia{},
				.expressionValue{ makeAdditionChainExprCtx(std::views::iota(0, 4)) },
				.trailingTrivia{}
			},
			.expectedExpressionStringRepresentation{ "0+1+2+3" },
			.expectedLeadingTrivia{ "  " },
			.expectedTrailingTrivia{ "   " },
			.expectedStringRepresentation{ "  0+1+2+3   " }
		}
	};

	TEST_P(getConvertedFullExpressionContextTests, getConvertedFullExpressionContext$returns$expected$value)
	{
		// Arrange
		const CmdCalculator::AntlrContextToDynamicMathAstConverter<decltype(GetParam().context), char, int>
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

	TEST_P(getConvertedExpressionContextTests, getConvertedExpressionContext$returns$expected$value)
	{
		// Arrange
		const CmdCalculator::AntlrContextToDynamicMathAstConverter<CmdCalculatorTestDoubles::StubFullExpressionAntlrContext<>, char, int>
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
					[](const auto* part)
					{ return part->getStringRepresentation(); }
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

	TEST_P(getConvertedOperandContextTests, getConvertedOperandContext$returns$expected$value)
	{
		// Arrange
		const CmdCalculator::AntlrContextToDynamicMathAstConverter<CmdCalculatorTestDoubles::StubFullExpressionAntlrContext<>, char, int>
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
						.binaryOperatorAntlrContextKind{ CmdCalculator::EBinaryOperatorAntlrContextKind::Addition },
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
						.binaryOperatorAntlrContextKind{ CmdCalculator::EBinaryOperatorAntlrContextKind::Subtraction },
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
						.binaryOperatorAntlrContextKind{ CmdCalculator::EBinaryOperatorAntlrContextKind::Multiplication },
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
						.binaryOperatorAntlrContextKind{ CmdCalculator::EBinaryOperatorAntlrContextKind::Division },
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
						.binaryOperatorAntlrContextKind{ CmdCalculator::EBinaryOperatorAntlrContextKind::Exponentiation },
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
						.binaryOperatorAntlrContextKind{ CmdCalculator::EBinaryOperatorAntlrContextKind::NthRoot },
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
						.binaryOperatorAntlrContextKind{ CmdCalculator::EBinaryOperatorAntlrContextKind::Modulo },
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
						.binaryOperatorAntlrContextKind{ CmdCalculator::EBinaryOperatorAntlrContextKind::Multiplication },
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

	TEST_P(getConvertedOperationPartPairsContextTests, getConvertedOperationPartPairsContext$returns$expected$value)
	{
		// Arrange
		const CmdCalculator::AntlrContextToDynamicMathAstConverter<CmdCalculatorTestDoubles::StubFullExpressionAntlrContext<>, char, int>
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
		std::unique_ptr<CmdCalculatorTestDoubles::StubAntlrToken<std::string>> leadingTrivia;
		CmdCalculatorTestDoubles::StubBinaryOperatorAntlrContext context;
		std::unique_ptr<CmdCalculatorTestDoubles::StubAntlrToken<std::string>> trailingTrivia;
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
				.binaryOperatorAntlrContextKind{ CmdCalculator::EBinaryOperatorAntlrContextKind::Addition },
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
				.binaryOperatorAntlrContextKind{ CmdCalculator::EBinaryOperatorAntlrContextKind::Subtraction },
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
				.binaryOperatorAntlrContextKind{ CmdCalculator::EBinaryOperatorAntlrContextKind::Multiplication },
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
				.binaryOperatorAntlrContextKind{ CmdCalculator::EBinaryOperatorAntlrContextKind::Division },
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
				.binaryOperatorAntlrContextKind{ CmdCalculator::EBinaryOperatorAntlrContextKind::Exponentiation },
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
				.binaryOperatorAntlrContextKind{ CmdCalculator::EBinaryOperatorAntlrContextKind::NthRoot },
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
				.binaryOperatorAntlrContextKind{ CmdCalculator::EBinaryOperatorAntlrContextKind::Modulo },
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
				std::make_unique<CmdCalculatorTestDoubles::StubAntlrToken<std::string>>(makeOptionalToken("  "))
			},
			.context
			{
				.binaryOperatorAntlrContextKind{ CmdCalculator::EBinaryOperatorAntlrContextKind::Multiplication },
				.token
				{
					.text{ "*" },
					.startIndex{ 0 },
					.stopIndex{ 0 }
				},
			},
			.trailingTrivia
			{
				std::make_unique<CmdCalculatorTestDoubles::StubAntlrToken<std::string>>(makeOptionalToken("   "))
			},
			.expectedOperatorKind{ CmdCalculator::MathAst::EBinaryOperator::Modulo },
			.expectedLeadingTrivia{ "  " },
			.expectedTrailingTrivia{ "   " },
			.expectedStringRepresentation{ "  %   " }
		}
	};

	TEST_P(getConvertedBinaryOperatorContextTests, getConvertedBinaryOperatorContext$returns$expected$value)
	{
		// Arrange
		const CmdCalculator::AntlrContextToDynamicMathAstConverter<CmdCalculatorTestDoubles::StubFullExpressionAntlrContext<>, char, int>
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
}