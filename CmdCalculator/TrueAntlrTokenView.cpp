#include "TrueAntlrTokenView.h"

#include <assert.h>


CmdCalculator::TrueAntlrTokenView::TrueAntlrTokenView(const antlr4::Token* token) :
	m_token{ token }
{
	assert(m_token);
}


CmdCalculator::TrueAntlrTokenView::StringType CmdCalculator::TrueAntlrTokenView::getText() const
{
	return m_token->getText();
}


CmdCalculator::TrueAntlrTokenView::StartIndexType CmdCalculator::TrueAntlrTokenView::getStartIndex() const
{
	return m_token->getStartIndex();
}


CmdCalculator::TrueAntlrTokenView::StopIndexType CmdCalculator::TrueAntlrTokenView::getStopIndex() const
{
	return m_token->getStopIndex();
}