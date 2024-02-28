#pragma once

#include "Expression.h"
//#include "DynamicExpressionBox.h"
#include "RealNumber.h"

#include <concepts>


namespace CmdCalculator::Expressions
{
	/// \brief A type that satisfies \ref Expression that is implemented via dynamic polymorphism.
	/// \tparam NumberT The type to use for numbers.
	template<Arithmetic::RealNumber NumberT>
	class DynamicExpression :
		public Expression_IntendedSatisfaction
	{
	public:

		using NumberType = NumberT;


		virtual ~DynamicExpression()
		{}


		/*/// \brief Tests whether or not the expression can be simplified.
		/// \returns True if the expression is simplifiable, false otherwise.
		virtual bool isSimplifiable() const = 0;*/


		/// \brief Accessor to the evaluation of the expression.
		/// \returns The numeric value that the expression evaluates to.
		virtual NumberType getEvaluation() const = 0;


		/*/// \brief Accessor to the full simplification of the expression.
		/// \returns The expression in it's simplest form.
		virtual DynamicExpressionBox<NumberType> getFullSimplification() const = 0;*/
	};
}