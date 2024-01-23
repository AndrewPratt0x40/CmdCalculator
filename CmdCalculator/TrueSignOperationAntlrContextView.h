#pragma once

#include <optional>

#include "SignOperationAntlrContext.h"
#include "TrueAntlrTokenView.h"
#include "TrueSignOperatorAntlrContextView.h"
#include "strings.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"


namespace CmdCalculator
{
	class TrueOperandAntlrContextView;


	/// \brief A non-owning reference to a \ref CmdCalculator::Antlr::CmdCalculatorExpressionParser::Sign_operationContext instance.
	class TrueSignOperationAntlrContextView :
		public SignOperationAntlrContext_IntendedSatisfaction
	{
	private:
		const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Sign_operationContext* m_signOperationContext;


	public:
		/// \brief Creates a new instance of the \ref TrueSignOperationAntlrContextView class.
		/// \param signOperationContext The context object to view.
		TrueSignOperationAntlrContextView(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Sign_operationContext* signOperationContext);


		/// \brief Accessor to the operation's sign operator.
		/// \returns A view of the sign operator.
		TrueSignOperatorAntlrContextView getSignOperator() const;


		/// \brief Accessor to the inner trivia of the operation, if there is any.
		/// \returns A view of the trivial content between the sign operator and it's operand, or an empty object if there is no inner trivia.
		std::optional<TrueAntlrTokenView> getInnerTrivia() const;


		/// \brief Accessor to the operand of the operation.
		/// \returns A view of the operand.
		TrueOperandAntlrContextView getOperandValue() const;
	};


	static_assert(SignOperationAntlrContext<TrueSignOperationAntlrContextView>);
}