#pragma once

#include "Expression.h"
#include "RealNumber.h"

#include <memory>


namespace CmdCalculator::Expressions
{
	template<Arithmetic::RealNumber NumberT>
	class DynamicExpression;


	/// \brief A type that holds a polymorphic reference to a \ref DynamicExpression value.
	/// \tparam NumberT The type to use for numbers.
	template<Arithmetic::RealNumber NumberT>
	class DynamicExpressionBox :
		public Expression_IntendedSatisfaction
	{
	public:

		using NumberType = NumberT;


	private:

		std::unique_ptr<DynamicExpression<NumberType>> m_innerValue;


	public:

		/// \brief Creates a new instance of the \ref DynamicExpressionBox class.
		/// \param innerValue The value to box.
		DynamicExpressionBox(std::unique_ptr<DynamicExpression<NumberType>> innerValue);


		DynamicExpressionBox() = delete;


		/// \brief Tests whether or not the expression can be simplified.
		/// \returns True if the expression is simplifiable, false if the expression is already in it's simplest form.
		inline bool isSimplifiable() const;


		/// \brief Accessor to the full simplification of the expression.
		/// \returns The expression in it's simplest form.
		inline DynamicExpressionBox getFullSimplification() const;
	};
}

#include "DynamicExpressionBox.hpp"