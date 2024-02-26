#pragma once

#include <vector>
#include <memory>

#include "../CmdCalculator/dynamic_mathast.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubles::MathAst
{
	template<::CmdCalculator::String StringT, ::CmdCalculator::StringView SourceStringViewT>
	class StubTrackingDynamicExpressionNode :
		public ::CmdCalculator::MathAst::DynamicExpressionNode<StringT>,
		public ::CmdCalculator::MathAst::ExpressionNode_IntendedSatisfaction,
		public ::CmdCalculator::MathAst::MathAstNode_IntendedSatisfaction
	{
	public:
		using StringType = StringT;
		using SourceStringViewType = SourceStringViewT;
		using PartsType = std::ranges::owning_view<std::vector<std::unique_ptr<::CmdCalculator::MathAst::DynamicExpressionPartNode<StringType>>>>;

		SourceStringViewType stringSource;

		StringType stringRepresentation;

		
		StubTrackingDynamicExpressionNode
		(
			SourceStringViewType stringSource,
			const StringType stringRepresentation,
			const StringType leadingTrivia,
			const StringType trailingTrivia,
			PartsType&& parts
		) :
			::CmdCalculator::MathAst::DynamicExpressionNode<StringType>(leadingTrivia, trailingTrivia, std::forward<PartsType&&>(parts)),
			stringSource{ stringSource }
		{}

		StubTrackingDynamicExpressionNode
		(
			SourceStringViewType stringSource,
			const StringType stringRepresentation,
			const StringType leadingTrivia,
			const StringType trailingTrivia
		) :
			StubTrackingDynamicExpressionNode
			(
				stringSource,
				stringRepresentation,
				leadingTrivia,
				trailingTrivia,
				std::move(PartsType{})
			)
		{}
	};
}