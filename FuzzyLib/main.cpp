#pragma once
#include <iostream>
#include "FuzzyString\FuzzyString.h"
#include "FuzzyList\FuzzyList.h"
#include "FuzzyDelegate\FuzzyDelegate.h"
#include "FuzzyEvent\FuzzyEvent.h"
#include "FuzzyEvent\EventSystem.h"
#include "FuzzyEvent\EventHandler.h"

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

	///testing fuzzy list
	string *Do1 = &string("hello");
	string *Do2 = &string("my");
	string *Do3 = &string("name");
	string *Do4 = &string("is");
	string *Do5 = &string("paul");

	{
		FuzzyList<string*> l_FuzzString = { Do1 ,Do2 ,Do3 ,Do4 ,Do5 };

		l_FuzzString.DebugLog();

	}

	cout << "string 1 :: '"<<Do2<<"'\n";

	///testing fuzzy delegates
	doClass testDoClass;
	FuzzyDelegate<int(int)> fuzzDele;
	fuzzDele.Add<doClass, &doClass::printThis1>(&testDoClass);
	fuzzDele.Add<doClass, &doClass::printThis2>(&testDoClass);
	fuzzDele.Add<&doClass::printThis3>();
	fuzzDele.Add <&printThis4>();
	fuzzDele(6);

	fuzzDele.Clear();
	fuzzDele(3);


	//testing fuzzy events

	InputEvent m_InputEvt;
	InputListener m_InputListener;
	InputListener m_InputListener1;

	EventSystem* const l_eventSystem = EventSystem::GetInstance();

	EventHandler* l_eventHandler1 = new EventHandler();
	
	l_eventSystem->DebugLog();

	EventHandler* l_eventHandler2 = new EventHandler();

	l_eventHandler1->AddListener(m_InputEvt, m_InputListener);
	l_eventHandler1->DebugLog();
	std::cout << "\n\n\n\n";

	l_eventHandler2->AddListener<InputEvent>(m_InputListener1);
	l_eventHandler2->DebugLog();

	EventSystem::Fire(m_InputEvt);

	delete l_eventHandler1;
	l_eventSystem->DebugLog();

	delete l_eventHandler2;
	l_eventSystem->DebugLog();

	EventSystem::Destroy();

	system("pause");
	return 0;
}