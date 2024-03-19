#pragma once

#include <ranges>
#include <utility>
#include <span>
#include <vector>
#include <memory>

#include "../CmdCalculator/dynamic_mathast.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubles::MathAst
{
	template<CmdCalculator::String StringT>
	class StubDynamicExpressionNode :
		public CmdCalculator::MathAst::DynamicExpressionNode<StringT>,
		public CmdCalculator::MathAst::ExpressionNode_IntendedSatisfaction,
		public CmdCalculator::MathAst::MathAstNode_IntendedSatisfaction
	{
	public:
		using StringType = StringT;


		StringType stringRepresentation;
		using PartsValueType = CmdCalculator::MathAst::DynamicExpressionPartNode<StringType>;
		using PartsRangeType = std::vector<std::unique_ptr<PartsValueType>>;
		using PartsType = std::ranges::owning_view<PartsRangeType>;

		
		StubDynamicExpressionNode
		(
			const StringType stringRepresentation,
			const StringType leadingTrivia,
			const StringType trailingTrivia,
			PartsType&& parts
		) :
			CmdCalculator::MathAst::DynamicExpressionNode<StringType>(leadingTrivia, trailingTrivia, std::move(parts)),
			stringRepresentation{ stringRepresentation }
		{}

		StubDynamicExpressionNode
		(
			const StringType stringRepresentation,
			const StringType leadingTrivia,
			const StringType trailingTrivia
		) :
			StubDynamicExpressionNode
			(
				stringRepresentation,
				leadingTrivia,
				trailingTrivia,
				std::move(PartsType{})
			)
		{}


		StringT getStringRepresentation() const override
		{
			return stringRepresentation;
		}
	};
}