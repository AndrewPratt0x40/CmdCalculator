#pragma once

#include "CommonDynamicBinaryOperation.h"
#include "RealNumber.h"

#include <concepts>


namespace CmdCalculator::Expressions
{
	/// \brief An addition operation.
	/// \tparam NumberT The type to use for numbers.
	template<Arithmetic::RealNumber NumberT>
	class DynamicAdditionOperation :
		public CommonDynamicBinaryOperation<NumberT>,
		public Expression_IntendedSatisfaction
	{
	public:

		using NumberType = CommonDynamicBinaryOperation<NumberT>::NumberType;


	public:

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
		/// \example The augend of the expression <tt>1+2<\tt> would be <tt>1</tt>.
		DynamicExpression<NumberType>& getAugend() const;


		/// \brief Accessor to the addend of the operation.
		/// \returns The operand to be added to the augend.
		/// \example The addend of the expression <tt>1+2<\tt> would be <tt>2</tt>.
		DynamicExpression<NumberType>& getAddend() const;


		NumberType getEvaluation() const override;


		//bool isSimplifiable() const override;


		//DynamicExpressionBox<NumberType> getFullSimplification() const override;
	};
}

#include "DynamicAdditionOperation.hpp"