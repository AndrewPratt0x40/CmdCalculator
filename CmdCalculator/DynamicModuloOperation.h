#pragma once
#pragma once

#include "DynamicExpression.h"
#include "RealNumber.h"

#include <concepts>
#include <memory>


namespace CmdCalculator::Expressions
{
	/// \brief A modulo operation.
	/// \tparam NumberT The type to use for numbers.
	template<Arithmetic::RealNumber NumberT>
	class DynamicModuloOperation :
		public DynamicExpression<NumberT>
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
		DynamicExpression<NumberType>& getDividend() const;


		/// \brief Accessor to the divisor of the operation.
		/// \returns The divisor of the division operation to retrieve the remainder from.
		DynamicExpression<NumberType>& getDivisor() const;


		NumberType getEvaluation() const override;


		//bool isSimplifiable() const override;


		//DynamicExpressionBox<NumberType> getFullSimplification() const override;
	};
}

#include "DynamicModuloOperation.hpp"