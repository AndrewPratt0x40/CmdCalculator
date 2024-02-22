#pragma once

#include <functional>
#include <concepts>
#include <memory>
#include <optional>
#include <vector>

#include "../CmdCalculator/DynamicExpressionPartSplitResult.h"
#include "../CmdCalculator/DynamicExpressionPartNode.h"
#include "../CmdCalculator/strings.h"


namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::String MathAstStringT>
	class StubDynamicExpressionPartSplitResult :
		public CmdCalculator::DynamicExpressionPartSplitResult_IntendedSatisfaction
	{
	public:
		using MathAstStringType = MathAstStringT;
		using DynamicExpressionPartType = CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringType>;


	private:
		const std::vector<std::reference_wrapper<const DynamicExpressionPartType>> m_leftParts;
		const std::reference_wrapper<const DynamicExpressionPartType> m_splitPart;
		const std::vector<std::reference_wrapper<const DynamicExpressionPartType>> m_rightParts;


		static std::vector<std::reference_wrapper<const DynamicExpressionPartType>> initPartRangeMember
			(const CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto partRefs)
		{
			std::ranges::input_range auto partsView
			{
				partRefs
				| std::views::transform
				(
					[](const DynamicExpressionPartType& part)
					{ return std::ref(part); }
				)
			};

			return std::vector<std::reference_wrapper<const DynamicExpressionPartType>>
				{ std::ranges::begin(partsView), std::ranges::end(partsView) }
			;
		}


	public:
		StubDynamicExpressionPartSplitResult
		(
			const CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto leftPartRefs,
			const DynamicExpressionPartType& splitPart,
			const CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto rightPartRefs
		) :
			m_leftParts{ initPartRangeMember(leftPartRefs) },
			m_splitPart{ std::ref(splitPart) },
			m_rightParts{ initPartRangeMember(rightPartRefs) }
		{}


		CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto getLeftParts() const
		{
			return m_leftParts | std::views::all;
		}


		const DynamicExpressionPartType& getSplitPart() const
		{
			return m_splitPart;
		}


		CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto getRightParts() const
		{
			return m_rightParts | std::views::all;
		}
	};
}