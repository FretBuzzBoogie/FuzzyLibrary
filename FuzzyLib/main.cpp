#pragma once
#include <iostream>
#include "FuzzyString\FuzzyString.h"
#include "FuzzyList\FuzzyList.h"

using namespace FuzzyLib;
using namespace std;

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

	l_fuzz.DebugLog();

	FuzzyList<string*> l_fuzzPtr = { pfirst,psecond,pthird,pfourth,pfifth };
	FuzzyList<string*> l_fuzzPtr1 = { psixth,pseventh,peighth,pninth,ptenth };

	string doThisNow = "doThisNow";

	l_fuzz.AddRange(l_fuzz1);

	l_fuzz.Add(doThisNow);


	l_fuzz.DebugLog();

	system("pause");
	return 0;
}