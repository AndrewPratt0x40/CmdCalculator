#pragma once
#pragma once

#include "CommonDynamicBinaryOperation.h"
#include "RealNumber.h"

#include <concepts>
#include <memory>


namespace CmdCalculator::Expressions
{
	/// \brief A modulo operation.
	/// \tparam NumberT The type to use for numbers.
	template<Arithmetic::RealNumber NumberT>
	class DynamicModuloOperation :
		public CommonDynamicBinaryOperation<NumberT>,
		public Expression_IntendedSatisfaction
	{
	public:

		using NumberType = DynamicExpression<NumberT>::NumberType;


		/// \brief Creates a new instance of the \ref DynamicModuloOperation class.
		/// \param dividend The dividend of the division operation to retrieve the remainder from.
		/// \param divisor The divisor of the division operation to retrieve the remainder from.
		DynamicModuloOperation
		(
			std::unique_ptr<DynamicExpression<NumberType>> dividend,
			std::unique_ptr<DynamicExpression<NumberType>> divisor
		);


		virtual ~DynamicModuloOperation();


		/// \brief Accessor to the dividend of the operation.
		/// \returns The dividend of the division operation to retrieve the remainder from.
		/// \example The dividend of the expression <tt>1%2<\tt> would be <tt>1</tt>.
		DynamicExpression<NumberType>& getDividend() const;


		/// \brief Accessor to the divisor of the operation.
		/// \returns The divisor of the division operation to retrieve the remainder from.
		/// \example The divisor of the expression <tt>1%2<\tt> would be <tt>2</tt>.
		DynamicExpression<NumberType>& getDivisor() const;


		NumberType getEvaluation() const override;


		//bool isSimplifiable() const override;


		//DynamicExpressionBox<NumberType> getFullSimplification() const override;
	};
}

#include "DynamicModuloOperation.hpp"