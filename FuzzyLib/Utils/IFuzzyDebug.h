#pragma once

#include <iostream>

namespace FuzzyLib
{
	class IFuzzyDebug
	{
	public:
		virtual void DebugLog() = 0;
		virtual ~IFuzzyDebug() {}
	};
}