#pragma once

#include <memory>
#include <string>

#include "DynamicUnaryOperationNode.h"
#include "strings.h"
#include "NotImplementedException.h"

using namespace std::string_literals;

namespace CmdCalculator::MathAst
{
	/// \brief A sign operation.
	/// \tparam StringT The string type to use.
	template<String StringT>
	class DynamicSignOperationNode :
		public DynamicUnaryOperationNode<StringT>
	{
	public:

		using StringType = DynamicOperandNode<StringT>::StringType;


	private:
		using CharType = typename StringType::value_type;

		const bool m_isPositive;


	protected:

		StringType getOperatorStringRepresentation() const override
		{
			return static_cast<StringType>(convertString<CharType>(isPositive() ? "+"s : "-"s));
		}


	public:

		virtual ~DynamicSignOperationNode() = default;


		DynamicSignOperationNode
		(
			std::unique_ptr<DynamicOperandNode<StringType>> operand,
			const bool isPositive,
			const StringType innerTrivia,
			const StringType leadingTrivia,
			const StringType trailingTrivia
		) :
			DynamicUnaryOperationNode<StringType>
			(
				true,
				std::move(operand),
				innerTrivia,
				leadingTrivia,
				trailingTrivia
			),
			m_isPositive{ isPositive }
		{}


		/// \brief Tests if the sign expression is positive or negative.
		/// \returns True if the sign expression is positive, false if it's negative.
		bool isPositive() const
		{
			return m_isPositive;
		}
	};
}