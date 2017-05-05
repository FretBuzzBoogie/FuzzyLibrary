#pragma once
#include <iostream>
#include "FuzzyString\FuzzyString.h"
#include "FuzzyList\FuzzyList.h"

int main(int argc, char** argv)
{
	using namespace FuzzyLib;
	
	FuzzyString l_str;
	FuzzyString l_str1("HailTheReaper::");
	l_str.DebugLog();
	l_str += l_str1 + 666;
	l_str.DebugLog();

	system("pause");
	return 0;
}