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
		std::vector<std::string> expectedPartStringRepresentations;
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
			.expectedPartStringRepresentations{ "0" },
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
			.expectedPartStringRepresentations{ "0" },
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
			.expectedPartStringRepresentations{ "0" },
			.expectedLeadingTrivia{ "  " },
			.expectedTrailingTrivia{ "   " },
			.expectedStringRepresentation{ "  0   " }
		},
		{
			.context
			{
				.leadingTrivia{},
				.expressionValue{ makeAdditionChainExprCtx(std::views::iota(0, 3)) },
				.trailingTrivia{}
			},
			.expectedPartStringRepresentations{ "0", "1", "2" },
			.expectedLeadingTrivia{ "" },
			.expectedTrailingTrivia{ "" },
			.expectedStringRepresentation{ "012" }
		},
		{
			.context
			{
				.leadingTrivia{},
				.expressionValue{ makeAdditionChainExprCtx(std::views::iota(0, 3)) },
				.trailingTrivia{}
			},
			.expectedPartStringRepresentations{ "0", "1", "2" },
			.expectedLeadingTrivia{ "  " },
			.expectedTrailingTrivia{ "   " },
			.expectedStringRepresentation{ "  012   " }
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
		EXPECT_EQ(GetParam().expectedLeadingTrivia, returnValue->getLeadingTrivia());
		EXPECT_EQ(GetParam().expectedTrailingTrivia, returnValue->getTrailingTrivia());
		EXPECT_EQ(GetParam().expectedStringRepresentation, returnValue->getStringRepresentation());
	}

#pragma endregion
}