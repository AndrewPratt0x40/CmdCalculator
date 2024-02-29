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
			RecursiveSplitResultToDynamicExpressionConverterT && recursiveSplitResultToDynamicExpressionConverter
		)
		{
			recursiveSplitResultToDynamicExpressionConverter.getSplitResultAsExpression
			(
				std::declval<SplitResultType<DynamicExpressionPartRecursiveSplitterT>>()
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
		using OutputExpressionInnerType =
			SmartPointedToType
			<
				decltype
				(
					std::declval<RecursiveSplitResultToDynamicExpressionConverterType>()
					.getSplitResultAsExpression
					(
						std::declval<SplitResultType<DynamicExpressionPartRecursiveSplitterType>>()
					)
				)
			>
		;
		using OutputExpressionType = Expressions::DynamicExpressionBox<OutputExpressionInnerType>;


	private:
		DynamicExpressionPartRecursiveSplitterType m_splitter;
		RecursiveSplitResultToDynamicExpressionConverterType m_splitResultConverter;


	public:

		/// \brief Creates a new instance of the \ref DynamicMathAstToDynamicExpressionConverter class.
		/// \param splitter The object to use for splitting collections of expression parts.
		/// \param splitResultConverter The object to use for converting split results into \ref Expressions::DynamicExpression instances.
		DynamicMathAstToDynamicExpressionConverter
		(
			DynamicExpressionPartRecursiveSplitterType&& splitter,
			RecursiveSplitResultToDynamicExpressionConverterType&& splitResultConverter
		);


		/// \brief Converts a mathematical abstract syntax tree into an expression.
		/// \param sourceRootNode The root node of the math AST to convert from.
		/// \returns \p sourceRootNode as a \ref Expressions::DynamicExpressionNode instance.
		OutputExpressionType getMathAstAsExpression(const RootMathAstNodeType& sourceRootNode) const;
	};
}


#include "DynamicMathAstToDynamicExpressionConverter.hpp"