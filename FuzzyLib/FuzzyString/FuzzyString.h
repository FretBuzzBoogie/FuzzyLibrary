#pragma once

#include <iostream>
#include <string>
#include <memory>
#include "..\Utils\IFuzzyDebug.h"
#include "..\Utils\FuzzyUtility.h"

namespace FuzzyLib
{
	class FuzzyString : public IFuzzyDebug
	{
		///PRIVATE VARIABLES
		private:
			int m_iCapacity = 1;
			int m_iSize = 1;
			static char* const NULL_TERMINATOR;
			static const int MAX_CHAR_EXTRACT;
			char* m_cptrStrArr = NULL_TERMINATOR;

		///PUBLIC VARIABLES
		public:

		///PRIVATE SOURCE
		private:
			void AllocateAndAssignStr(const char a_cptrInput[]);

			static FuzzyString Concatenate(const char* a_cptrInput1, const char* a_cptrInput2);
			static int GetSizeOfPointedData(const char a_cptr[]);
			static char* AppendString(const char* a_cptr1, const char* a_cptr2);

		///PUBLIC SOURCE
		public:
			FuzzyString();
			FuzzyString(FuzzyString &a_FuzzyString);
			FuzzyString(const char a_cptrInput[]);
			FuzzyString(const std::string &a_strInput);
			FuzzyString(const int &a_intInput);

			~FuzzyString();

			int GetCapacity() const;
			int GetSize() const;
			char* GetC_Str() const;

			bool IsEqual(const FuzzyString &a_FuzzyString) const;
			bool IsEqual(const char* a_cptrInput) const;
			bool IsEqual(const std::string& a_strInput) const;
			virtual void DebugLog() override;

			void operator=(const char a_cptrInput[]);
			void operator=(const std::string& a_strInput);
			void operator=(const FuzzyString& a_FuzzyStringInput);
			void operator=(const int& a_Int);

			friend FuzzyString operator+(const FuzzyString& a_FuzzyString, const char a_cptrInput[]);
			friend FuzzyString operator+(const FuzzyString& a_FuzzyString, const std::string& a_strInput);
			friend FuzzyString operator+(const FuzzyString& a_FuzzyString, const FuzzyString& a_FuzzyStringInput);
			friend FuzzyString operator+(const FuzzyString& a_FuzzyString, const int& a_Int);

			friend FuzzyString operator+(const char a_cptrInput[], const FuzzyString& a_FuzzyString);
			friend FuzzyString operator+(const std::string& a_strInput, const FuzzyString& a_FuzzyString);
			friend FuzzyString operator+(const int& a_Int, const FuzzyString& a_FuzzyString);

			void operator+=(const FuzzyString& a_FuzzyStringInput);
			void operator+=(const char* a_cptrInput);
			void operator+=(const std::string& a_strInput);
			void operator+=(const int& a_Int);

			friend void operator+=(char* &a_cptrInput, const FuzzyString& a_FuzzyString);
			friend void operator+=(std::string &a_strInput, const FuzzyString& a_FuzzyString);

			friend std::ostream& operator<<(std::ostream& out, const FuzzyString& a_FuzzyStr);
			friend std::istream& operator>>(std::istream& in,  FuzzyString& a_FuzzyStr);

			static char* const GetEmpty();
			static char* const GetNullTerminator();
	};
}