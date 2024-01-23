#pragma once

#include <ranges>

#include "GroupingMultiplicationAntlrContext.h"
#include "TrueNonGroupingMultiplicationAntlrContextView.h"
#include "TrueGroupingTailMultiplicandAntlrContextView.h"
#include "strings.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"


namespace CmdCalculator
{
	/// \brief A non-owning reference to a \ref CmdCalculator::Antlr::CmdCalculatorExpressionParser::Grouping_multiplicationContext instance.
	class TrueGroupingMultiplicationAntlrContextView :
		public GroupingMultiplicationAntlrContext_IntendedSatisfaction
	{
	private:
		const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Grouping_multiplicationContext* m_groupingMultiplicationContext;


	public:
		/// \brief Creates a new instance of the \ref TrueGroupingMultiplicationAntlrContextView class.
		/// \param groupingMultiplicationContext The context object to view.
		TrueGroupingMultiplicationAntlrContextView(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Grouping_multiplicationContext* groupingMultiplicationContext);


		/// \brief Accessor to the head multiplicand of the grouping multiplication.
		/// \returns A view of the value to be multiplied by all of the groupings that follow it.
		TrueNonGroupingMultiplicationAntlrContextView getHeadMultiplicand() const;


		/// \brief Accessor to the tail multiplicands of the grouping multiplication.
		/// \returns A range of views of every grouping to be multiplied by the head multiplicand.
		std::ranges::input_range auto getTailMultiplicands() const;
	};


	static_assert(GroupingMultiplicationAntlrContext<TrueGroupingMultiplicationAntlrContextView>);
}