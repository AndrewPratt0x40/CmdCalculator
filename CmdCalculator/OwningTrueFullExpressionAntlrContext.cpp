#include "OwningTrueFullExpressionAntlrContext.h"

#include <assert.h>
#include "strings.h"
#include "utilities.h"


CmdCalculator::OwningTrueFullExpressionAntlrContext::OwningTrueFullExpressionAntlrContext
(
	std::unique_ptr<antlr4::ANTLRInputStream> inputStream,
	std::unique_ptr<CmdCalculator::Antlr::CmdCalculatorExpressionLexer> lexer,
	std::unique_ptr<antlr4::CommonTokenStream> tokenStream,
	std::unique_ptr<CmdCalculator::Antlr::CmdCalculatorExpressionParser> parser,
	const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Full_expressionContext* fullExpressionContext
) :
	m_inputStream{ std::move(inputStream) },
	m_lexer{ std::move(lexer) },
	m_tokenStream{ std::move(tokenStream) },
	m_parser{ std::move(parser) },
	m_fullExpressionContext{ fullExpressionContext }
{
	assert(m_inputStream);
	assert(m_lexer);
	assert(m_tokenStream);
	assert(m_parser);
	assert(m_fullExpressionContext);
}


std::optional<CmdCalculator::TrueAntlrTokenView> CmdCalculator::OwningTrueFullExpressionAntlrContext::getLeadingTrivia() const
{
	return
		m_fullExpressionContext->leading_trivia
		? std::make_optional<TrueAntlrTokenView>(m_fullExpressionContext->leading_trivia)
		: std::optional<TrueAntlrTokenView>{}
	;
}


CmdCalculator::TrueExpressionAntlrContextView CmdCalculator::OwningTrueFullExpressionAntlrContext::getExpressionValue() const
{
	return TrueExpressionAntlrContextView{ m_fullExpressionContext->expression_value };
}


std::optional<CmdCalculator::TrueAntlrTokenView> CmdCalculator::OwningTrueFullExpressionAntlrContext::getTrailingTrivia() const
{
	return
		m_fullExpressionContext->trailing_trivia
		? std::make_optional<TrueAntlrTokenView>(m_fullExpressionContext->trailing_trivia)
		: std::optional<TrueAntlrTokenView>{}
	;
}