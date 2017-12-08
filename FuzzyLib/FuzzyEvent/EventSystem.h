#pragma once
#include "../FuzzyList/FuzzyList.h"
#include "../Utils/IFuzzyDebug.h"

namespace FuzzyLib
{
	template<typename T>
	class FuzzyEvent;

	class EventHandler;

	class EventSystem : public IFuzzyDebug
	{
	private:
		static EventSystem* s_pEventSystem;
		
		EventSystem();
		virtual ~EventSystem();

		FuzzyList<EventHandler*>* m_pListEventHandler = nullptr;

	public:

		static EventSystem* const GetInstance();
		static void Destroy();

		void RegisterEventHandler(EventHandler* a_EventHandler);
		void UnregisterEventHandler(EventHandler* a_EventHandler);

		const int GetEventHandlerCount() const;

		void DebugLog();
	};
}