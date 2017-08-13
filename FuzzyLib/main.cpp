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

		int Add(int a, int b)
		{
			return a + b;
		}

		int Subtract(int a, int b)
		{
			return a - b;
		}

		static int Multiply(int a, int b)
		{
			return a * b;
		}
		

		/*void TestThis()
		{
			doClass testDoClass;
			FuzzyDelegate <int(int, int)> doDele;
			auto d = decltype(doDele)::Create<doClass, &doClass::Subtract>(&testDoClass);
		}*/
};

int main(int argc, char** argv)
{
	doClass testDoClass;
	FuzzyDelegate<int(int, int)> fuzzDele;
	fuzzDele.Add<doClass, &doClass::Subtract>(&testDoClass);
	fuzzDele.Add<doClass, &doClass::Add>(&testDoClass);
	cout<<"Printing result ::"<<fuzzDele.Invoke(5, 2);
	fuzzDele.DebugLog();

	system("pause");
	return 0;
}