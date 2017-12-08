#pragma once
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <type_traits>
#include "../FuzzyList/FuzzyList.h"
#include "FuzzyEventListener.h"
#include "FuzzyEvent.h"

namespace FuzzyLib
{
	class EventSystem;

	class EventHandler
	{
	private:
		class RegisteredListener
		{
		private:


		public:
			RegisteredListener() = delete;
			RegisteredListener(IEvent* a_pEventObject, IEventListener* a_pListenerObj);
			~RegisteredListener();

			IEvent* m_pIEvent = nullptr;
			IEventListener* m_pEventListener = nullptr;
		};

		EventSystem* const m_pEventSystem = nullptr;

		std::unordered_map<std::type_index, FuzzyList<RegisteredListener*>*>* m_pUMapRegisteredListener = nullptr;

	public:
		EventHandler();
		~EventHandler();

		const int GetCount() const;

		template<typename EVENT_TYPE, typename LISTENER_TYPE>
		void AddListener(EVENT_TYPE& a_pClassType, LISTENER_TYPE& a_pListener);
	};

	//Adds listener of type into the unordered list with type EVENT_TYPE
	template<typename EVENT_TYPE, typename LISTENER_TYPE>
	void EventHandler::AddListener(EVENT_TYPE& a_EventType, LISTENER_TYPE& a_Listener)
	{
		FuzzyList<RegisteredListener*>* l_pListRegListener = nullptr;

		if (m_pUMapRegisteredListener->find(typeid(a_EventType)) == m_pUMapRegisteredListener->end())
		{
			l_pListRegListener = new FuzzyList<RegisteredListener*>();
			m_pUMapRegisteredListener->insert({ typeid(EVENT_TYPE), l_pListRegListener });
		}
		else
		{
			l_pListRegListener = m_pUMapRegisteredListener->at(typeid(a_EventType));
		}
		
		RegisteredListener* l_newRegisteredListener = new RegisteredListener(static_cast<IEvent*>(&a_EventType), static_cast<IEventListener*>(&a_Listener));
		l_pListRegListener->Add(l_newRegisteredListener);
	}
}