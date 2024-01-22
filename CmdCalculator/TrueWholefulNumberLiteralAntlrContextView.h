#pragma once

#include <optional>

#include "WholefulNumberLiteralAntlrContext.h"
#include "TrueAntlrTokenView.h"
#include "strings.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"


namespace CmdCalculator
{
	/// \brief An owning reference to a \ref CmdCalculator::Antlr::CmdCalculatorExpressionParser::Wholeful_number_literalContext instance.
	class TrueWholefulNumberLiteralAntlrContextView :
		public WholelessNumberLiteralAntlrContext_IntendedSatisfaction
	{
	private:
		const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Wholeful_number_literalContext* m_wholefulNumberLiteralContext;


	public:
		/// \brief Creates a new instance of the \ref TrueWholefulNumberLiteralAntlrContextView class.
		/// \param wholefulNumberLiteralContext The context object to view.
		TrueWholefulNumberLiteralAntlrContextView(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Wholeful_number_literalContext* wholefulNumberLiteralContext);


		/// \brief Accessor to the whole part of the number literal.
		/// \returns The token holding the text content of the number's whole part.
		TrueAntlrTokenView getWholePart() const;


		/// \brief Accessor to the decimal point of the number literal, if there is any.
		/// \returns The token holding the text content of the number's decimal point, or an empty object if no decimal point exists.
		std::optional<TrueAntlrTokenView> getDecimalPoint() const;


		/// \brief Accessor to the fractional part of the number literal, if there is any.
		/// \returns The token holding the text content of the number's fractional part, or an empty object if no fractional part exists.
		std::optional<TrueAntlrTokenView> getFractionalPart() const;
	};


	static_assert(WholefulNumberLiteralAntlrContext<TrueWholefulNumberLiteralAntlrContextView>);
}