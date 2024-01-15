#pragma once

#include <concepts>
#include <memory>
#include <utility>
#include <ranges>
#include <span>

#include "../CmdCalculator/AntlrContextToMathAstConverter.h"
#include "../CmdCalculator/AntlrContextTypeDeductions.h"
#include "../CmdCalculator/dynamic_mathast.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculator/NotImplementedException.h"
#include "StubTrackingFullExpressionAntlrContext.h"
#include "StubTrackingDynamicExpressionNode.h"

namespace CmdCalculatorTestDoubles
{
	template
	<
		CmdCalculator::String StringT,
		std::integral IntT,
		CmdCalculator::StringView SourceStringViewT
	>
	class StubTrackingAntlrContextToMathAstConverter :
		public CmdCalculator::AntlrContextToMathAstConverter_IntendedSatisfaction
	{
	public:

		using StringType = StringT;
		using IntType = IntT;
		using SourceStringViewType = SourceStringViewT;
		using FullExpressionAntlrContextType = StubTrackingFullExpressionAntlrContext<SourceStringViewType>;


		StringT convertedContextLeadingTrivia;
		StringT convertedContextTrailingTrivia;
		std::span<std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionPartNode<StringType>>> convertedContextParts;


		std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionNode<StringType>> getConvertedFullExpressionContext
		(const FullExpressionAntlrContextType& context)
		{
			return
				std::make_unique<MathAst::StubTrackingDynamicExpressionNode<StringType, SourceStringViewType>>
				(
					context.stringSource,
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
									return std::make_unique<CmdCalculator::MathAst::DynamicExpressionPartNode<StringType>>(*convertedContextPart);
								}
							)
						}
					)
				)
			;
		}


		std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionNode<StringT>> getConvertedExpressionContext
		(const CmdCalculator::AntlrContextTypeDeductions::ExpressionType<FullExpressionAntlrContextType>& context)
		{
			throw CmdCalculator::NotImplementedException{};
		}


		std::unique_ptr<CmdCalculator::MathAst::DynamicOperandNode<StringT>> getConvertedOperandContext
		(const CmdCalculator::AntlrContextTypeDeductions::OperandType<FullExpressionAntlrContextType>& context)
		{
			throw CmdCalculator::NotImplementedException{};
		}


		std::unique_ptr<CmdCalculator::ConvertedOperation_part_pairContext<StringType>> getConvertedOperationPartPairContext
		(const CmdCalculator::AntlrContextTypeDeductions::OperationPartPairType<FullExpressionAntlrContextType>& context)
		{
			throw CmdCalculator::NotImplementedException{};
		}


		std::unique_ptr<CmdCalculator::MathAst::DynamicBinaryOperatorNode<StringT>> getConvertedBinaryOperatorContext
		(const CmdCalculator::AntlrContextTypeDeductions::BinaryOperatorType<FullExpressionAntlrContextType>& context)
		{
			throw CmdCalculator::NotImplementedException{};
		}


		std::unique_ptr<CmdCalculator::MathAst::DynamicNumberLiteralNode<StringT, IntT>> getConvertedNumberLiteralContext
		(const CmdCalculator::AntlrContextTypeDeductions::NumberLiteralType<FullExpressionAntlrContextType>& context)
		{
			throw CmdCalculator::NotImplementedException{};
		}


		std::unique_ptr<CmdCalculator::MathAst::DynamicSignOperationNode<StringT>> getConvertedSignOperationContext
		(const CmdCalculator::AntlrContextTypeDeductions::SignOperationType<FullExpressionAntlrContextType>& context)
		{
			throw CmdCalculator::NotImplementedException{};
		}


		std::unique_ptr<CmdCalculator::MathAst::DynamicSqrtOperationNode<StringT>> getConvertedSqrtOperationContext
		(const CmdCalculator::AntlrContextTypeDeductions::SqrtOperationType<FullExpressionAntlrContextType>& context)
		{
			throw CmdCalculator::NotImplementedException{};
		}


		std::unique_ptr<CmdCalculator::MathAst::DynamicGroupingNode<StringT>> getConvertedGroupingContext
		(const CmdCalculator::AntlrContextTypeDeductions::GroupingType<FullExpressionAntlrContextType>& context)
		{
			throw CmdCalculator::NotImplementedException{};
		}


		std::unique_ptr<CmdCalculator::MathAst::DynamicGroupingMultiplicationNode<StringT>> getConvertedGroupingMultiplicationContext
		(const CmdCalculator::AntlrContextTypeDeductions::GroupingMultiplicationType<FullExpressionAntlrContextType>& context)
		{
			throw CmdCalculator::NotImplementedException{};
		}


		std::unique_ptr<CmdCalculator::MathAst::DynamicAbsoluteValueNode<StringT>> getConvertedAbsoluteValueOperationContext
		(const CmdCalculator::AntlrContextTypeDeductions::AbsoluteValueOperationType<FullExpressionAntlrContextType>& context)
		{
			throw CmdCalculator::NotImplementedException{};
		}
	};
}