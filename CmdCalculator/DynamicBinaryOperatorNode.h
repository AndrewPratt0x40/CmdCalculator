#pragma once

#include "DynamicExpressionPartNode.h"
#include "EBinaryOperator.h"
#include "strings.h"
#include "std_polyfills.h"
#include "NotImplementedException.h"

namespace CmdCalculator::MathAst
{
	/// \brief A node holding a binary operator.
	/// \tparam StringT The string type to use.
	template<String StringT>
	class DynamicBinaryOperatorNode :
		public DynamicExpressionPartNode<StringT>
	{
	public:
		using StringType = DynamicExpressionPartNode<StringT>::StringType;

	private:
		using CharType = typename StringType::value_type;

		const EBinaryOperator m_operatorKind;
		const StringType m_leadingTrivia;
		const StringType m_trailingTrivia;


		CharType getOperatorChar() const
		{
			switch (m_operatorKind)
			{
			case EBinaryOperator::Addition:
				return convertChar<CharType>('+');
			case EBinaryOperator::Subtraction:
				return convertChar<CharType>('-');
			case EBinaryOperator::Multiplication:
				return convertChar<CharType>('*');
			case EBinaryOperator::Division:
				return convertChar<CharType>('/');
			case EBinaryOperator::Exponentiation:
				return convertChar<CharType>('^');
			case EBinaryOperator::NthRoot:
				return convertChar<CharType>('_');
			case EBinaryOperator::Modulo:
				return convertChar<CharType>('%');
			default:
				Polyfills::unreachable();
				break;
			}
		}


	public:

		virtual ~DynamicBinaryOperatorNode() = default;


		DynamicBinaryOperatorNode(const EBinaryOperator operatorKind, const StringType leadingTrivia, const StringType trailingTrivia) :
			m_operatorKind{ operatorKind },
			m_leadingTrivia{ leadingTrivia },
			m_trailingTrivia{ trailingTrivia }
		{}


		inline bool isBinaryOperator() const
		{
			return true;
		}


		/// \brief Accessor to the kind of operator the node holds.
		/// \returns The operator kind.
		EBinaryOperator getOperatorKind() const
		{
			return m_operatorKind;
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
				+ getOperatorChar()
				+ static_cast<StdStringType>(getTrailingTrivia())
			);
		}
	};
}