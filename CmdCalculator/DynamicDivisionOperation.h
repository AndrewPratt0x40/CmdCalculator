#pragma once

#include "DynamicExpression.h"
#include "RealNumber.h"

#include <concepts>
#include <memory>


namespace CmdCalculator::Expressions
{
	/// \brief A division operation.
	/// \tparam NumberT The type to use for numbers.
	template<Arithmetic::RealNumber NumberT>
	class DynamicDivisionOperation :
		public DynamicExpression<NumberT>
	{
	public:

		using NumberType = DynamicExpression<NumberT>::NumberType;


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
		DynamicExpression<NumberType>& getDividend() const;


		/// \brief Accessor to the divisor of the operation.
		/// \returns The operand that the dividend is to be divided by.
		DynamicExpression<NumberType>& getDivisor() const;


		NumberType getEvaluation() const override;


		//bool isSimplifiable() const override;


		//DynamicExpressionBox<NumberType> getFullSimplification() const override;
	};
}

#include "DynamicDivisionOperation.hpp"