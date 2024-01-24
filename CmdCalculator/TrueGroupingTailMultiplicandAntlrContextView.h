#pragma once

#include <optional>

#include "GroupingTailMultiplicandAntlrContext.h"
#include "TrueAntlrTokenView.h"
#include "TrueGroupingAntlrContextView.h"
#include "strings.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"


namespace CmdCalculator
{
	/// \brief A non-owning reference to a \ref CmdCalculator::Antlr::CmdCalculatorExpressionParser::Grouping_tail_multiplicandContext instance.
	class TrueGroupingTailMultiplicandAntlrContextView :
		public GroupingTailMultiplicandAntlrContext_IntendedSatisfaction
	{
	private:
		const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Grouping_tail_multiplicandContext* m_groupingTailMultiplicandContext;


	public:
		/// \brief Creates a new instance of the \ref TrueGroupingTailMultiplicandAntlrContextView class.
		/// \param groupingTailMultiplicandContext The context object to view.
		TrueGroupingTailMultiplicandAntlrContextView(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Grouping_tail_multiplicandContext* groupingTailMultiplicandContext);


		/// \brief Accessor to the inner trivia.
		/// \returns A view of the trivial content between this grouping and the previous multiplicand.
		std::optional<TrueAntlrTokenView> getInnerTrivia() const;


		/// \brief Accessor to the grouping.
		/// \returns The grouping the object represents.
		TrueGroupingAntlrContextView getGroupingValue() const;
	};
}