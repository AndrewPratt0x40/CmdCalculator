#pragma once

#include <memory>

#include "DynamicUnaryOperationNode.h"
#include "strings.h"
#include "NotImplementedException.h"

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

	protected:

		StringType getOperatorStringRepresentation() const override
		{
			throw NotImplementedException{};
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
			)
		{
			throw NotImplementedException{};
		}


		/// \brief Tests if the sign expression is positive or negative.
		/// \returns True if the sign expression is positive, false if it's negative.
		bool isPositive() const
		{
			throw NotImplementedException{};
		}
	};
}