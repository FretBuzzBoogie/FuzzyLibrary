#pragma once
#include <iostream>
#include "FuzzyString\FuzzyString.h"
#include "FuzzyList\FuzzyList.h"

int main(int argc, char** argv)
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
	std::string* ptrGregard = &Gregard;

	std::string Schilling = "Schilling";
	std::string* ptrSchilling = &Schilling;

	std::string MrDodo = "MrDodo";
	std::string* ptrMrDodo = &MrDodo;


	FuzzyList<std::string*> strListEmptyTest;
	FuzzyList<std::string*> strlist = { ptrWelcomeHome,ptrHello,ptrGregard,ptrMrDodo, ptrSchilling };

	strListEmptyTest = strlist;
	
	strlist.DebugLog();
	strListEmptyTest.DebugLog();

	*ptrHello = MyFriend;

	strlist.DebugLog();
	strListEmptyTest.DebugLog();



	system("pause");
	return 0;
}