#pragma once

#include <optional>

#include "OperationPartPairAntlrContext.h"
#include "TrueAntlrTokenView.h"
#include "TrueOperandAntlrContextView.h"
#include "TrueBinaryOperatorAntlrContextView.h"
#include "strings.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"


namespace CmdCalculator
{
	/// \brief A non-owning reference to a \ref CmdCalculator::Antlr::CmdCalculatorExpressionParser::Operation_part_pairContext instance.
	class TrueOperationPartPairAntlrContextView :
		public OperationPartPairAntlrContext_IntendedSatisfaction
	{
	private:
		const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Operation_part_pairContext* m_operationPartPairContext;


	public:
		/// \brief Creates a new instance of the \ref TrueOperationPartPairAntlrContextView class.
		/// \param operationPartPairContext The context object to view.
		TrueOperationPartPairAntlrContextView(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Operation_part_pairContext* operationPartPairContext);


		/// \brief Accessor to the leading trivia of the operator, if there is any.
		/// \returns A view of trivial content between the operator and it's left operand, or an empty object if the operator has no leading trivia.
		std::optional<TrueAntlrTokenView> getOperatorLeadingTrivia() const;


		/// \brief Accessor to the operator.
		/// \returns A view of the binary operator.
		TrueBinaryOperatorAntlrContextView getOperatorValue() const;


		/// \brief Accessor to the trailing trivia of the operator, if there is any.
		/// \returns A view of trivial content between the operator and it's right operand, or an empty object if the operator has no trailing trivia.
		std::optional<TrueAntlrTokenView> getOperatorTrailingTrivia() const;


		/// \brief Accessor to the pair's operand.
		/// \returns A view of the right operand of the pair's binary operator.
		TrueOperandAntlrContextView getOperandValue() const;
	};


	static_assert(OperationPartPairAntlrContext<TrueOperationPartPairAntlrContextView>);
}