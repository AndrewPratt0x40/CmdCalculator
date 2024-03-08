#pragma once

#include "DynamicExpression.h"
#include "DynamicExpressionBox.h"
#include "RealNumber.h"

#include <concepts>


namespace CmdCalculator::Expressions
{
	/// \brief A single numeric value.
	/// \tparam NumberT The type to use for numbers.
	template<Arithmetic::RealNumber NumberT>
	class DynamicNumber :
		public DynamicExpression<NumberT>
	{
	public:

		using NumberType = DynamicExpression<NumberT>::NumberType;


	private:
		NumberType m_value;


	public:

		/// \brief Creates a new instance of the \ref DynamicNumber class.
		/// \param value The numeric value of the object.
		DynamicNumber(const NumberType value);


		virtual ~DynamicNumber();


		/// \brief Accessor to the numeric value.
		/// \returns The value of the number the object represents.
		NumberT getValue() const;


		NumberT getEvaluation() const override;


		//bool isSimplifiable() const override;


		//DynamicExpressionBox<NumberType> getFullSimplification() const override;
	};
}

#include "DynamicNumber.hpp"