#pragma once

#include "FuzzyString.h"

namespace FuzzyLib
{
	//////////PRIVATE VARIABLES//////////
	char* const FuzzyString::NULL_TERMINATOR = "\0";

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

			m_cptrStrArr = new char[l_iSizeToAssign];
			m_iCapacity = l_iSizeToAssign;

			/*
			If the a_cptrInput is more than double the size
			allocate the capacity to the size of a_cptrInput 
			else allocate the capacity to double the size of a_cptrInput.

			if (l_iDoubleTheCapacity < l_iSizeToAssign)
			{
				m_cptrStrArr = new char[l_iSizeToAssign];
				m_iCapacity = l_iSizeToAssign;
			}
			else
			{
				m_cptrStrArr = new char[l_iDoubleTheCapacity];
				m_iCapacity = l_iDoubleTheCapacity;
			}*/
		}
		m_iSize = l_iSizeToAssign;
		memcpy_s(m_cptrStrArr, m_iCapacity, a_cptrInput, m_iSize);
	}

	///Gets the length of the array
	int FuzzyString :: GetSizeOfPointedData(const char a_cptr[])
	{
		int l_iMultiplier = 1;
		int l_iSize = 0;
		int l_iSizeToCheck = 50;
		do
		{
			l_iSizeToCheck *= l_iMultiplier;
			l_iSize = strnlen_s(a_cptr, l_iSizeToCheck);
			l_iMultiplier++;
		} while (l_iSize >= l_iSizeToCheck);

		return l_iSize;
	}

	///Returns the result of the concatenation of the 2 char pointers 
	char* FuzzyString::AppendString(const char* a_cptr1, const char* a_cptr2)
	{
		int l_iSize1 = FuzzyString::GetSizeOfPointedData(a_cptr1);
		int l_iSize2 = FuzzyString::GetSizeOfPointedData(a_cptr2);
		int l_iSize = l_iSize1 + l_iSize2 + 1;

		char* l_cptrConcat = new char[l_iSize];

		memcpy_s(l_cptrConcat, l_iSize, a_cptr1, l_iSize);
		strncat_s(l_cptrConcat, l_iSize, a_cptr2, l_iSize2 + 1);
		return l_cptrConcat;
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
		m_cptrStrArr = nullptr;
	}

	//Compares FuzzyString object and another FuzzyString Object
	bool FuzzyString :: IsEqual(const FuzzyString &a_FuzzyString) const
	{
		if (std::strcmp(this->m_cptrStrArr, a_FuzzyString.m_cptrStrArr) == 0)
		{
			return true;
		}
		return false;
	}

	//Compares FuzzyString object and a char pointer
	bool FuzzyString::IsEqual(const char* a_cptrInput) const
	{
		if (std::strcmp(this->m_cptrStrArr, a_cptrInput) == 0)
		{
			return true;
		}
		return false;
	}

	//Compares FuzzyString object and a std::string object
	bool FuzzyString::IsEqual(const std::string& a_strInput) const
	{
		if (std::strcmp(this->m_cptrStrArr, a_strInput.c_str()) == 0)
		{
			return true;
		}
		return false;
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

	//Overides FuzzyString1 = FuzzyString2
	void FuzzyString :: operator=(const FuzzyString& a_FuzzyStringInput)
	{
		this->AllocateAndAssignStr(a_FuzzyStringInput.m_cptrStrArr);
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

	//Overrides FuzzyString1 += FuzzyString2
	void FuzzyString::operator+=(const FuzzyString& a_FuzzyStringInput)
	{
		char* l_cptrConcat = FuzzyString::AppendString(this->m_cptrStrArr, a_FuzzyStringInput.m_cptrStrArr);
		AllocateAndAssignStr(l_cptrConcat);

		delete l_cptrConcat;
		l_cptrConcat = nullptr;
	}

	//Overides FuzzyString += a_cptrInput
	void FuzzyString::operator+=(const char* a_cptrInput)
	{
		char* l_cptrConcat = FuzzyString::AppendString(this->m_cptrStrArr, a_cptrInput);
		AllocateAndAssignStr(l_cptrConcat);

		delete[] l_cptrConcat;
		l_cptrConcat = nullptr;
	}

	//Overides FuzzyString += a_strInput
	void FuzzyString:: operator+=(const std::string& a_strInput)
	{
		char* l_cptrConcat = FuzzyString::AppendString(this->m_cptrStrArr, a_strInput.c_str());
		AllocateAndAssignStr(l_cptrConcat);

		delete[] l_cptrConcat;
		l_cptrConcat = nullptr;
	}

	//Overides a_cptrInput += FuzzyString 
	void operator+=(char* &a_cptrInput, const FuzzyString& a_FuzzyString)
	{
		delete[] a_cptrInput;
		a_cptrInput = FuzzyString::AppendString(a_cptrInput, a_FuzzyString.m_cptrStrArr);
	}

	//Overides a_strInput += FuzzyString 
	void operator+=(std::string &a_strInput, const FuzzyString& a_FuzzyString)
	{
		a_strInput = FuzzyString::AppendString(a_strInput.c_str(), a_FuzzyString.m_cptrStrArr);
	}

	////Overides FuzzyString + a_cptrInput
	//FuzzyString FuzzyString :: operator+(const char a_cptrInput[])
	//{
	//	char* l_charConcat = FuzzyString::AppendString(this->m_cptrStrArr, a_cptrInput);
	//	FuzzyString l_FuzzyString(l_charConcat);

	//	delete[] l_charConcat;
	//	l_charConcat = nullptr;

	//	return l_FuzzyString;
	//}

	////Overides FuzzyString + a_strInput
	//FuzzyString FuzzyString :: operator+(const std::string& a_strInput)
	//{
	//	char* l_charConcat = FuzzyString::AppendString(this->m_cptrStrArr, a_strInput.c_str());
	//	FuzzyString l_FuzzyString(l_charConcat);

	//	delete[] l_charConcat;
	//	l_charConcat = nullptr;

	//	return l_FuzzyString;
	//}

	////Overides FuzzyString + a_FuzzyStringInput
	//FuzzyString FuzzyString :: operator+(const FuzzyString a_FuzzyStringInput)
	//{
	//	char* l_charConcat = FuzzyString::AppendString(this->m_cptrStrArr, a_FuzzyStringInput.m_cptrStrArr);
	//	FuzzyString l_FuzzyString(l_charConcat);

	//	delete[] l_charConcat;
	//	l_charConcat = nullptr;

	//	return l_FuzzyString;
	//}


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
	char* FuzzyString::GetEmpty()
	{
		return NULL_TERMINATOR;
	}

	//Returns the Null terminator char
	char* FuzzyString::GetNullTerminator()
	{
		return NULL_TERMINATOR;
	}

	//Returns the char pointer
	char* FuzzyString :: GetC_Str() const
	{
		return m_cptrStrArr;
	}

#pragma endregion Getters

	void FuzzyString::DebugLog()
	{
		std::cout << "FuzzyString ::'" << *this << "', Size::" <<
			m_iSize << ", Capacity::" << m_iCapacity << "\n";
	}
}