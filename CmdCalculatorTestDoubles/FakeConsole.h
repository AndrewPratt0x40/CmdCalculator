#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <ranges>
#include <initializer_list>

#include "../CmdCalculator/strings.h"
#include "../CmdCalculator/Console.h"


namespace CmdCalculatorTestDoubles
{
	template <class CharT>
	class FakeConsole :
		public ::CmdCalculator::Console_IntendedSatisfaction
	{
	public:
		using StringType = std::basic_string<CharT>;
		using StringViewType = std::basic_string_view<CharT>;

		struct TextSpan
		{
			const StringType text;
			const ::CmdCalculator::EWriteMode writeMode;

			bool operator==(const TextSpan&) const = default;

			TextSpan(const StringType text, const ::CmdCalculator::EWriteMode writeMode) :
				text{text},
				writeMode{writeMode}
			{}
		};


	private:
		StringType m_defaultInput;
		std::vector<StringType> m_nextInputs;
		size_t m_inputCalls{ 0 };
		std::vector<TextSpan> m_textSpans;


	public:
		void FAKE_setDefaultInput(StringType defaultInput)
		{
			m_defaultInput = defaultInput;
		}


		const StringType FAKE_getDefaultInput() const
		{
			return m_defaultInput;
		}


		template<std::ranges::forward_range NextInputsT>
			requires std::same_as<StringType, std::ranges::range_value_t<NextInputsT>>
		void FAKE_setNextInputs(NextInputsT nextInputs)
		{
			m_nextInputs.clear();
			std::ranges::copy(nextInputs, std::back_inserter(m_nextInputs));
		}


		const auto FAKE_getNextInputs() const
		{
			return std::views::all(m_nextInputs);
		}


		const size_t FAKE_getNumberOfCallsTo_getInput() const
		{
			return m_inputCalls;
		}


		const auto FAKE_getTextSpans() const
		{
			return std::views::all(m_textSpans);
		}


		StringType getInput()
		{
			m_inputCalls++;
			if (m_nextInputs.empty())
				return m_defaultInput;

			StringType input{ m_nextInputs.back() };
			m_nextInputs.pop_back();
			return input;
		}
		

		void write(const StringViewType text, const ::CmdCalculator::EWriteMode writeMode)
		{
			m_textSpans.push_back(TextSpan{ std::string{text}, writeMode });
		}


		void writeLine(const StringViewType text, const ::CmdCalculator::EWriteMode writeMode)
		{
			write(std::string{ text } + '\n', writeMode);
		}


		FakeConsole() :
			m_defaultInput{},
			m_nextInputs{},
			m_textSpans{}
		{}


		FakeConsole(StringType defaultInput, std::initializer_list<TextSpan> textSpans) :
			m_defaultInput{ defaultInput },
			m_nextInputs{},
			m_textSpans{ textSpans }
		{}


		template<std::ranges::forward_range NextInputsT>
			requires std::same_as<StringType, std::ranges::range_value_t<NextInputsT>>
		FakeConsole(StringType defaultInput, NextInputsT nextInputs, std::initializer_list<TextSpan> textSpans) :
			FakeConsole(defaultInput, textSpans)
		{
			std::ranges::copy(nextInputs, std::back_inserter(m_nextInputs));
		}
	};
}