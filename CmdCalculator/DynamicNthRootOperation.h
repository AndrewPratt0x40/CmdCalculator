#pragma once
#pragma once

#include "DynamicExpression.h"
#include "RealNumber.h"

#include <concepts>
#include <memory>


namespace CmdCalculator::Expressions
{
	/// \brief An nth root operation.
	/// \tparam NumberT The type to use for numbers.
	template<Arithmetic::RealNumber NumberT>
	class DynamicNthRootOperation :
		public DynamicExpression<NumberT>
	{
	public:

		using NumberType = DynamicExpression<NumberT>::NumberType;


		/// \brief Creates a new instance of the \ref DynamicNthRootOperation class.
		/// \param degree The operand that is the root to get from the radicand.
		/// \param radicand The operand who's root to get.
		DynamicNthRootOperation
		(
			std::unique_ptr<DynamicExpression<NumberType>> degree,
			std::unique_ptr<DynamicExpression<NumberType>> radicand
		);


		virtual ~DynamicNthRootOperation();


		/// \brief Accessor to the degree of the operation.
		/// \returns The operand that is the root to get from the radicand.
		DynamicExpression<NumberType>& getDegree() const;


		/// \brief Accessor to the radicand of the operation.
		/// \returns The operand who's root to get.
		DynamicExpression<NumberType>& getRadicand() const;


		bool isSimplifiable() const override;


		DynamicExpressionBox<NumberType> getFullSimplification() const override;
	};
}

#include "DynamicNthRootOperation.hpp"