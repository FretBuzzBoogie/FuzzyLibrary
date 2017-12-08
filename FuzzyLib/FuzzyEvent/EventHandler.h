#pragma once
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
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
		};

		EventSystem* const m_pEventSystem = nullptr;

		std::unordered_map<std::type_index, FuzzyList<RegisteredListener*>*>* m_pUMapRegisteredListener = nullptr;

	public:
		EventHandler();
		~EventHandler();

		template<typename EVENT_TYPE, typename LISTENER_TYPE>
		void AddListener(EVENT_TYPE& a_pClassType, LISTENER_TYPE& a_pListener);
	};

	//Adds listener of type into the unordered list with type EVENT_TYPE
	template<typename EVENT_TYPE, typename LISTENER_TYPE>
	void EventHandler::AddListener(EVENT_TYPE& a_pEventType, LISTENER_TYPE& a_pListener)
	{
		//static_cast<>()

		if (m_pUMapRegisteredListener->find(typeid(a_pEventType)) == m_pUMapRegisteredListener->end())
		{
			FuzzyList<RegisteredListener*>* l_pListRegListener = m_pUMapRegisteredListener->at(typeid(a_pEventType));
			
		}
	}
}