#pragma once


#include "WholelessNumberLiteralAntlrContext.h"
#include "TrueAntlrTokenView.h"
#include "strings.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"


namespace CmdCalculator
{
	/// \brief A non-owning reference to a \ref CmdCalculator::Antlr::CmdCalculatorExpressionParser::Wholeless_number_literalContext instance.
	class TrueWholelessNumberLiteralAntlrContextView :
		public WholelessNumberLiteralAntlrContext_IntendedSatisfaction
	{
	private:
		const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Wholeless_number_literalContext* m_wholelessNumberLiteralContext;


	public:
		/// \brief Creates a new instance of the \ref TrueWholelessNumberLiteralAntlrContextView class.
		/// \param wholelessNumberLiteralContext The context object to view.
		TrueWholelessNumberLiteralAntlrContextView(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Wholeless_number_literalContext* wholelessNumberLiteralContext);


		/// \brief Accessor to the decimal point of the number literal.
		/// \returns The token holding the text content of the number's decimal point.
		TrueAntlrTokenView getDecimalPoint() const;
		
		
		/// \brief Accessor to the fractional part of the number literal.
		/// \returns The token holding the text content of the number's fractional part.
		TrueAntlrTokenView getFractionalPart() const;
	};


	static_assert(WholelessNumberLiteralAntlrContext<TrueWholelessNumberLiteralAntlrContextView>);
}