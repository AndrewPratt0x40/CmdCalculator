#pragma once

#include "SignOperatorAntlrContext.h"
#include "TrueAntlrTokenView.h"
#include "strings.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"


namespace CmdCalculator
{
	/// \brief An owning reference to a \ref CmdCalculator::Antlr::CmdCalculatorExpressionParser::Sign_operatorContext instance.
	class TrueSignOperatorAntlrContextView :
		public SignOperatorAntlrContext_IntendedSatisfaction
	{
	private:
		const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Sign_operatorContext* m_signOperatorContext;


	public:
		/// \brief Creates a new instance of the \ref TrueSignOperatorAntlrContextView class.
		/// \param signOperatorContext The context object to view.
		TrueSignOperatorAntlrContextView(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Sign_operatorContext* signOperatorContext);


		/// \brief Accessor to the kind of sign operator node.
		/// \returns The specific kind of sign operator the node is.
		ESignOperatorAntlrContextKind getSignOperatorAntlrContextKind() const;


		/// \brief Accessor to the token representing the sign operator.
		/// \returns A view of the token representing the sign operator.
		TrueAntlrTokenView getToken() const;
	};


	static_assert(SignOperatorAntlrContext<TrueSignOperatorAntlrContextView>);
}