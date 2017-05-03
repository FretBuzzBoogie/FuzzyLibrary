#pragma once
#include <iostream>
#include "FuzzyString\FuzzyString.h"
#include "FuzzyList\FuzzyList.h"

int main()
{
	using namespace FuzzyLib;
	FuzzyString* fuzzStr = new FuzzyString("doIt123");
	fuzzStr->DebugLog();

	std::string WelcomeHome = "WelcomeHome";
	std::string* ptrWelcomeHome = &WelcomeHome;

	std::string Hello = "Hello";
	std::string* ptrHello = &Hello;

	std::string MyFriend = "MyFriend";
	std::string* ptrMyFriend = &MyFriend;

	std::string Gregard = "Gregard";
	std::string* ptrGregard = &MyFriend;

	std::string Schilling = "Schilling";
	std::string* ptrSchilling = &Schilling;

	FuzzyList<std::string*> strlist{ ptrWelcomeHome,ptrMyFriend };
	strlist.DebugLog();
	
	strlist.Add(ptrGregard);
	strlist.Add(ptrSchilling);
	strlist.DebugLog();

	
	std::string doHello = "doHello";
	std::string* ptrdoHello = &doHello;

	std::string doMyFriend = "doMyFriend";
	std::string* ptrdoMyFriend = &doMyFriend;

	std::string doGregard = "doGregard";
	std::string* ptrdoGregard = &doMyFriend;

	std::string doSchilling = "doSchilling";
	std::string* ptrdoSchilling = &doSchilling;

	FuzzyList<std::string*> *strlist2 = new FuzzyList<std::string*>{ ptrdoHello,ptrdoMyFriend,ptrdoGregard,ptrdoSchilling };

	strlist.AddRange(*strlist2);

	strlist.DebugLog();

	strlist.Clear();

	strlist.DebugLog();

	std::string doDiaz = "doDiaz";
	std::string* ptrdoDiaz = &doDiaz;

	strlist.Add(ptrdoDiaz);
	strlist.DebugLog();
	strlist.AddRange(*strlist2);
	strlist.DebugLog();

	*strlist[3] = "George";
	strlist.DebugLog();
	

	system("pause");
	return 0;
}