#pragma once

#include "DynamicExpression.h"
#include "RealNumber.h"

#include <concepts>
#include <memory>


namespace CmdCalculator::Expressions
{
	/// \brief A negation operation.
	/// \tparam NumberT The type to use for numbers.
	template<Arithmetic::RealNumber NumberT>
	class DynamicNegationOperation :
		public DynamicExpression<NumberT>
	{
	public:

		using NumberType = DynamicExpression<NumberT>::NumberType;


	private:
		const std::unique_ptr<DynamicExpression<NumberType>> m_operand;


	public:

		/// \brief Creates a new instance of the \ref DynamicNegationOperation class.
		/// \param operand The operand who's value is negated by the operation.
		DynamicNegationOperation(std::unique_ptr<DynamicExpression<NumberType>> operand);


		virtual ~DynamicNegationOperation();


		/// \brief Accessor to the operand of the operation.
		/// \returns The operand who's value is negated by the operation.
		DynamicExpression<NumberType>& getOperand() const;


		NumberType getEvaluation() const override;


		//bool isSimplifiable() const override;


		//DynamicExpressionBox<NumberType> getFullSimplification() const override;
	};
}

#include "DynamicNegationOperation.hpp"