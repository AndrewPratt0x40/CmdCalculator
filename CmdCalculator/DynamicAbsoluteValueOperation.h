#pragma once

#include "DynamicExpression.h"
#include "RealNumber.h"

#include <concepts>
#include <memory>


namespace CmdCalculator::Expressions
{
	/// \brief An absolute value operation.
	/// \tparam NumberT The type to use for numbers.
	template<Arithmetic::RealNumber NumberT>
	class DynamicAbsoluteValueOperation :
		public DynamicExpression<NumberT>
	{
	public:

		using NumberType = DynamicExpression<NumberT>::NumberType;


		/// \brief Creates a new instance of the \ref DynamicAbsoluteValueOperation class.
		/// \param operand The operand who's absolute value to retrieve.
		DynamicAbsoluteValueOperation(std::unique_ptr<DynamicExpression<NumberType>> operand);


		virtual ~DynamicAbsoluteValueOperation();


		/// \brief Accessor to the operand of the operation.
		/// \returns The operand who's absolute value to retrieve.
		DynamicExpression<NumberType>& getOperand() const;


		NumberType getEvaluation() const override;


		//bool isSimplifiable() const override;


		//DynamicExpressionBox<NumberType> getFullSimplification() const override;
	};
}

#include "DynamicAbsoluteValueOperation.hpp"