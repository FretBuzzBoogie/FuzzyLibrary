#pragma once
#include <iostream>
#include "FuzzyString\FuzzyString.h"
int main()
{
	using namespace FuzzyLib;
	std::cout << "\nChar Ptr\n";
	FuzzyString FuzzStr1 = "CharacterPointerAttempt";
	FuzzStr1.DebugLog();

	std::cout << "\nString\n";
	std::string StdString = "StdStringPointerAttempt";
	FuzzyString FuzzStr2 = StdString;
	FuzzStr2.DebugLog();

	std::cout << "\nFuzzyString\n";
	FuzzyString FuzzTest("FuzzTestAttempt");
	FuzzyString FuzzString = FuzzTest;
	FuzzString.DebugLog();

	std::cout << "\n\n\n";

	system("pause");
	return 0;
}