#pragma once

#include "FuzzyString.h"

namespace FuzzyLib
{
	//////////PRIVATE VARIABLES//////////
	char* const FuzzyString::NULL_TERMINATOR = new char('\0');
	const int FuzzyString::MAX_CHAR_EXTRACT = 32767;

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
		if (l_iSizeToAssign > m_iCapacity)
		{
			if (m_cptrStrArr != NULL_TERMINATOR)
			{
				delete m_cptrStrArr;
				m_cptrStrArr = nullptr;
			}

			m_cptrStrArr = new char[l_iSizeToAssign];
			m_iCapacity = l_iSizeToAssign;
		}
		m_iSize = l_iSizeToAssign;
		memcpy_s(m_cptrStrArr, m_iCapacity, a_cptrInput, m_iSize);
	}

	////Gets the length of the array
	int FuzzyString::GetSizeOfPointedData(const char a_cptr[])
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

	////Concatenates a_cptrInput1 + a_cptrInput2 to a FuzzyString
	FuzzyString FuzzyString::Concatenate(const char* a_cptrInput1, const char* a_cptrInput2)
	{
		char* l_charConcat = FuzzyString::AppendString(a_cptrInput1, a_cptrInput2);
		FuzzyString l_FuzzyStr(l_charConcat);
		delete[] l_charConcat;
		l_charConcat = nullptr;

		return l_FuzzyStr;
	}

	////Returns the result of the concatenation of the 2 char pointers 
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

	////Deletes all memory allocated by this class.
	void FuzzyString :: DeleteAllocatedMemory()
	{
		if (m_cptrStrArr != NULL_TERMINATOR && m_cptrStrArr !=nullptr )
		{
			delete[] m_cptrStrArr;
			m_cptrStrArr = nullptr;
		}
	}

	////Copy constructor of FuzzyString to *this by r - value reference
	void FuzzyString::CopyConstructorByValue(FuzzyString& a_FuzzyString)
	{
		DeleteAllocatedMemory();
		m_cptrStrArr = a_FuzzyString.m_cptrStrArr;
		m_iCapacity = a_FuzzyString.m_iCapacity;
		m_iSize = a_FuzzyString.m_iSize;
		a_FuzzyString.m_cptrStrArr = nullptr;
	}

	//////////PUBLIC SOURCE//////////

#pragma region Constructors

	////Default Constructor
	FuzzyString::FuzzyString()
	{
	}

	////Copy constructor
	FuzzyString::FuzzyString(const FuzzyString &a_FuzzyString)
	{
		AllocateAndAssignStr(a_FuzzyString.m_cptrStrArr);
	}

	////Copy constructor for r-value reference by move semantics.
	FuzzyString::FuzzyString(FuzzyString&& a_FuzzyString)
	{
		CopyConstructorByValue(a_FuzzyString);
	}

	////Constructor to initialize the char ptr into the internal char array
	FuzzyString::FuzzyString(const char a_cInputArr[])
	{
		AllocateAndAssignStr(a_cInputArr);
	}

	////Constructor to initialize the string into the internal char array
	FuzzyString::FuzzyString(const std::string &a_strInput)
	{
		const char* l_cptrStrInput = a_strInput.c_str();
		AllocateAndAssignStr(l_cptrStrInput);
	}

	////Constructor that initializes an int
	FuzzyString::FuzzyString(const int &a_intInput)
	{
		char* l_CharConvertedInt = FuzzyUtility::IntToChar(a_intInput);
		*this = l_CharConvertedInt;
		delete[] l_CharConvertedInt;
	}

#pragma endregion Constructors

	////Destructor to Destroy the FuzzyString Array
	FuzzyString::~FuzzyString()
	{
		DeleteAllocatedMemory();
	}

	////Compares FuzzyString object and another FuzzyString Object
	bool FuzzyString::IsEqual(const FuzzyString &a_FuzzyString) const
	{
		if (std::strcmp(this->m_cptrStrArr, a_FuzzyString.m_cptrStrArr) == 0)
		{
			return true;
		}
		return false;
	}

	////Compares FuzzyString object and a char pointer
	bool FuzzyString::IsEqual(const char* a_cptrInput) const
	{
		if (std::strcmp(this->m_cptrStrArr, a_cptrInput) == 0)
		{
			return true;
		}
		return false;
	}

	////Compares FuzzyString object and a std::string object
	bool FuzzyString::IsEqual(const std::string& a_strInput) const
	{
		if (std::strcmp(this->m_cptrStrArr, a_strInput.c_str()) == 0)
		{
			return true;
		}
		return false;
	}

