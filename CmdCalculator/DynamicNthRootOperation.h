#pragma once
#pragma once

#include "CommonDynamicBinaryOperation.h"
#include "RealNumber.h"

#include <concepts>
#include <memory>


namespace CmdCalculator::Expressions
{
	/// \brief An nth root operation.
	/// \tparam NumberT The type to use for numbers.
	template<Arithmetic::RealNumber NumberT>
	class DynamicNthRootOperation :
		public CommonDynamicBinaryOperation<NumberT>,
		public Expression_IntendedSatisfaction
	{
	public:

		using NumberType = DynamicExpression<NumberT>::NumberType;


		// TODO: Take a natural number (positive integer) for the degree instead of any real number.
		// TODO: Consider supporting negative radicands.
		/// \brief Creates a new instance of the \ref DynamicNthRootOperation class.
		/// \param degree The operand that is the root to get from the radicand.
		/// \param radicand The operand who's root to get.
		DynamicNthRootOperation
		(
			std::unique_ptr<DynamicExpression<NumberType>> degree,
			std::unique_ptr<DynamicExpression<NumberType>> radicand
		);


		virtual ~DynamicNthRootOperation();


		/// \brief Accessor to the degree of the operation.
		/// \returns The operand that is the root to get from the radicand.
		/// \example The degree of the expression <tt>1_2<\tt> would be <tt>2</tt>.
		DynamicExpression<NumberType>& getDegree() const;


		/// \brief Accessor to the radicand of the operation.
		/// \returns The operand who's root to get.
		/// \example The radicand of the expression <tt>1_2<\tt> would be <tt>1</tt>.
		DynamicExpression<NumberType>& getRadicand() const;


		NumberType getEvaluation() const override;


		//bool isSimplifiable() const override;


		//DynamicExpressionBox<NumberType> getFullSimplification() const override;
	};
}

#include "DynamicNthRootOperation.hpp"