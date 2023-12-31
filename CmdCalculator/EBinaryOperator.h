#pragma once

namespace CmdCalculator::MathAst
{
	/// \brief Enumerates the types of binary operators that may appear in a mathematical abstract syntax tree.
	enum class EBinaryOperator
	{
		Addition,
		Subtraction,
		Multiplication,
		Division,
		Exponentiation,
		NthRoot,
		Modulo
	};
}