#pragma once
#include <iostream>
#include "FuzzyString\FuzzyString.h"
#include "FuzzyList\FuzzyList.h"

	using namespace FuzzyLib;

FuzzyList<std::string> GetNewFuzzyList()
{
	std::string Gamma1 = "Gamma1";

	std::string Delta1 = "Delta1";

	std::string Zeta = "Zeta";
	FuzzyList<std::string> l_Fuzz = { Zeta, Delta1, Gamma1 };
	return l_Fuzz;
}

int main(int argc, char** argv)
{
	
	std::string Alpha = "Alpha";
	std::string* ptrAlpha = &Alpha;

	std::string Beta = "Beta";
	std::string* ptrBeta = &Beta;

	std::string Gamma = "Gamma";
	std::string* ptrGamma = &Gamma;

	std::string Delta = "Delta";
	std::string* ptrDelta = &Delta;

	std::string Alpha1 = "Alpha1";
	std::string* ptrAlpha1 = &Alpha1;

	std::string Beta1 = "Beta1";
	std::string* ptrBeta1 = &Beta1;

	std::string Gamma1 = "Gamma1";
	std::string* ptrGamma1 = &Gamma1;

	std::string Delta1 = "Delta1";
	std::string* ptrDelta1 = &Delta1;

	std::string Zeta = "Zeta";
	std::string* ptrZeta = &Zeta;

	FuzzyList<std::string> l_list1 = { Alpha, Beta, Gamma, Delta };
	
	l_list1 = FuzzyList<std::string>(GetNewFuzzyList());
	l_list1.DebugLog();
	FuzzyList<std::string> l_list2(l_list1);
	system("pause");
	return 0;
}