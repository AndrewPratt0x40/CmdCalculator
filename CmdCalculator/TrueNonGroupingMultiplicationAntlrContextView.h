#pragma once

#include <optional>

#include "NonGroupingMultiplicationAntlrContext.h"
#include "TrueAntlrTokenView.h"
#include "TrueNumberLiteralAntlrContextView.h"
#include "TrueSignOperationAntlrContextView.h"
#include "TrueSqrtOperationAntlrContextView.h"
#include "TrueGroupingAntlrContextView.h"
#include "TrueAbsoluteValueOperationAntlrContextView.h"
#include "strings.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"


namespace CmdCalculator
{
	/// \brief An owning reference to a \ref CmdCalculator::Antlr::CmdCalculatorExpressionParser::Non_grouping_multiplication_operandContext instance.
	class TrueNonGroupingMultiplicationAntlrContextView :
		public NonGroupingMultiplicationAntlrContext_IntendedSatisfaction
	{
	private:
		const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Non_grouping_multiplication_operandContext* m_nonGroupingMultiplicationContext;


	public:
		/// \brief Creates a new instance of the \ref TrueNonGroupingMultiplicationAntlrContextView class.
		/// \param nonGroupingMultiplicationContext The context object to view.
		TrueNonGroupingMultiplicationAntlrContextView
			(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Non_grouping_multiplication_operandContext* operandContext);


		/// \brief Accessor to the kind of non-grouping multiplication node.
		/// \returns The specific kind of non-grouping multiplication the node is.
		ENonGroupingMultiplicationAntlrContextKind ENonGroupingMultiplicationAntlrContextKind() const;


		/// \brief Accessor to the non-grouping multiplication node as a number literal, if it is one.
		/// \returns A view of the non-grouping multiplication node as a number literal, or an empty object otherwise.
		std::optional<TrueNumberLiteralAntlrContextView> getNumberLiteral() const;


		/// \brief Accessor to the non-grouping multiplication node as a sign operation, if it is one.
		/// \returns A view of the non-grouping multiplication node as a sign operation, or an empty object otherwise.
		std::optional<TrueSignOperationAntlrContextView> getSignOperation() const;


		/// \brief Accessor to the non-grouping multiplication node as a sqrt operation, if it is one.
		/// \returns A view of the non-grouping multiplication node as a sqrt operation, or an empty object otherwise.
		std::optional<TrueSqrtOperationAntlrContextView> getSqrtOperation() const;


		/// \brief Accessor to the non-grouping multiplication node as a grouping, if it is one.
		/// \returns A view of the non-grouping multiplication node as a grouping, or an empty object otherwise.
		std::optional<TrueGroupingAntlrContextView> getGrouping() const;


		/// \brief Accessor to the non-grouping multiplication node as a absolute value operation, if it is one.
		/// \returns A view of the non-grouping multiplication node as a absolute value operation, or an empty object otherwise.
		std::optional<TrueAbsoluteValueOperationAntlrContextView> getAbsoluteValueOperation() const;
	};


	static_assert(NonGroupingMultiplicationAntlrContext<TrueNonGroupingMultiplicationAntlrContextView>);
}