#pragma once

#include "FuzzyString.h"

namespace FuzzyLib
{
	//////////PRIVATE VARIABLES//////////
	const char FuzzyString::NULL_TERMINATOR = '\0';

	//////////PUBLIC VARIABLES//////////


	//////////PRIVATE SOURCE//////////

	//Allocates memory if input string length is greater than the current capacity
	////Else uses the previously allocated memory
	//Sets capacity to twice the current capacity if input string length is less than twice the curreent capacity
	////Else the length of the input string is the new capacity
	//Sets the input cptr to the internal FuzzyString cptr array
	//Sets the cptr to m_cptrStrArr appropriately by assigning data
	void FuzzyString::AllocateAndAssignStr(const char a_cptrInput[])
	{
		int l_iSizeToAssign = GetSizeOfPointedData(a_cptrInput) + 1;
		int l_iDoubleTheCapacity = 2 * m_iCapacity;
		if (l_iSizeToAssign > m_iCapacity)
		{
			delete []m_cptrStrArr;
			m_cptrStrArr = nullptr;

			if (l_iDoubleTheCapacity < l_iSizeToAssign)
			{
				m_cptrStrArr = new char[l_iSizeToAssign];
				m_iCapacity = l_iSizeToAssign;
			}
			else
			{
				m_cptrStrArr = new char[l_iDoubleTheCapacity];
				m_iCapacity = l_iDoubleTheCapacity;
			}
		}
		m_iSize = l_iSizeToAssign;
		memcpy_s(m_cptrStrArr, m_iCapacity, a_cptrInput, m_iSize);
	}

	///Gets the length of the array
	int FuzzyString :: GetSizeOfPointedData(const char a_cptr[])
	{
		int l_iMultiplier = 1;
		int l_iSize = 0;
		int l_iSizeToCheck = 1000;
		do
		{
			l_iSizeToCheck *= l_iMultiplier;
			l_iSize = strnlen_s(a_cptr, l_iSizeToCheck);
			l_iMultiplier++;
		} while (l_iSize >= l_iSizeToCheck);

		return l_iSize;
	}

	//////////PUBLIC SOURCE//////////

#pragma region Constructors

	//Constructor to initialize the char ptr into the internal char array
	FuzzyString::FuzzyString(const char a_cInputArr[] = FuzzyString::NULL_TERMINATOR)
	{
		AllocateAndAssignStr(a_cInputArr);
	}

	//Constructor to initialize the string into the internal char array
	FuzzyString::FuzzyString(const std::string &a_strInput)
	{
		const char* l_cptrStrInput = a_strInput.c_str();
		AllocateAndAssignStr(l_cptrStrInput);
	}

#pragma endregion Constructors

	//Destructor to Destroy the FuzzyString Array
	FuzzyString::~FuzzyString()
	{
		delete [] m_cptrStrArr;
	}

#pragma region Overriding

	//Overides <<
	std::ostream& operator<<(std::ostream& out, const FuzzyString& a_FuzzyStr)
	{
		out << a_FuzzyStr.m_cptrStrArr;
		return out;
	}

	//Overides >>
	std::istream& operator >> (std::istream& in, const FuzzyString& a_FuzzyStr)
	{
		in >> a_FuzzyStr.m_cptrStrArr;
		return in;
	}

	//Overides FuzzyString = cArray
	void FuzzyString:: operator=(const char a_cptrInput[])
	{
		AllocateAndAssignStr(a_cptrInput);
	}

	//Overides FuzzyString = std::string
	void FuzzyString:: operator=(const std::string& a_strInput )
	{
		AllocateAndAssignStr(a_strInput.c_str());
	}

#pragma endregion Overriding

#pragma region Getters

	//Returns the capacity of internal char array
	int FuzzyString::GetCapacity() const
	{
		return m_iCapacity;
	}

	//Returns the size of internal char array
	int FuzzyString::GetSize() const
	{
		return m_iSize;
	}

	//Returns the Empty char
	char* FuzzyString::GetEmpty() const
	{
		return NULL_TERMINATOR;
	}

	//Returns the Null terminator char
	char* FuzzyString::GetNullTerminator() const
	{
		return NULL_TERMINATOR;
	}

#pragma endregion Getters

	void FuzzyString::DebugLog()
	{
		std::cout << "FuzzyString ::'" << *this << "', Size::" <<
			m_iSize << ", Capacity::" << m_iCapacity << "\n";
	}
}















