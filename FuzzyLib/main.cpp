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


	FuzzyList<std::string> strListEmptyTest;
	FuzzyList<std::string> strlist = { WelcomeHome,Hello,Gregard,MrDodo, Schilling };

	strListEmptyTest.Add(Schilling);
	strListEmptyTest.AddRange(strlist);
	strlist.DebugLog();

	strlist.Remove(666);
	strlist[-1];

	std::cout << "Retrieving data at index 2 ::" << strlist[1] << "\n";

	strlist.Remove(3);
	strlist.Remove(3);
	strlist.DebugLog();
	
	system("pause");
	return 0;
}