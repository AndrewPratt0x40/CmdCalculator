#pragma once

#include <string>
#include <assert.h>

#include "DynamicUnaryOperationNode.h"
#include "strings.h"
#include "NotImplementedException.h"

using namespace std::string_literals;

namespace CmdCalculator::MathAst
{
	/// \brief A square root operation.
	/// \tparam StringT The string type to use.
	template<String StringT>
	class DynamicSqrtOperationNode :
		public DynamicUnaryOperationNode<StringT>
	{
	public:

		using StringType = DynamicOperandNode<StringT>::StringType;


	private:
		using CharType = typename StringType::value_type;


	protected:

		StringType getOperatorStringRepresentation() const override
		{
			return static_cast<StringType>(convertString<CharType>("sqrt"s));
		}


	public:

		virtual ~DynamicSqrtOperationNode() = default;


		DynamicSqrtOperationNode
		(
			std::unique_ptr<DynamicOperandNode<StringType>> operand,
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
			assert(DynamicUnaryOperationNode<StringType>::getOperand());
		}
	};
}