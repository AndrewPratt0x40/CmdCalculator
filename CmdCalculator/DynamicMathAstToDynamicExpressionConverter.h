#pragma once

#include <concepts>
#include <memory>

#include "MathAstToExpressionConverter.h"
#include "DynamicExpressionPartRecursiveSplitter.h"
#include "RecursiveSplitResultToDynamicExpressionConverter.h"
#include "DynamicExpressionNode.h"
#include "DynamicExpressionBox.h"
#include "FundamentallyBackedRealNumber.h"
#include "strings.h"


namespace CmdCalculator
{
	/// \brief Describes a compatible \ref DynamicExpressionPartRecursiveSplitter and \ref RecursiveSplitResultToDynamicExpressionConverter type.
	/// \tparam DynamicExpressionPartRecursiveSplitterT The type of object to use for splitting collections of expression parts.
	/// \tparam RecursiveSplitResultToDynamicExpressionConverterT The type of object to use for converting split results into \ref Expressions::DynamicExpression instances.
	template
	<
		class DynamicExpressionPartRecursiveSplitterT,
		class RecursiveSplitResultToDynamicExpressionConverterT
	>
	concept CompatibleSplitterAndResultToExpressionConverter =
		DynamicExpressionPartRecursiveSplitter<DynamicExpressionPartRecursiveSplitterT>
		&& RecursiveSplitResultToDynamicExpressionConverter<RecursiveSplitResultToDynamicExpressionConverterT>
		&& requires
		(
			DynamicExpressionPartRecursiveSplitterT&& dynamicExpressionPartRecursiveSplitter,
			RecursiveSplitResultToDynamicExpressionConverterT&& recursiveSplitResultToDynamicExpressionConverter
		)
		{
			recursiveSplitResultToDynamicExpressionConverter.getSplitResultAsExpression
			(
				dynamicExpressionPartRecursiveSplitter
				.tryToSplit
				(
					std::declval<MathAst::DynamicExpressionNodePartsView<typename DynamicExpressionPartRecursiveSplitterT::MathAstStringType>>()
				)
				.value()
			);
		}
	;
	
	
	/// \brief An algorithm to convert a \ref MathAst::DynamicExpressionNode to a \ref Expressions::DynamicExpression instance.
	/// \tparam DynamicExpressionPartRecursiveSplitterT The type of object to use for splitting collections of expression parts.
	/// \tparam RecursiveSplitResultToDynamicExpressionConverterT The type of object to use for converting split results into \ref Expressions::DynamicExpression instances.
	template
	<
		DynamicExpressionPartRecursiveSplitter DynamicExpressionPartRecursiveSplitterT,
		RecursiveSplitResultToDynamicExpressionConverter RecursiveSplitResultToDynamicExpressionConverterT
	>
		requires CompatibleSplitterAndResultToExpressionConverter<DynamicExpressionPartRecursiveSplitterT, RecursiveSplitResultToDynamicExpressionConverterT>
	class DynamicMathAstToDynamicExpressionConverter :
		public MathAstToExpressionConverter_IntendedSatisfaction
	{
	public:
		using DynamicExpressionPartRecursiveSplitterType = DynamicExpressionPartRecursiveSplitterT;
		using RecursiveSplitResultToDynamicExpressionConverterType = RecursiveSplitResultToDynamicExpressionConverterT;
		using MathAstStringType = DynamicExpressionPartRecursiveSplitterType::MathAstStringType;

		using RootMathAstNodeType = MathAst::DynamicExpressionNode<MathAstStringType>;
		using OutputExpressionNumberType = RecursiveSplitResultToDynamicExpressionConverterType::ExpressionNumberType;
		using OutputExpressionType = Expressions::DynamicExpressionBox<OutputExpressionNumberType>;


	private:
		// TODO


	public:

		/// \brief Converts a mathematical abstract syntax tree into an expression.
		/// \param sourceRootNode The root node of the math AST to convert from.
		/// \returns \p sourceRootNode as a \ref Expressions::DynamicExpressionNode instance.
		OutputExpressionType getMathAstAsExpression(const RootMathAstNodeType& sourceRootNode) const;
	};
}