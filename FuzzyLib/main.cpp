#pragma once
#include "FuzzyString\FuzzyString.h"

int main(int argc, char* argv[])
{
	using namespace FuzzyLib;
	FuzzyString* fuzzStr = new FuzzyString("doIt123");
	fuzzStr->DebugLog();

	system("pause");
	return 0;
}