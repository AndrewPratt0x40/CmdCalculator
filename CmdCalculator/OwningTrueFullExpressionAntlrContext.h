#pragma once

#include <optional>
#include <memory>

#include "FullExpressionAntlrContext.h"
#include "TrueAntlrTokenView.h"
#include "TrueExpressionAntlrContextView.h"
#include "strings.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionLexer.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"


namespace CmdCalculator
{
	/// \brief An owning reference to a \ref CmdCalculator::Antlr::CmdCalculatorExpressionParser::Full_expressionContext instance.
	class OwningTrueFullExpressionAntlrContext :
		public FullExpressionAntlrContext_IntendedSatisfaction
	{
	private:
		const antlr4::ANTLRInputStream m_inputStream;
		static_assert(std::movable<std::remove_cv_t<decltype(m_inputStream)>>);
		const std::unique_ptr<CmdCalculator::Antlr::CmdCalculatorExpressionLexer> m_lexer;
		const std::unique_ptr<CmdCalculator::Antlr::CmdCalculatorExpressionParser> m_parser;
		const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Full_expressionContext* m_fullExpressionContext;


		OwningTrueFullExpressionAntlrContext
		(
			antlr4::ANTLRInputStream&& inputStream,
			std::unique_ptr<CmdCalculator::Antlr::CmdCalculatorExpressionLexer> lexer,
			std::unique_ptr<CmdCalculator::Antlr::CmdCalculatorExpressionParser> parser,
			const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Full_expressionContext* fullExpressionContext
		);


	public:
		/// \brief Creates a new instance of the \ref OwningTrueFullExpressionAntlrContext class by invoking the ANTLR runtime and parsing a given expression.
		/// \param input The expression to parse.
		/// \returns A new \ref OwningTrueFullExpressionAntlrContext instance.
		static OwningTrueFullExpressionAntlrContext parse(StringView auto input);


		/// \brief Accessor to the leading trivia of the full expression, if any.
		/// \returns The leading trivia, or an empty object if no leading trivia exists.
		std::optional<TrueAntlrTokenView> getLeadingTrivia() const;


		/// \brief Accessor to the contained expression.
		/// \returns A view of the contained expression.
		TrueExpressionAntlrContextView getExpressionValue() const;


		/// \brief Accessor to the trailing trivia of the full expression, if any.
		/// \returns The trailing trivia, or an empty object if no trailing trivia exists.
		std::optional<TrueAntlrTokenView> getTrailingTrivia() const;
	};


	static_assert(FullExpressionAntlrContext<OwningTrueFullExpressionAntlrContext>);
}