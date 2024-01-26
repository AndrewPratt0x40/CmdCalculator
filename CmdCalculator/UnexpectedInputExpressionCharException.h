#pragma once

#include <string>
#include <ranges>
#include <concepts>
#include <vector>
#include <optional>

#include "InvalidInputExpressionException.h"
#include "NotImplementedException.h"

namespace CmdCalculator
{
	/// \brief An exception that is thrown when an unexpected character is encountered in an input expression.
	class UnexpectedInputExpressionCharException : public InvalidInputExpressionException
	{
	private:
		const size_t m_charIndex;
		const std::vector<std::string> m_expectedValues;


	public:
		
		/// \brief Creates a new instance of the \ref UnexpectedInputExpressionCharException class.
		/// \tparam ExpectedValuesT The type of \p expectedValues.
		/// \param charIndex The index of the unexpected character.
		/// \param expectedValues A range of string descriptions of each possible value that was expected.
		template<std::ranges::input_range ExpectedValuesT>
			requires std::same_as<std::string, std::ranges::range_value_t<ExpectedValuesT>>
		UnexpectedInputExpressionCharException
		(
			const size_t charIndex,
			ExpectedValuesT&& expectedValues
		) :
			m_charIndex{ charIndex },
			m_expectedValues{ std::ranges::begin(expectedValues), std::ranges::end(expectedValues) }
		{}


		/// \brief Creates a new instance of the \ref UnexpectedInputExpressionCharException class.
		/// \param charIndex The index of the unexpected character.
		UnexpectedInputExpressionCharException
		(
			const size_t charIndex
		);


		virtual ~UnexpectedInputExpressionCharException() = default;


		/// \brief Accessor to the index of the unexpected character.
		/// \returns The unexpected character's index.
		size_t getCharIndex() const;


		/// \brief Accessor to the index of the unexpected character.
		/// \returns The unexpected character's index.
		std::ranges::input_range auto getExpectedValues() const
		{
			return m_expectedValues | std::views::all;
		}


		const char* what() const noexcept override;
	};
}