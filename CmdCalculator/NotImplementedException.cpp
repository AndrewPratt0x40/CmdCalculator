#include "NotImplementedException.h"


const char* CmdCalculator::NotImplementedException::what() const noexcept
{
	return "Code that has not been implemented has been invoked";
}