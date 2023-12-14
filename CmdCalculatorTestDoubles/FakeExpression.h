#pragma once

#include <concepts>
#include <optional>

#include "../CmdCalculator/NotImplementedException.h"
#include "../CmdCalculator/Expression.h"

namespace CmdCalculatorTestDoubles::Expressions
{
	using FakeExpressionDefaultIdentifierType = int;
	static_assert(std::regular<FakeExpressionDefaultIdentifierType>);


	template<std::regular IdentifierT = FakeExpressionDefaultIdentifierType>
	class FakeExpression :
		public CmdCalculator::Expressions::Expression_IntendedSatisfaction
	{
	public:
		using IdentifierType = IdentifierT;

	private:
		const IdentifierT m_identifier;
		const std::optional<FakeExpression<IdentifierT>> m_fullSimplification;

	public:
		const IdentifierT FAKE_getIdentifier() const
		{
			return m_identifier;
		}

		
		const std::optional<FakeExpression<IdentifierT>> FAKE_getFullSimplification() const
		{
			return m_fullSimplification;
		}


		bool isSimplifiable()
		{
			throw CmdCalculator::NotImplementedException{};
		}


		FakeExpression getFullSimplification()
		{
			throw CmdCalculator::NotImplementedException{};
		}


		FakeExpression(const std::optional<FakeExpression<IdentifierT>> fullSimplification = {}, const IdentifierT identifier = {}) :
			m_identifier{ identifier },
			m_fullSimplification{ fullSimplification }
		{
			throw CmdCalculator::NotImplementedException{};
		}


		FakeExpression(const FakeExpression<IdentifierT>& other) :
			FakeExpression(other.m_identifier, other.m_fullSimplification)
		{}
	};
}