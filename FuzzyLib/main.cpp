#pragma once
#include "FuzzyString\FuzzyString.h"

int main(int argc, char* argv[])
{
	using namespace FuzzyLib;
	
	FuzzyString FuzzyResult = "Result";
	FuzzyString Fuzzya = "abcd";
	FuzzyString Fuzzyb = "efgh";
	std::string Fuzzyc = "ijkl";
	
	FuzzyResult = Fuzzya + Fuzzyb + Fuzzyc;
	FuzzyResult.DebugLog();

	std::cin >> FuzzyResult;

	FuzzyResult.DebugLog();

	system("pause");
	return 0;
}