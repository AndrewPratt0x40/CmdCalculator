#pragma once

#include <ranges>

#include "ExpressionAntlrContext.h"
#include "TrueAntlrTokenView.h"
#include "TrueOperandAntlrContextView.h"
#include "TrueOperationPartPairAntlrContextView.h"
#include "strings.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"


namespace CmdCalculator
{
	/// \brief A non-owning reference to a \ref CmdCalculator::Antlr::CmdCalculatorExpressionParser::ExpressionContext instance.
	class TrueExpressionAntlrContextView :
		public ExpressionAntlrContext_IntendedSatisfaction
	{
	private:
		const CmdCalculator::Antlr::CmdCalculatorExpressionParser::ExpressionContext* m_expressionContext;


	public:
		/// \brief Creates a new instance of the \ref TrueExpressionAntlrContextView class.
		/// \param expressionContext The context object to view.
		TrueExpressionAntlrContextView(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::ExpressionContext* expressionContext);


		/// \brief Accessor to the head operand of the expression.
		/// \returns A view of the head operand.
		TrueOperandAntlrContextView getHeadOperand() const;


		/// \brief Accessor to the operation part pair objects of the expression.
		/// \returns A range of views of every operation part pair object.
		std::ranges::input_range auto getOperationPartPairs() const;
	};


	static_assert(ExpressionAntlrContext<TrueExpressionAntlrContextView>);
}