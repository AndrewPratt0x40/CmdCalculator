#pragma once

#include <optional>

#include "BinaryOperatorAntlrContext.h"
#include "TrueAntlrTokenView.h"
#include "strings.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"


namespace CmdCalculator
{
	/// \brief A non-owning reference to a \ref CmdCalculator::Antlr::CmdCalculatorExpressionParser::Binary_operatorContext instance.
	class TrueBinaryOperatorAntlrContextView :
		public BinaryOperatorAntlrContext_IntendedSatisfaction
	{
	private:
		const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Binary_operatorContext* m_binaryOperatorContext;


	public:
		/// \brief Creates a new instance of the \ref TrueBinaryOperatorAntlrContextView class.
		/// \param binaryOperatorContext The context object to view.
		TrueBinaryOperatorAntlrContextView(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Binary_operatorContext* binaryOperatorContext);


		/// \brief Accessor to the kind of binary operator node.
		/// \returns The specific kind of binary operator the node is.
		EBinaryOperatorAntlrContextKind getBinaryOperatorAntlrContextKind() const;


		/// \brief Accessor to the token representing the binary operator.
		/// \returns A view of the token representing the binary operator.
		TrueAntlrTokenView getToken() const;
	};
}