#pragma once

#include <string>

#include "ExpressionToStringConverter.h"
#include "Expression.h"
#include "strings.h"


namespace CmdCalculator
{
	/// \brief An algorithm that converts the evaluation of expression objects to strings.
	/// \tparam ExpressionT The type of expressions to convert to strings.
	template<Expressions::Expression ExpressionT>
	class ExpressionEvaluationToStringConverter :
		public ExpressionToStringConverter_IntendedSatisfaction
	{
	public:
		using ExpressionType = ExpressionT;
		using ExpressionNumberType = Expressions::ExpressionEvaluationType<ExpressionT>;
		using ExpressionStringType = decltype(std::declval<ExpressionNumberType>().getStringRepresentation());
		using CharType = ExpressionStringType::value_type;
		using StringType = std::basic_string<CharType>;


		/// \brief Converts an expression's evaluation to a string.
		/// \param source The expression to convert.
		/// \param configuration Calculation settings that affect how to expression will be represented as a string.
		/// \returns The evaluation of \param source as a string.
		StringType stringifyExpression(const ExpressionT& source, const CalculationConfiguration& configuration) const;
	};
}


#include "ExpressionEvaluationToStringConverter.hpp"