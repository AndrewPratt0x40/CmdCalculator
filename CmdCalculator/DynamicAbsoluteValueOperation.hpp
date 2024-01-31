#include "DynamicAbsoluteValueOperation.h"
#include "NotImplementedException.h"


#pragma push_macro("THIS_NUMBER_TYPE")
#define THIS_NUMBER_TYPE CmdCalculator::Expressions::DynamicAbsoluteValueOperation<NumberT>::NumberType
#pragma push_macro("THIS_NUMBER_TYPENAME")
#define THIS_NUMBER_TYPENAME typename THIS_NUMBER_TYPE


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicAbsoluteValueOperation<NumberT>::DynamicAbsoluteValueOperation(std::unique_ptr<DynamicExpression<NumberType>> operand)
{
	throw NotImplementedException{};
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicAbsoluteValueOperation<NumberT>::~DynamicAbsoluteValueOperation() = default;


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicExpression<THIS_NUMBER_TYPENAME>&
	CmdCalculator::Expressions::DynamicAbsoluteValueOperation<NumberT>::getOperand() const
{
	throw NotImplementedException{};
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline bool CmdCalculator::Expressions::DynamicAbsoluteValueOperation<NumberT>::isSimplifiable() const
{
	throw NotImplementedException{};
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicExpressionBox<THIS_NUMBER_TYPENAME>
	CmdCalculator::Expressions::DynamicAbsoluteValueOperation<NumberT>::getFullSimplification() const
{
	throw NotImplementedException{};
}


#pragma pop_macro("THIS_NUMBER_TYPE")
#pragma pop_macro("THIS_NUMBER_TYPENAME")