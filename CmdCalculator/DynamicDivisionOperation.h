#pragma once

#include "CommonDynamicBinaryOperation.h"
#include "RealNumber.h"

#include <concepts>
#include <memory>


namespace CmdCalculator::Expressions
{
	/// \brief A division operation.
	/// \tparam NumberT The type to use for numbers.
	template<Arithmetic::RealNumber NumberT>
	class DynamicDivisionOperation :
		public CommonDynamicBinaryOperation<NumberT>,
		public Expression_IntendedSatisfaction
	{
	public:

		using NumberType = CommonDynamicBinaryOperation<NumberT>::NumberType;


		/// \brief Creates a new instance of the \ref DynamicDivisionOperation class.
		/// \param dividend The operand to divide by the divisor.
		/// \param divisor The operand that the dividend is to be divided by.
		DynamicDivisionOperation
		(
			std::unique_ptr<DynamicExpression<NumberType>> dividend,
			std::unique_ptr<DynamicExpression<NumberType>> divisor
		);


		virtual ~DynamicDivisionOperation();


		/// \brief Accessor to the dividend of the operation.
		/// \returns The operand to divide by the divisor.
		/// \example The dividend of the expression <tt>1/2<\tt> would be <tt>1</tt>.
		DynamicExpression<NumberType>& getDividend() const;


		/// \brief Accessor to the divisor of the operation.
		/// \returns The operand that the dividend is to be divided by.
		/// \example The divisor of the expression <tt>1/2<\tt> would be <tt>2</tt>.
		DynamicExpression<NumberType>& getDivisor() const;


		NumberType getEvaluation() const override;


		//bool isSimplifiable() const override;


		//DynamicExpressionBox<NumberType> getFullSimplification() const override;
	};
}

#include "DynamicDivisionOperation.hpp"