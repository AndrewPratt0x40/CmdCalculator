#pragma once

#include "DynamicExpression.h"
#include "RealNumber.h"

#include <concepts>


namespace CmdCalculator::Expressions
{
	/// \brief An addition operation.
	/// \tparam NumberT The type to use for numbers.
	template<Arithmetic::RealNumber NumberT>
	class DynamicAdditionOperation :
		public DynamicExpression<NumberT>,
		public Expression_IntendedSatisfaction
	{
	public:

		using NumberType = DynamicExpression<NumberT>::NumberType;


		/// \brief Creates a new instance of the \ref DynamicAdditionOperation class.
		/// \param augend The operand that the addend is to be added to.
		/// \param addend The operand to be added to the augend.
		DynamicAdditionOperation
		(
			std::unique_ptr<DynamicExpression<NumberType>> augend,
			std::unique_ptr<DynamicExpression<NumberType>> addend
		);


		virtual ~DynamicAdditionOperation();


		/// \brief Accessor to the augend of the operation.
		/// \returns The operand that the addend is to be added to.
		DynamicExpression<NumberType>& getAugend() const;


		/// \brief Accessor to the addend of the operation.
		/// \returns The operand to be added to the augend.
		DynamicExpression<NumberType>& getAddend() const;

		NumberType getEvaluation() const override;


		//bool isSimplifiable() const override;


		//DynamicExpressionBox<NumberType> getFullSimplification() const override;
	};
}

#include "DynamicAdditionOperation.hpp"