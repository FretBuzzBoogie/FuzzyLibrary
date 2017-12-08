#pragma once
#include <iostream>
#include "EventSystem.h"

namespace FuzzyLib
{
	class IEvent
	{
	private:

	public:
		//virtual ~IEvent() = 0;
	};

	template<typename T>
	class FuzzyEvent :virtual public IEvent
	{
	private:
		T* const m_pTEvent = nullptr;

	public:
		EventSystem* const m_pEventHandler = nullptr;

		FuzzyEvent( T* const a_pTEvent) :
			m_pEventHandler{ EventSystem::GetInstance() },
			m_pTEvent{ a_pTEvent }
		{
		}

		/*virtual ~FuzzyEvent() = 0;*/

		void Fire(const std::type_info& a_Type, const FuzzyEvent*& a_EventHandle)
		{
			EventSystem::Fire();
		}
	};

	class InputEvent : public FuzzyEvent<InputEvent>
	{
	public:
		InputEvent() : FuzzyEvent(this)
		{

		}

		/*virtual ~InputEvent()
		{
			
		}*/
	};
}