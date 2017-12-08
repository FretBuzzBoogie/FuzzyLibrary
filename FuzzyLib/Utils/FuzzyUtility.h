#pragma once
#include <cmath>
#include <memory>

namespace FuzzyUtility
{
	//Converts an integer to a char*
	extern std::unique_ptr<char[]> IntToChar(int a_Int);
}