#pragma region Operator Overloading

	////Overloading cout << a_FuzzyStr
	std::ostream& operator<<(std::ostream& out, const FuzzyString& a_FuzzyStr)
	{
		out << a_FuzzyStr.m_cptrStrArr;
		return out;
	}

	////Overloading cin >> a_FuzzyStr
	std::istream& operator >> (std::istream& in, FuzzyString& a_FuzzyStr)
	{
		char* l_cptrInput = new char[FuzzyString::MAX_CHAR_EXTRACT];
		std::cin.getline(l_cptrInput, FuzzyString::MAX_CHAR_EXTRACT);

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(FuzzyString::MAX_CHAR_EXTRACT, '\n');
			std::cout << "Fail bit is reset\n";
			return in;
		}

		a_FuzzyStr.AllocateAndAssignStr(l_cptrInput);

		delete[] l_cptrInput;
		l_cptrInput = nullptr;

		return in;
	}

	////Sets FuzzyString1 = FuzzyString2
	void FuzzyString :: operator=(const FuzzyString& a_FuzzyStringInput)
	{
		AllocateAndAssignStr(a_FuzzyStringInput.m_cptrStrArr);
	}

	////Sets FuzzyString = cArray
	void FuzzyString:: operator=(const char a_cptrInput[])
	{
		AllocateAndAssignStr(a_cptrInput);
	}

	////Sets FuzzyString.m_cptrStrArr = std::string
	void FuzzyString:: operator=(const std::string& a_strInput)
	{
		AllocateAndAssignStr(a_strInput.c_str());
	}

	////Sets FuzzyString.m_cptrStrArr = Int
	void FuzzyString:: operator=(const int& a_Int)
	{
		*this = FuzzyString(a_Int);
	}

	////operatir overloading for FuzzyString = r value a_FuzzyStringInput by reference.
	void FuzzyString:: operator=(FuzzyString&& a_FuzzyStringInput)
	{
		CopyConstructorByValue(a_FuzzyStringInput);
	}

	////Concatenates FuzzyString += a_cptrInput
	void FuzzyString::operator+=(const char* a_cptrInput)
	{
		char* l_cptrConcat = FuzzyString::AppendString(this->m_cptrStrArr, a_cptrInput);
		AllocateAndAssignStr(l_cptrConcat);

		delete[] l_cptrConcat;
		l_cptrConcat = nullptr;
	}

	////Concatenates FuzzyString1 += FuzzyString2
	void FuzzyString::operator+=(const FuzzyString& a_FuzzyStringInput)
	{
		*this += a_FuzzyStringInput.m_cptrStrArr;
	}

	////Concatenates FuzzyString += a_strInput
	void FuzzyString:: operator+=(const std::string& a_strInput)
	{
		*this += a_strInput.c_str();
	}

	////Concatenates FuzzyString += Int
	void FuzzyString :: operator+=(const int& a_Int)
	{
		*this += a_Int;
	}

	////Concatenates a_cptrInput += FuzzyString 
	void operator+=(char* &a_cptrInput, const FuzzyString& a_FuzzyString)
	{
		a_cptrInput = FuzzyString::AppendString(a_cptrInput, a_FuzzyString.m_cptrStrArr);
	}

	////Concatenates a_strInput += FuzzyString 
	void operator+=(std::string &a_strInput, const FuzzyString& a_FuzzyString)
	{
		a_strInput = FuzzyString::AppendString(a_strInput.c_str(), a_FuzzyString.m_cptrStrArr);
	}

	////Concatenates FuzzyString + a_cptrInput
	FuzzyString operator+(const FuzzyString& a_FuzzyString, const char a_cptrInput[])
	{
		return FuzzyString::Concatenate(a_FuzzyString.m_cptrStrArr, a_cptrInput);
	}

	////Concatenates FuzzyString + a_strInput
	FuzzyString operator+(const FuzzyString& a_FuzzyString, const std::string& a_strInput)
	{
		return FuzzyString::Concatenate(a_FuzzyString.m_cptrStrArr, a_strInput.c_str());
	}

	////Concatenates a_FuzzyString1.m_cptrStrArr + a_FuzzyString2 to FuzzyString
	FuzzyString operator+(const FuzzyString& a_FuzzyString1, const FuzzyString& a_FuzzyString2)
	{
		return FuzzyString::Concatenate(a_FuzzyString1.m_cptrStrArr, a_FuzzyString2.m_cptrStrArr);
	}

	////Concatenates FuzzyString.m_cptrStrArr + int
	FuzzyString operator+(const FuzzyString& a_FuzzyString, const int& a_Int)
	{
		return  a_FuzzyString + FuzzyString(a_Int);
	}

	////Concatenates a_cptrInput + FuzzyString
	FuzzyString operator+(const char a_cptrInput[], const FuzzyString& a_FuzzyString)
	{
		return FuzzyString::Concatenate(a_cptrInput, a_FuzzyString.m_cptrStrArr);
	}

	////Concatenates a_strInput + FuzzyString
	FuzzyString operator+(const std::string& a_strInput, const FuzzyString& a_FuzzyString)
	{
		return FuzzyString::Concatenate(a_strInput.c_str(), a_FuzzyString.m_cptrStrArr);
	}

	////Concatenates int + FuzzyString
	FuzzyString operator+(const int& a_Int, const FuzzyString& a_FuzzyString)
	{
		return FuzzyString(a_Int) + a_FuzzyString;
	}

#pragma endregion Operator Overloading

#pragma region Getters

	////Returns the capacity of internal char array
	int FuzzyString::GetCapacity() const
	{
		return m_iCapacity;
	}

	////Returns the size of internal char array
	int FuzzyString::GetSize() const
	{
		return m_iSize;
	}

	////Returns the Empty char
	char* const FuzzyString::GetEmpty()
	{
		return NULL_TERMINATOR;
	}

	////Returns the Null terminator char
	char* const FuzzyString::GetNullTerminator()
	{
		return NULL_TERMINATOR;
	}

	////Returns the char pointer
	char* FuzzyString::GetC_Str() const
	{
		return m_cptrStrArr;
	}

#pragma endregion Getters

	////Logs the internal char ptr, the size and capacity
	void FuzzyString:: DebugLog()
	{
		std::cout << "FuzzyString ::'" << *this << "', Size::" <<
			m_iSize << ", Capacity::" << m_iCapacity << "\n";
	}
}