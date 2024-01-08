#pragma once

#include <concepts>
#include <span>

#include "../CmdCalculator/DynamicExpressionNode.h"
#include "../CmdCalculator/DynamicExpressionPartNode.h"
#include "../CmdCalculator/AntlrFullExpressionContextOwner.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"

namespace CmdCalculatorTestDoubles::MathAst
{
	template<CmdCalculator::String StringT>
	class StubTrackingDynamicExpressionNode :
		public CmdCalculator::MathAst::DynamicExpressionNode<StringT>
	{
	public:
		using SourceStringTreeType = decltype(std::declval<CmdCalculator::Antlr::CmdCalculatorExpressionParser::Full_expressionContext>().toStringTree());

		SourceStringTreeType sourceStringTree;


		StubTrackingDynamicExpressionNode
		(
			const SourceStringTreeType source,
			const StringT leadingTrivia,
			const StringT trailingTrivia,
			const std::span<MathAst::StubTrackingDynamicExpressionNode<StringT>>&& parts
		) : CmdCalculator::MathAst::DynamicExpressionNode<StringT>(leadingTrivia, trailingTrivia, std::move(parts)),
			sourceStringTree{ source }
		{}
	};
}