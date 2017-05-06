#pragma once

#include <iostream>

namespace FuzzyLib
{
	class IFuzzyEvent
	{
		public:

			virtual ~IFuzzyEvent() {}
	};

	template<typename T>
	class FuzzyEvent: public IFuzzyEvent
	{
		private:

		public:
			FuzzyEvent()
			{
			}
	};
}