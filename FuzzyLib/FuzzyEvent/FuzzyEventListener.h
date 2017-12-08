#pragma once
#include "FuzzyEvent.h"

namespace FuzzyLib
{
	class IEventListener
	{
	private:

	public:
		virtual ~IEventListener() {};

		virtual void Dispatch(IEvent& a_pEvent) = 0;
	};

	template<typename T>
	class FuzzyEventListener : virtual public IEventListener
	{
	private:

	public:
		FuzzyEventListener()
		{
			
		}

		virtual ~FuzzyEventListener() {};

		virtual void OnEvent(T* a_pEvent) = 0;

		virtual void Dispatch(IEvent& a_pEvent)
		{
			OnEvent( dynamic_cast<T*>(&a_pEvent));
		}

	};

	class InputListener : public FuzzyEventListener<InputEvent>
	{
	public:
		InputListener()
		{
			
		}

		virtual ~InputListener()
		{
			
		}

		virtual void OnEvent(InputEvent* a_Event) override
		{
			std::cout << "DISPATCHED DISPATCHED DISPATCHED DISPATCHED \n";
		}
	};
}