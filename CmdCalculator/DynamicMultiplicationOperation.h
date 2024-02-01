#pragma once

#include "DynamicExpression.h"
#include "RealNumber.h"

#include <concepts>
#include <memory>


namespace CmdCalculator::Expressions
{
	/// \brief A multiplication operation.
	/// \tparam NumberT The type to use for numbers.
	template<Arithmetic::RealNumber NumberT>
	class DynamicMultiplicationOperation :
		public DynamicExpression<NumberT>
	{
	public:

		using NumberType = DynamicExpression<NumberT>::NumberType;


		/// \brief Creates a new instance of the \ref DynamicMultiplicationOperation class.
		/// \param multiplier The operand to multiply with the multiplicand.
		/// \param multiplicand The operand that the multiplier is to be multiplied with.
		DynamicMultiplicationOperation
		(
			std::unique_ptr<DynamicExpression<NumberType>> multiplier,
			std::unique_ptr<DynamicExpression<NumberType>> multiplicand
		);


		virtual ~DynamicMultiplicationOperation();


		/// \brief Accessor to the multiplier of the operation.
		/// \returns The operand that the multiplicand is to be multiplied with.
		DynamicExpression<NumberType>& getMultiplier() const;


		/// \brief Accessor to the multiplicand of the operation.
		/// \returns The operand to multiply with the multiplier.
		DynamicExpression<NumberType>& getMultiplicand() const;


		NumberType getEvaluation() const override;


		//bool isSimplifiable() const override;


		//DynamicExpressionBox<NumberType> getFullSimplification() const override;
	};
}

#include "DynamicMultiplicationOperation.hpp"