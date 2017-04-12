#pragma once

#include <iostream>
#include <string>
#include <memory>

namespace FuzzyLib
{
	class FuzzyString
	{
		///PRIVATE VARIABLES
		private:
			int m_iCapacity = 1;
			int m_iSize = 1;
			char* m_cptrStrArr;
			static char* const NULL_TERMINATOR;

		///PUBLIC VARIABLES
		public:

		///PRIVATE SOURCE
		private:
			void AllocateAndAssignStr(const char a_cptrInput[]);
			static int GetSizeOfPointedData(const char a_cptr[]);
			static char* AppendString(const char* a_cptr1, const char* a_cptr2);

		///PUBLIC SOURCE
		public:
			FuzzyString(FuzzyString &a_FuzzyString);
			FuzzyString(const char a_cptrInput[]);
			FuzzyString(const std::string &a_strInput);

			~FuzzyString();

			int GetCapacity() const;
			int GetSize() const;
			char* GetC_Str() const;

			bool IsEqual(const FuzzyString &a_FuzzyString) const;
			bool IsEqual(const char* a_cptrInput) const;
			bool IsEqual(const std::string& a_strInput) const;
			void DebugLog();

			void operator=(const char a_cptrInput[]);
			void operator=(const std::string& a_strInput);
			void operator=(const FuzzyString& a_FuzzyStringInput);

			friend FuzzyString operator+(const FuzzyString& a_FuzzyString, const char a_cptrInput[]);
			friend FuzzyString operator+(const FuzzyString& a_FuzzyString, const std::string& a_strInput);
			friend FuzzyString operator+(const FuzzyString& a_FuzzyString, const FuzzyString& a_FuzzyStringInput);

			friend FuzzyString operator+(const char a_cptrInput[], const FuzzyString& a_FuzzyString);
			friend FuzzyString operator+(const std::string& a_strInput, const FuzzyString& a_FuzzyString);

			void operator+=(const FuzzyString& a_FuzzyStringInput);
			void operator+=(const char* a_cptrInput);
			void operator+=(const std::string& a_strInput);

			friend void operator+=(char* &a_cptrInput, const FuzzyString& a_FuzzyString);
			friend void operator+=(std::string &a_strInput, const FuzzyString& a_FuzzyString);

			friend std::ostream& operator<<(std::ostream& out, const FuzzyString& a_FuzzyStr);
			
			static char* GetEmpty();
			static char* GetNullTerminator();
	};
}