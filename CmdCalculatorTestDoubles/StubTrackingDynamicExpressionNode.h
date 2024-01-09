#pragma once

#include <concepts>
#include <span>
#include <memory>

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
		using Full_expressionContextType = CmdCalculator::Antlr::CmdCalculatorExpressionParser::Full_expressionContext;

		Full_expressionContextType* sourceFull_expressionContext;


		StubTrackingDynamicExpressionNode
		(
			const Full_expressionContextType* source,
			const StringT leadingTrivia,
			const StringT trailingTrivia,
			const std::span<std::unique_ptr<MathAst::StubTrackingDynamicExpressionNode<StringT>>>&& parts
		) : CmdCalculator::MathAst::DynamicExpressionNode<StringT>(leadingTrivia, trailingTrivia, std::move(parts)),
			sourceFull_expressionContext{ source }
		{}
	};
}