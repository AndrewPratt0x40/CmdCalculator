#pragma once

#include "DynamicOperandNode.h"
#include "strings.h"
#include "NotImplementedException.h"

#include <concepts>
#include <ranges>
#include <utility>

namespace CmdCalculator::MathAst
{
	/// \brief A node that holds an expression inside of it.
	/// \tparam StringT The string type to use.
	/// \tparam IntT The type to use to store integers.
	template<String StringT, std::integral IntT>
	class DynamicNumberLiteralNode :
		public DynamicOperandNode<StringT>
	{
	public:

		using StringType = DynamicOperandNode<StringT>::StringType;

		using IntType = IntT;


		/// \brief Accessor to the whole part of the number.
		/// \returns The whole part of the number as an integer. This is the portion of the number to the left of the decimal point.
		/// \example The whole part of the number <tt>7</tt> is <tt>7</tt>.
		/// \example The whole part of the number <tt>7.</tt> is <tt>7</tt>.
		/// \example The whole part of the number <tt>.7</tt> is <tt>0</tt>.
		/// \example The whole part of the number <tt>123.456</tt> is <tt>123</tt>.
		IntT getWholePart() const
		{
			throw NotImplementedException{};
		}


		/// \brief Accessor to the fractional part of the number.
		/// \returns The fractional part of the number as an integer. This is the portion of the number to the right of the decimal point.
		/// \example The fractional part of the number <tt>7</tt> is <tt>0</tt>.
		/// \example The fractional part of the number <tt>7.</tt> is <tt>0</tt>.
		/// \example The fractional part of the number <tt>.7</tt> is <tt>7</tt>.
		/// \example The fractional part of the number <tt>123.456</tt> is <tt>123</tt>.
		IntT getFractionalPart() const
		{
			throw NotImplementedException{};
		}


		/// \brief Tests if the number includes a decimal point.
		/// \returns True if the number includes a decimal point, false otherwise.
		bool isDecimalPointVisible() const
		{
			throw NotImplementedException{};
		}


		/// \brief Tests if the number includes a whole part.
		/// \returns True if the number includes a whole part, false otherwise.
		bool isWholePartVisible() const
		{
			throw NotImplementedException{};
		}


		/// \brief Tests if the number includes a fractional part.
		/// \returns True if the number includes a fractional part, false otherwise.
		bool isFractionalPartVisible() const
		{
			throw NotImplementedException{};
		}


		StringT getLeadingTrivia() const override
		{
			throw NotImplementedException{};
		}


		StringT getTrailingTrivia() const override
		{
			throw NotImplementedException{};
		}


		StringT getStringRepresentation() const override
		{
			throw NotImplementedException{};
		}
	};
}