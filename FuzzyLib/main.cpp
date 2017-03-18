#pragma once
#include <iostream>
#include "FuzzyString\FuzzyString.h"
int main()
{
	using namespace FuzzyLib;
	FuzzyString l_str("abcd");
	l_str.DebugLog();

	l_str += l_str;
	l_str.DebugLog();

	l_str += "hello";
	l_str.DebugLog();

	FuzzyString l_str1("Hello ");
	FuzzyString l_str2("Friend");
	
	/*l_str = l_str1 + "abcd";*/

	l_str.DebugLog();

	system("pause");
	return 0;
}