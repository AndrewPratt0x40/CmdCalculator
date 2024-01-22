#pragma once

#include <optional>

#include "OperandAntlrContext.h"
#include "TrueAntlrTokenView.h"
#include "TrueNonGroupingMultiplicationAntlrContextView.h"
#include "TrueGroupingMultiplicationAntlrContextView.h"
#include "strings.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"


namespace CmdCalculator
{
	/// \brief An owning reference to a \ref CmdCalculator::Antlr::CmdCalculatorExpressionParser::OperandContext instance.
	class TrueOperandAntlrContextView :
		public OperandAntlrContext_IntendedSatisfaction
	{
	private:
		const CmdCalculator::Antlr::CmdCalculatorExpressionParser::OperandContext* m_operandContext;


	public:
		/// \brief Creates a new instance of the \ref TrueOperandAntlrContextView class.
		/// \param operandContext The context object to view.
		TrueOperandAntlrContextView(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::OperandContext* operandContext);


		/// \brief Tests if the operand is a grouping multiplication.
		/// \returns True if the operand is a grouping multiplication, false if the operand is a non-grouping multiplication.
		bool isGroupingMultiplication() const;


		/// \brief Accessor to the operand node as a non-grouping multiplication, if it is one.
		/// \returns A view of the operand node as a non-grouping multiplication, or an empty object if the operand is a grouping multiplication.
		std::optional<TrueNonGroupingMultiplicationAntlrContextView> getNonGroupingMultiplicationOperand() const;


		/// \brief Accessor to the operand node as a grouping multiplication, if it is one.
		/// \returns A view of the operand node as a grouping multiplication, or an empty object if the operand is a non-grouping multiplication.
		std::optional<TrueGroupingMultiplicationAntlrContextView> getGroupingMultiplicationOperand() const;
	};


	static_assert(OperandAntlrContext<TrueOperandAntlrContextView>);
}