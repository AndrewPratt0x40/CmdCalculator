#pragma once

#include <memory>
#include <assert.h>

#include "DynamicOperandNode.h"
#include "strings.h"
#include "NotImplementedException.h"

namespace CmdCalculator::MathAst
{
	/// \brief A unary operation.
	/// \tparam StringT The string type to use.
	template<String StringT>
	class DynamicUnaryOperationNode :
		public DynamicOperandNode<StringT>
	{
	public:

		using StringType = DynamicOperandNode<StringT>::StringType;


	private:
		const bool m_isOperatorOnLeftOfOperand;
		const std::unique_ptr<DynamicOperandNode<StringType>> m_operand;
		const StringType m_innerTrivia;
		const StringType m_leadingTrivia;
		const StringType m_trailingTrivia;


	protected:

		DynamicUnaryOperationNode
		(
			const bool isOperatorOnLeftOfOperand,
			std::unique_ptr<DynamicOperandNode<StringType>> operand,
			const StringType innerTrivia,
			const StringType leadingTrivia,
			const StringType trailingTrivia
		) :
			m_isOperatorOnLeftOfOperand{ isOperatorOnLeftOfOperand },
			m_operand{ std::move(operand) },
			m_innerTrivia{ innerTrivia },
			m_leadingTrivia{ leadingTrivia },
			m_trailingTrivia{ trailingTrivia }
		{
			assert(m_operand);
		}


		virtual StringType getOperatorStringRepresentation() const = 0;


	public:


		virtual ~DynamicUnaryOperationNode()
		{}


		/// \brief Accessor to the operand of the operation.
		/// \returns The single operand of the operation.
		virtual DynamicOperandNode<StringType>* getOperand() const
		{
			return m_operand.get();
		}
		
		
		/// \brief Accessor to the inner trivia of the operation.
		/// \returns The trivia content between the operator and it's operand.
		virtual StringType getInnerTrivia() const
		{
			return m_innerTrivia;
		}


		virtual StringType getLeadingTrivia() const override
		{
			return m_leadingTrivia;
		}


		virtual StringType getTrailingTrivia() const override
		{
			return m_trailingTrivia;
		}


		virtual StringType getStringRepresentation() const override
		{
			using StdStringType = std::basic_string<typename StringType::value_type>;

			return static_cast<StringType>
			(
				static_cast<StdStringType>(getLeadingTrivia())
				+ static_cast<StdStringType>
				(
					m_isOperatorOnLeftOfOperand
					? (
						static_cast<StdStringType>(getOperatorStringRepresentation())
						+ static_cast<StdStringType>(getInnerTrivia())
						+ static_cast<StdStringType>(getOperand()->getStringRepresentation())
					)
					: (
						static_cast<StdStringType>(getOperand()->getStringRepresentation())
						+ static_cast<StdStringType>(getInnerTrivia())
						+ static_cast<StdStringType>(getOperatorStringRepresentation())
					)
				)
				+ static_cast<StdStringType>(getTrailingTrivia())
			);
		}
	};
}