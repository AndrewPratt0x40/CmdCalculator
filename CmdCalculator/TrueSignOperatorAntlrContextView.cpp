#include "TrueSignOperatorAntlrContextView.h"

#include <assert.h>


CmdCalculator::TrueSignOperatorAntlrContextView::TrueSignOperatorAntlrContextView
	(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Sign_operatorContext* signOperatorContext) :
	m_signOperatorContext{ signOperatorContext }
{
	assert(m_signOperatorContext);
}


CmdCalculator::ESignOperatorAntlrContextKind CmdCalculator::TrueSignOperatorAntlrContextView::getSignOperatorAntlrContextKind() const
{
	return
		m_signOperatorContext->positive_sign_operator
		? ESignOperatorAntlrContextKind::Positive
		: ESignOperatorAntlrContextKind::Negative
	;
}


CmdCalculator::TrueAntlrTokenView CmdCalculator::TrueSignOperatorAntlrContextView::getToken() const
{
	return TrueAntlrTokenView
	{
		m_signOperatorContext->positive_sign_operator
		? m_signOperatorContext->positive_sign_operator
		: m_signOperatorContext->negative_sign_operator
	};
}