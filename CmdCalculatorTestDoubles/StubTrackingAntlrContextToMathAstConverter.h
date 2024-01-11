#pragma once

#include <concepts>
#include <memory>
#include <utility>
#include <ranges>
#include <span>

#include "../CmdCalculator/AntlrContextToMathAstConverter.h"
#include "../CmdCalculator/DynamicExpressionPartNode.h"
#include "../CmdCalculator/dynamic_mathast.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculator/NotImplementedException.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"

namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::String StringT, std::integral IntT>
	class StubTrackingAntlrContextToMathAstConverter :
		public CmdCalculator::BasicAntlrContextToMathAstConverter_IntendedSatisfaction
	{
	public:

		using StringType = StringT;
		using IntType = IntT;


		StringT convertedContextLeadingTrivia;
		StringT convertedContextTrailingTrivia;
		//std::span<CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<StringType>> convertedContextParts;


		/*std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionNode<StringType>> getConvertedFull_expressionContext(CmdCalculator::Antlr::CmdCalculatorExpressionParser::Full_expressionContext& context)
		{
			return
				std::make_unique<MathAst::StubTrackingDynamicExpressionNode<StringType>>
				(
					context,
					convertedContextLeadingTrivia,
					convertedContextTrailingTrivia,
					std::move
					(
						std::span<std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionPartNode<StringType>>>
						{
							convertedContextParts | std::views::transform
							(
								[](auto convertedContextPart)
								{
									return std::make_unique<CmdCalculator::MathAst::DynamicExpressionPartNode<StringType>>(convertedContextPart);
								}
							)
						}
					)
				)
			;
		}


		std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionNode<StringT>> getConvertedExpressionContext(CmdCalculator::Antlr::CmdCalculatorExpressionParser::ExpressionContext& context)
		{
			throw CmdCalculator::NotImplementedException{};
		}


		std::unique_ptr<CmdCalculator::MathAst::DynamicOperandNode<StringT>> getConvertedOperandContext(CmdCalculator::Antlr::CmdCalculatorExpressionParser::OperandContext& context)
		{
			throw CmdCalculator::NotImplementedException{};
		}


		std::unique_ptr<CmdCalculator::ConvertedOperation_part_pairContext<StringType>> getConvertedOperation_part_pairContext
		(
			CmdCalculator::Antlr::CmdCalculatorExpressionParser::Operation_part_pairContext& context
		)
		{
			throw CmdCalculator::NotImplementedException{};
		}


		std::unique_ptr<CmdCalculator::MathAst::DynamicBinaryOperatorNode<StringT>> getConvertedBinary_operatorContext(CmdCalculator::Antlr::CmdCalculatorExpressionParser::Binary_operatorContext& context)
		{
			throw CmdCalculator::NotImplementedException{};
		}


		std::unique_ptr<CmdCalculator::MathAst::DynamicNumberLiteralNode<StringT, IntT>> getConvertedNumber_literalContext(CmdCalculator::Antlr::CmdCalculatorExpressionParser::Number_literalContext& context)
		{
			throw CmdCalculator::NotImplementedException{};
		}


		std::unique_ptr<CmdCalculator::MathAst::DynamicSignOperationNode<StringT>> getConvertedSign_operationContext(CmdCalculator::Antlr::CmdCalculatorExpressionParser::Sign_operationContext& context)
		{
			throw CmdCalculator::NotImplementedException{};
		}


		std::unique_ptr<CmdCalculator::MathAst::DynamicSqrtOperationNode<StringT>> getConvertedSqrt_operationContext(CmdCalculator::Antlr::CmdCalculatorExpressionParser::Sqrt_operationContext& context)
		{
			throw CmdCalculator::NotImplementedException{};
		}


		std::unique_ptr<CmdCalculator::MathAst::DynamicGroupingNode<StringT>> getConvertedGroupingContext(CmdCalculator::Antlr::CmdCalculatorExpressionParser::GroupingContext& context)
		{
			throw CmdCalculator::NotImplementedException{};
		}


		std::unique_ptr<CmdCalculator::MathAst::DynamicGroupingMultiplicationNode<StringT>> getConvertedGrouping_multiplicationContext(CmdCalculator::Antlr::CmdCalculatorExpressionParser::Grouping_multiplicationContext& context)
		{
			throw CmdCalculator::NotImplementedException{};
		}


		std::unique_ptr<CmdCalculator::MathAst::DynamicAbsoluteValueNode<StringT>> getConvertedAbsolute_value_operationContext(CmdCalculator::Antlr::CmdCalculatorExpressionParser::Absolute_value_operationContext& context)
		{
			throw CmdCalculator::NotImplementedException{};
		}*/
	};
}