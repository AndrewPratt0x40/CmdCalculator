#pragma once
#pragma once

#include "CommonDynamicBinaryOperation.h"
#include "RealNumber.h"

#include <concepts>
#include <memory>


namespace CmdCalculator::Expressions
{
	/// \brief An exponentiation operation.
	/// \tparam NumberT The type to use for numbers.
	template<Arithmetic::RealNumber NumberT>
	class DynamicExponentiationOperation :
		public CommonDynamicBinaryOperation<NumberT>,
		public Expression_IntendedSatisfaction
	{
	public:

		using NumberType = DynamicExpression<NumberT>::NumberType;


		// TODO: Take a whole number (non-negative integer) for the exponent instead of any real number.
		/// \brief Creates a new instance of the \ref DynamicExponentiationOperation class.
		/// \param base The operand to be raised by the exponent.
		/// \param exponent The operand that the base is raised by.
		DynamicExponentiationOperation
		(
			std::unique_ptr<DynamicExpression<NumberType>> base,
			std::unique_ptr<DynamicExpression<NumberType>> exponent
		);


		virtual ~DynamicExponentiationOperation();


		/// \brief Accessor to the base of the operation.
		/// \returns The operand to be raised by the exponent.
		DynamicExpression<NumberType>& getBase() const;


		/// \brief Accessor to the exponent of the operation.
		/// \returns The operand that the base is raised by.
		DynamicExpression<NumberType>& getExponent() const;


		NumberType getEvaluation() const override;


		//bool isSimplifiable() const override;


		//DynamicExpressionBox<NumberType> getFullSimplification() const override;
	};
}

#include "DynamicExponentiationOperation.hpp"