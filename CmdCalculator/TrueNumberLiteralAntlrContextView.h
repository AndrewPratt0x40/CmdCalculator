#pragma once

#include <optional>

#include "NumberLiteralAntlrContext.h"
#include "TrueAntlrTokenView.h"
#include "TrueWholefulNumberLiteralAntlrContextView.h"
#include "TrueWholelessNumberLiteralAntlrContextView.h"
#include "strings.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"


namespace CmdCalculator
{
	/// \brief An owning reference to a \ref CmdCalculator::Antlr::CmdCalculatorExpressionParser::Number_literalContext instance.
	class TrueNumberLiteralAntlrContextView :
		public NumberLiteralAntlrContext_IntendedSatisfaction
	{
	private:
		const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Number_literalContext* m_numberLiteralContext;


	public:
		/// \brief Creates a new instance of the \ref TrueNumberLiteralAntlrContextView class.
		/// \param numberLiteralContext The context object to view.
		TrueNumberLiteralAntlrContextView(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Number_literalContext* numberLiteralContext);


		/// \brief Accessor to the kind of number literal node.
		/// \returns The specific kind of number literal the node is.
		ENumberLiteralAntlrContextKind getNumberLiteralAntlrContextKind() const;


		/// \brief Accessor to the number literal node as a wholeful number literal, if it is one.
		/// \returns A view of the number literal node as a wholeful number literal, or an empty object if the number literal is wholeless.
		std::optional<TrueWholefulNumberLiteralAntlrContextView> getWholefulNumberLiteral() const;


		/// \brief Accessor to the number literal node as a wholeless number literal, if it is one.
		/// \returns A view of the number literal node as a wholeless number literal, or an empty object if the number literal is wholelful.
		std::optional<TrueWholelessNumberLiteralAntlrContextView> getWholelessNumberLiteral() const;
	};


	static_assert(NumberLiteralAntlrContext<TrueNumberLiteralAntlrContextView>);
}