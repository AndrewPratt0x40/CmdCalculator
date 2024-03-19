#pragma once

#include "CommonDynamicBinaryOperation.h"
#include "RealNumber.h"

#include <concepts>
#include <memory>


namespace CmdCalculator::Expressions
{
	/// \brief A subtraction operation.
	/// \tparam NumberT The type to use for numbers.
	template<Arithmetic::RealNumber NumberT>
	class DynamicSubtractionOperation :
		public CommonDynamicBinaryOperation<NumberT>,
		public Expression_IntendedSatisfaction
	{
	public:

		using NumberType = DynamicExpression<NumberT>::NumberType;


		/// \brief Creates a new instance of the \ref DynamicSubtractionOperation class.
		/// \param minuend The operand that the subtrahend is to be subtracted from.
		/// \param subtrahend The operand to be subtracted from the minuend.
		DynamicSubtractionOperation
		(
			std::unique_ptr<DynamicExpression<NumberType>> minuend,
			std::unique_ptr<DynamicExpression<NumberType>> subtrahend
		);


		virtual ~DynamicSubtractionOperation();


		/// \brief Accessor to the minuend of the operation.
		/// \returns The operand that the subtrahend is to be subtracted from.
		/// \example The minuend of the expression <tt>1-2<\tt> would be <tt>1</tt>.
		DynamicExpression<NumberType>& getMinuend() const;


		/// \brief Accessor to the subtrahend of the operation.
		/// \returns The operand to be subtracted from the minuend.
		/// \example The subtrahend of the expression <tt>1-2<\tt> would be <tt>2</tt>.
		DynamicExpression<NumberType>& getSubtrahend() const;


		NumberType getEvaluation() const override;


		//bool isSimplifiable() const override;


		//DynamicExpressionBox<NumberType> getFullSimplification() const override;
	};
}

#include "DynamicSubtractionOperation.hpp"