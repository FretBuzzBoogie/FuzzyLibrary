#pragma once
#include <iostream>
#include "FuzzyString\FuzzyString.h"
int main()
{
	using namespace FuzzyLib;
	
	FuzzyString FuzzyResult = "Result";
	FuzzyString Fuzzya = "abcd";
	FuzzyString Fuzzyb = "efgh";
	FuzzyString Fuzzyc = "ijkl";
	
	FuzzyResult = Fuzzya + Fuzzyb + Fuzzyc;
	FuzzyResult.DebugLog();

	system("pause");
	return 0;
}