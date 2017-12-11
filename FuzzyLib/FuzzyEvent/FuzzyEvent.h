#pragma once
#include <iostream>
#include "EventSystem.h"

namespace FuzzyLib
{
	class IEvent
	{
	private:

	public:
		virtual ~IEvent() = 0
		{}
	};

	class FuzzyEvent : public IEvent
	{
	private:

	public:
		FuzzyEvent()
		{
		}

		virtual ~FuzzyEvent() = 0
		{}
	};

	class InputEvent : public FuzzyEvent
	{
	public:
		InputEvent() : FuzzyEvent()
		{

		}

		virtual ~InputEvent()
		{
			
		}

		void PrintEventSuccess()
		{
			std::cout << "SUCCESS\n";
		}
	};
}