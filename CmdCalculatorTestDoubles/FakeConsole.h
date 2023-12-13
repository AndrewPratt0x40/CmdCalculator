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
		public CmdCalculator::Console_IntendedSatisfaction
	{
	public:
		using StringType = std::basic_string<CharT>;
		using StringViewType = std::basic_string_view<CharT>;

		struct TextSpan
		{
			const StringType text;
			const CmdCalculator::EWriteMode writeMode;

			bool operator==(const TextSpan&) const = default;

			TextSpan(const StringType text, const CmdCalculator::EWriteMode writeMode) :
				text{text},
				writeMode{writeMode}
			{}
		};


	private:
		StringType m_nextInput;
		std::vector<TextSpan> m_textSpans;


	public:
		void FAKE_setNextInput(StringType nextInput)
		{
			m_nextInput = nextInput;
		}


		const StringType FAKE_getNextInput()
		{
			return m_nextInput;
		}


		const auto FAKE_getTextSpans()
		{
			return std::views::all(m_textSpans);
		}


		StringType getInput()
		{
			return m_nextInput;
		}
		

		void write(const StringViewType text, const CmdCalculator::EWriteMode writeMode)
		{
			m_textSpans.push_back(TextSpan{ std::string{text}, writeMode });
		}


		void writeLine(const StringViewType text, const CmdCalculator::EWriteMode writeMode)
		{
			write(std::string{ text } + '\n', writeMode);
		}


		FakeConsole() :
			m_nextInput{},
			m_textSpans{}
		{}


		FakeConsole(StringType nextInput, std::initializer_list<TextSpan> textSpans) :
			m_nextInput{nextInput},
			m_textSpans{textSpans}
		{}
	};
}