#pragma once

#include <optional>

#include "AbsoluteValueOperationAntlrContext.h"
#include "TrueAntlrTokenView.h"
#include "strings.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"


namespace CmdCalculator
{
	class TrueExpressionAntlrContextView;


	/// \brief An owning reference to a \ref CmdCalculator::Antlr::CmdCalculatorExpressionParser::Absolute_value_operationContext instance.
	class TrueAbsoluteValueOperationAntlrContextView :
		public AbsoluteValueOperationAntlrContext_IntendedSatisfaction
	{
	private:
		const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Absolute_value_operationContext* m_absoluteValueOperationContext;


	public:
		/// \brief Creates a new instance of the \ref TrueAbsoluteValueOperationAntlrContextView class.
		/// \param absoluteValueOperationContext The context object to view.
		TrueAbsoluteValueOperationAntlrContextView(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Absolute_value_operationContext* absoluteValueOperationContext);


		/// \brief Accessor to the inner leading trivia of the grouping, if there is any.
		/// \returns A view of the trivial content between the grouping's opening bracket and it's inner expression, or an empty object if there is no inner leading trivia.
		std::optional<TrueAntlrTokenView> getInnerLeadingTrivia() const;


		/// \brief Accessor to the inner expression of the grouping.
		/// \returns A view of the expression contained by the grouping's brackets.
		TrueExpressionAntlrContextView getInnerExpression() const;


		/// \brief Accessor to the inner trailing trivia of the grouping, if there is any.
		/// \returns A view of the trivial content between the grouping's inner expression and it's closing bracket, or an empty object if there is no inner trailing trivia.
		std::optional<TrueAntlrTokenView> getInnerTrailingTrivia() const;
	};


	static_assert(AbsoluteValueOperationAntlrContext<TrueAbsoluteValueOperationAntlrContextView>);
}