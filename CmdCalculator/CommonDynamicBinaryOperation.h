#pragma once

#include "DynamicExpression.h"
#include "RealNumber.h"

#include <concepts>


namespace CmdCalculator::Expressions
{
	/// \brief Common implementation for a dynamic binary operation expression.
	/// \tparam NumberT The type to use for numbers.
	template<Arithmetic::RealNumber NumberT>
	class CommonDynamicBinaryOperation :
		public DynamicExpression<NumberT>,
		public Expression_IntendedSatisfaction
	{
	public:

		using NumberType = DynamicExpression<NumberT>::NumberType;


	private:
		std::unique_ptr<DynamicExpression<NumberType>> m_leftOperand;
		std::unique_ptr<DynamicExpression<NumberType>> m_rightOperand;


	protected:

		/// \brief Creates a new instance of the \ref DynamicAdditionOperation class.
		/// \param leftOperand The operand that would appear to the left of the operator.
		/// \param rightOperand The operand that would appear to the right of the operator.
		CommonDynamicBinaryOperation
		(
			std::unique_ptr<DynamicExpression<NumberType>> leftOperand,
			std::unique_ptr<DynamicExpression<NumberType>> rightOperand
		);


	public:


		virtual ~CommonDynamicBinaryOperation();


		/// \brief Accessor to the left operand.
		/// \returns The operand that would appear to the left of the operator.
		DynamicExpression<NumberType>& getLeftOperand() const;


		/// \brief Accessor to the right operand.
		/// \returns The operand that would appear to the right of the operator.
		DynamicExpression<NumberType>& getRightOperand() const;


		//bool isSimplifiable() const override;


		//DynamicExpressionBox<NumberType> getFullSimplification() const override;
	};
}

#include "CommonDynamicBinaryOperation.hpp"