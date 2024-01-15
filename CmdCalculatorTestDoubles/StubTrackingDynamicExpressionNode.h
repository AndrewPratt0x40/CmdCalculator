#pragma once

#include <span>

#include "../CmdCalculator/dynamic_mathast.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubles::MathAst
{
	template<CmdCalculator::String StringT, CmdCalculator::StringView SourceStringViewT>
	class StubTrackingDynamicExpressionNode :
		public CmdCalculator::MathAst::DynamicExpressionNode<StringT>,
		public CmdCalculator::MathAst::ExpressionNode_IntendedSatisfaction,
		public CmdCalculator::MathAst::MathAstNode_IntendedSatisfaction
	{
	public:
		using StringType = StringT;
		using SourceStringViewType = SourceStringViewT;

		SourceStringViewType stringSource;

		
		StubTrackingDynamicExpressionNode
		(
			SourceStringViewType stringSource,
			const StringType leadingTrivia,
			const StringType trailingTrivia,
			std::span<CmdCalculator::MathAst::DynamicExpressionPartNode<StringType>*>&& parts
		) :
			CmdCalculator::MathAst::DynamicExpressionNode<StringType>(leadingTrivia, trailingTrivia, std::move(parts)),
			stringSource{ stringSource }
		{}
	};
}