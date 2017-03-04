#pragma once

#include <iostream>
#include <string>

namespace FuzzyLib
{
	class FuzzyString
	{
		///PRIVATE VARIABLES
		private:
			int m_iCapacity = 1;
			int m_iSize = 1;
			char* m_cptrStrArr;
			static const char NULL_TERMINATOR;

		///PUBLIC VARIABLES
		public:

		///PRIVATE SOURCE
		private:
			void AllocateAndAssignStr(const char a_cptrInput[]);
			int GetSizeOfPointedData(const char a_cptr[]);

		///PUBLIC SOURCE
		public:
			FuzzyString(const char a_cptrInput[]);
			FuzzyString(const std::string &a_strInput);

			~FuzzyString();

			int GetCapacity() const;
			int GetSize() const;
			char* GetEmpty() const;
			char* GetNullTerminator() const;
			void DebugLog();

			void operator=(const char a_cptrInput[]);
			void operator=(const std::string& a_strInput);

			friend std::ostream& operator<<(std::ostream& out, const FuzzyString& a_FuzzyStr);
			friend std::istream& operator>>(std::istream& in, const FuzzyString& a_FuzzyStr);

	};
}