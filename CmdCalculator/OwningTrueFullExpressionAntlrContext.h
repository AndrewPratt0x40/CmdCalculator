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
		using AntlrStringType = TrueAntlrTokenView::StringType;
		using AntlrCharType = AntlrStringType::value_type;


		std::unique_ptr<antlr4::ANTLRInputStream> m_inputStream;
		std::unique_ptr<CmdCalculator::Antlr::CmdCalculatorExpressionLexer> m_lexer;
		std::unique_ptr<antlr4::CommonTokenStream> m_tokenStream;
		std::unique_ptr<CmdCalculator::Antlr::CmdCalculatorExpressionParser> m_parser;
		const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Full_expressionContext* m_fullExpressionContext;


		OwningTrueFullExpressionAntlrContext
		(
			std::unique_ptr<antlr4::ANTLRInputStream> inputStream,
			std::unique_ptr<CmdCalculator::Antlr::CmdCalculatorExpressionLexer> lexer,
			std::unique_ptr<antlr4::CommonTokenStream> tokenStream,
			std::unique_ptr<CmdCalculator::Antlr::CmdCalculatorExpressionParser> parser,
			const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Full_expressionContext* fullExpressionContext
		);


	public:
		/// \brief Creates a new instance of the \ref OwningTrueFullExpressionAntlrContext class by invoking the ANTLR runtime and parsing a given expression.
		/// \param input The expression to parse.
		/// \returns A new \ref OwningTrueFullExpressionAntlrContext instance.
		static OwningTrueFullExpressionAntlrContext parse(String auto input);


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


	CmdCalculator::OwningTrueFullExpressionAntlrContext CmdCalculator::OwningTrueFullExpressionAntlrContext::parse(String auto input)
	{
		try
		{
			const AntlrStringType inputString{ convertString<AntlrCharType>(input) };
			auto inputStream{ std::make_unique<antlr4::ANTLRInputStream>(inputString) };

			auto lexer{ std::make_unique<Antlr::CmdCalculatorExpressionLexer>(inputStream.get()) };
			lexer->removeErrorListeners();

			auto tokenStream{ std::make_unique<antlr4::CommonTokenStream>(lexer.get()) };

			auto parser{ std::make_unique<Antlr::CmdCalculatorExpressionParser>(tokenStream.get()) };
			const auto parserErrorHandler{ std::make_shared<antlr4::BailErrorStrategy>() };
			parser->setErrorHandler(parserErrorHandler);
			parser->removeErrorListeners();

			const auto* fullExpressionContext{ parser->full_expression() };

			return OwningTrueFullExpressionAntlrContext
			{
				std::move(inputStream),
				std::move(lexer),
				std::move(tokenStream),
				std::move(parser),
				fullExpressionContext
			};
		}
		catch (antlr4::ParseCancellationException& exception)
		{
			std::rethrow_if_nested(exception);
		}
	}
}