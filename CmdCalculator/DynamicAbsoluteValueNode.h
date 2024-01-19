#pragma once

#include "DynamicExpressionContainingNode.h"
#include "strings.h"
#include "NotImplementedException.h"

#include <concepts>
#include <ranges>
#include <utility>
#include <assert.h>

namespace CmdCalculator::MathAst
{
	/// \brief An absolute value operation expression.
	/// \tparam StringT The string type to use.
	template<String StringT>
	class DynamicAbsoluteValueNode :
		public DynamicExpressionContainingNode<StringT>
	{
	public:

		using StringType = DynamicExpressionContainingNode<StringT>::StringType;


	private:

		using CharType = typename StringType::value_type;

		const std::unique_ptr<DynamicExpressionNode<StringT>> m_containedExpression;
		const StringType m_leadingTrivia;
		const StringType m_trailingTrivia;


		CharType getBracketChar() const
		{
			return convertChar<CharType>('|');
		}

	public:


		virtual ~DynamicAbsoluteValueNode() = default;
		
		
		DynamicAbsoluteValueNode
		(
			std::unique_ptr<DynamicExpressionNode<StringT>> containedExpression,
			StringType leadingTrivia,
			StringType trailingTrivia
		) :
			m_containedExpression{ std::move(containedExpression) },
			m_leadingTrivia{ leadingTrivia },
			m_trailingTrivia{ trailingTrivia }
		{
			assert(m_containedExpression);
		}
		
		
		DynamicExpressionNode<StringT>* getContainedExpression() const override
		{
			return m_containedExpression.get();
		}


		StringType getLeadingTrivia() const override
		{
			return m_leadingTrivia;
		}


		StringType getTrailingTrivia() const override
		{
			return m_trailingTrivia;
		}


		StringType getStringRepresentation() const override
		{
			using StdStringType = std::basic_string<CharType>;

			return static_cast<StringType>
			(
				static_cast<StdStringType>(getLeadingTrivia())
				+ getBracketChar()
				+ static_cast<StdStringType>(getContainedExpression()->getStringRepresentation())
				+ getBracketChar()
				+ static_cast<StdStringType>(getTrailingTrivia())
			);
		}
	};
}