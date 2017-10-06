#pragma once
#include <iostream>
#include "FuzzyString\FuzzyString.h"
#include "FuzzyList\FuzzyList.h"
#include "FuzzyDelegate\FuzzyDelegate.h"

using namespace FuzzyLib;
using namespace std;

class doClass
{
	public:
		int printThis1(int)
		{
			cout << "Printing 111 ... member func\n";
			return 0;
		}

		int printThis2(int) const
		{
			cout << "Printing 222 ... const member func\n";
			return 0;
		}

		static int printThis3(int)
		{
			cout << "Printing 333 ... static member func\n";
			return 0;
		}
};

int printThis4(int)
{
	cout << "Printing 444 ... global func\n";
	return 0;
}

int main(int argc, char** argv)
{
	doClass testDoClass;
	FuzzyDelegate<int(int)> fuzzDele;
	fuzzDele.Add<doClass, &doClass::printThis1>(&testDoClass);
	fuzzDele.Add<doClass, &doClass::printThis2>(&testDoClass);
	fuzzDele.Add<&doClass::printThis3>();
	fuzzDele.Add <&printThis4>();
	fuzzDele(6);

	fuzzDele.Clear();
	fuzzDele(3);
	system("pause");
	return 0;
}