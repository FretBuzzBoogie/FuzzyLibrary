#pragma once
#include <iostream>
#include "FuzzyString\FuzzyString.h"
int main()
{
	using namespace FuzzyLib;
	FuzzyString l_str("Rohan Fernandez");
	l_str.DebugLog();
	l_str = "Somebody i used to knowSomebody i used to know";
	l_str.DebugLog();
	l_str = "Somebody";
	l_str.DebugLog();
	system("pause");
	return 0;
}