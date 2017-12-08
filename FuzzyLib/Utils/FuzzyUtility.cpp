#pragma once
#include "FuzzyUtility.h"

namespace FuzzyUtility
{
	std::unique_ptr<char[]> IntToChar(int a_Int)
	{
		int l_iAbsNum = a_Int;
		int l_iNumberOfDigits = 0;
		int l_iUnit = 1;
		bool l_bIsNegative = false;

		if (l_iAbsNum < 0)
		{
			l_bIsNegative = true;
			l_iAbsNum = -l_iAbsNum;
		}

		do
		{
			l_iNumberOfDigits++;
			l_iUnit *= 10;
		} while (l_iAbsNum >= l_iUnit);

		const int l_iArraySize = l_bIsNegative ? l_iNumberOfDigits + 2 : l_iNumberOfDigits + 1;

		std::unique_ptr<char[]>l_return(std::make_unique<char[]>(l_iArraySize));

		int l_iNullTerminatorIndex = l_iArraySize - 1;
		l_return[l_iNullTerminatorIndex] = '\0';

		int i_lAssignStart = 0;
		if (l_bIsNegative)
		{
			i_lAssignStart = 1;
			l_return[0] = '-';
		}

		int l_iCurrentDigit = l_iNumberOfDigits;
		for (int l_iArrayIndex = i_lAssignStart; l_iArrayIndex < l_iNullTerminatorIndex; l_iArrayIndex++)
		{
			int l_iCurrentUnit = std::pow(10, l_iCurrentDigit - 1);
			l_return[l_iArrayIndex] = '0' + (l_iAbsNum / l_iCurrentUnit);
			l_iCurrentDigit--;
			l_iAbsNum %= l_iCurrentUnit;
		}

		return l_return;
	}
}