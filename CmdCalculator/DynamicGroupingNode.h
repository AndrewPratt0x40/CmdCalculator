#pragma once

#include "DynamicExpressionContainingNode.h"
#include "strings.h"
#include "std_polyfills.h"
#include "NotImplementedException.h"

#include <concepts>
#include <ranges>
#include <utility>
#include <assert.h>

namespace CmdCalculator::MathAst
{
	/// \brief An expression grouped by parentheses.
	/// \tparam StringT The string type to use.
	template<String StringT>
	class DynamicGroupingNode :
		public DynamicExpressionContainingNode<StringT>
	{
	public:
		using StringType = DynamicExpressionContainingNode<StringT>::StringType;


	private:
		using CharType = typename StringType::value_type;


		const std::unique_ptr<DynamicExpressionNode<StringType>> m_containedExpression;
		const StringType m_leadingTrivia;
		const StringType m_trailingTrivia;


		CharType getOpeningBracketChar() const
		{
			return convertChar<CharType>('(');
		}


		CharType getClosingBracketChar() const
		{
			return convertChar<CharType>(')');
		}


	public:

		virtual ~DynamicGroupingNode() = default;

		
		DynamicGroupingNode
		(
			std::unique_ptr<DynamicExpressionNode<StringType>> containedExpression,
			StringType leadingTrivia,
			StringType trailingTrivia
		) :
			m_containedExpression{ std::move(containedExpression) },
			m_leadingTrivia{ leadingTrivia },
			m_trailingTrivia{ trailingTrivia }
		{
			assert(m_containedExpression);
		}


		DynamicExpressionNode<StringType>* getContainedExpression() const override
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


		virtual StringType getStringRepresentation() const override
		{
			using StdStringType = std::basic_string<CharType>;

			return static_cast<StringType>
			(
				static_cast<StdStringType>(getLeadingTrivia())
				+ getOpeningBracketChar()
				+ static_cast<StdStringType>(getContainedExpression()->getStringRepresentation())
				+ getClosingBracketChar()
				+ static_cast<StdStringType>(getTrailingTrivia())
			);
		}
	};
}