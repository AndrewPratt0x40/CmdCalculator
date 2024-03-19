#pragma once

#include <concepts>
#include <memory>

#include "Expression.h"
#include "DynamicExpression.h"
#include "RealNumber.h"


namespace CmdCalculator::Expressions
{
	template<class T>
	concept BoxableInnerExpression =
		Expression<T>
		&& std::convertible_to<T*, DynamicExpression<typename T::NumberType>*>
	;


	/// \brief A type that holds a polymorphic reference to a \ref DynamicExpression value.
	/// \tparam BoxedExpressionT The derived type of \ref DynamicExpression to box.
	template<BoxableInnerExpression BoxedExpressionT>
	class DynamicExpressionBox :
		public Expression_IntendedSatisfaction
	{
	public:

		using BoxedExpressionType = BoxedExpressionT;
		using NumberType = BoxedExpressionType::NumberType;


	private:

		std::unique_ptr<BoxedExpressionType> m_innerValue;


	public:

		/// \brief Creates a new instance of the \ref DynamicExpressionBox class.
		/// \param innerValue The value to box.
		DynamicExpressionBox(std::unique_ptr<BoxedExpressionT> innerValue);


		DynamicExpressionBox() = delete;


		/// \brief Accessor to the expression boxed by the object.
		/// \returns A reference to the boxed value.
		const BoxedExpressionT& getInnerValue() const;


		/// \brief Releases the expression boxed by the object.
		/// \returns A unique pointer to the value that was boxed by the object.
		/// \remark After calling this method, the object is left in a valid but unspecified state.
		std::unique_ptr<BoxedExpressionType> releaseInnerValue();


		/*/// \brief Tests whether or not the expression can be simplified.
		/// \returns True if the expression is simplifiable, false if the expression is already in it's simplest form.
		inline bool isSimplifiable() const;*/


		/// \brief Accessor to the evaluation of the expression.
		/// \returns The numeric value that the expression evaluates to.
		typename BoxedExpressionT::NumberType getEvaluation() const;


		/*/// \brief Accessor to the full simplification of the expression.
		/// \returns The expression in it's simplest form.
		inline DynamicExpressionBox getFullSimplification() const;*/
	};
}

#include "DynamicExpressionBox.hpp"