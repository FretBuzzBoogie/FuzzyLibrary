#pragma once
#include <iostream>
#include "FuzzyString\FuzzyString.h"
#include "FuzzyList\FuzzyList.h"
#include "FuzzyDelegate\FuzzyDelegate.h"
#include "FuzzyDelegate\FuzzyAction.h"

using namespace FuzzyLib;
using namespace std;

class doFuzzyList : public FuzzyList<string*>
{
	public:

		doFuzzyList(const std::initializer_list<string*>& a_initList) : FuzzyList<string*>(a_initList)
		{
		}

	//Logs the contents of the List.
	virtual void DebugLog() override
	{
		std::cout << "\nCount : " << GetCount() << "..... Size :: " << GetCapacity() << "\n";
		string* l_currObjPtr = nullptr;
		for (int l_iListIndex = 0; l_iListIndex < GetCount(); l_iListIndex++)
		{
			l_currObjPtr = GetAtIndex(l_iListIndex);
			if (l_currObjPtr != nullptr)
			{
				std::cout << "Index Value::" << *l_currObjPtr << "\n";
			}
		}
	}
};

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
<<<<<<< HEAD
=======

		static int Multiply(int a, int b)
		{
			return a * b;
		}
		
>>>>>>> 3a362fd0bbc11ddde03c53f64452ed5117124cd7

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
<<<<<<< HEAD
	FuzzyDelegate<int(int)> fuzzDele;
	fuzzDele.Add<doClass, &doClass::printThis1>(&testDoClass);
	fuzzDele.Add<doClass, &doClass::printThis2>(&testDoClass);
	fuzzDele.Add<&doClass::printThis3>();
	fuzzDele.Add <&printThis4>();
	fuzzDele.Invoke(6);

	fuzzDele.Clear();
	fuzzDele.Invoke(3);
=======
	FuzzyDelegate<int(int, int)> fuzzDele;
	fuzzDele.Add<doClass, &doClass::Subtract>(&testDoClass);
	fuzzDele.Add<doClass, &doClass::Add>(&testDoClass);
	cout<<"Printing result ::"<<fuzzDele.Invoke(5, 2);
	fuzzDele.DebugLog();

>>>>>>> 3a362fd0bbc11ddde03c53f64452ed5117124cd7
	system("pause");
	return 0;
}