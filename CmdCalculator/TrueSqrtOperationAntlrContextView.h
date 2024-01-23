#pragma once

#include <optional>

#include "SqrtOperationAntlrContext.h"
#include "TrueAntlrTokenView.h"
#include "TrueSignOperatorAntlrContextView.h"
#include "strings.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"


namespace CmdCalculator
{
	class TrueOperandAntlrContextView;


	/// \brief An owning reference to a \ref CmdCalculator::Antlr::CmdCalculatorExpressionParser::Sqrt_operationContext instance.
	class TrueSqrtOperationAntlrContextView :
		public SqrtOperationAntlrContext_IntendedSatisfaction
	{
	private:
		const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Sqrt_operationContext* m_sqrtOperationContext;


	public:
		/// \brief Creates a new instance of the \ref TrueSqrtOperationAntlrContextView class.
		/// \param sqrtOperationContext The context object to view.
		TrueSqrtOperationAntlrContextView(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Sqrt_operationContext* sqrtOperationContext);


		/// \brief Accessor to the inner trivia of the operation, if there is any.
		/// \returns A view of the trivial content between the sign operator and it's operand, or an empty object if there is no inner trivia.
		std::optional<TrueAntlrTokenView> getInnerTrivia() const;


		/// \brief Accessor to the operand of the operation.
		/// \returns A view of the operand.
		TrueOperandAntlrContextView getOperandValue() const;
	};


	static_assert(SqrtOperationAntlrContext<TrueSqrtOperationAntlrContextView>);
}