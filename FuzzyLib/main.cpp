#pragma once
#include <iostream>
#include "FuzzyString\FuzzyString.h"
#include "FuzzyList\FuzzyList.h"

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

int main(int argc, char** argv)
{
	string first = "first";
	string *pfirst = &first;

	string second = "second";
	string *psecond = &second;

	string third = "third";
	string *pthird = &third;

	string fourth = "fourth";
	string *pfourth = &fourth;

	string fifth = "fifth";
	string *pfifth = &fifth;

	string sixth = "sixth";
	string *psixth = &sixth;

	string seventh = "seventh";
	string *pseventh = &seventh;

	string eighth = "eighth";
	string *peighth = &eighth;

	string ninth = "ninth";
	string *pninth = &ninth;

	string tenth = "tenth";
	string *ptenth = &tenth;

	FuzzyList<string> l_fuzz = { first,second,third,fourth,fifth };
	FuzzyList<string> l_fuzz1 = { sixth,seventh,eighth,ninth,tenth };

	doFuzzyList l_fuzzPtr = { pfirst,psecond,pthird,pfourth,pfifth };
	doFuzzyList l_fuzzPtr1 = { psixth,pseventh,peighth,pninth,ptenth };

	string doThisNow = "doThisNow";
	string* pdoThisNow = &doThisNow;

	l_fuzzPtr.AddRange(l_fuzzPtr1);

	l_fuzzPtr.Add(pdoThisNow);


	l_fuzzPtr.DebugLog();

	system("pause");
	return 0;
}