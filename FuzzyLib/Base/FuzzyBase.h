#pragma once

#include <iostream>

namespace FuzzyLib
{
	class IFuzzyBase
	{
	public:
		virtual void DebugLog() = 0;
		virtual ~IFuzzyBase() {}
	};
}