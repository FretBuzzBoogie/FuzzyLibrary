#pragma once

#include <iostream>
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

			bool operator==(const RegisteredListener& a_pRegisteredlistener);
			bool operator!=(const RegisteredListener& a_pRegisteredlistener);

			IEvent* m_pIEvent = nullptr;
			IEventListener* m_pEventListener = nullptr;
		};

		void DeleteAllListeners();

		EventSystem* const m_pEventSystem = nullptr;

		std::unordered_map<std::type_index, FuzzyList<RegisteredListener*>*>* m_pUMapRegisteredListener = nullptr;

	public:
		EventHandler();
		~EventHandler();

		const int GetCount() const;

		void Fire(IEvent& a_IEvet);

		void DebugLog();

		template<typename EVENT_TYPE>
		const int GetListenerCountOfType() const;

		template<typename EVENT_TYPE, typename LISTENER_TYPE>
		void RemoveListener(EVENT_TYPE& a_pClassType, LISTENER_TYPE& a_pListener);

		template<typename EVENT_TYPE, typename LISTENER_TYPE>
		void AddListener(EVENT_TYPE& a_pClassType, LISTENER_TYPE& a_pListener);
	};


	template<typename EVENT_TYPE>
	const int EventHandler::GetListenerCountOfType() const
	{
		const std::type_info& l_TypeIdToAdd = typeid(EVENT_TYPE);
		if (m_pUMapRegisteredListener->find(l_TypeIdToAdd) != m_pUMapRegisteredListener->end())
		{
			return m_pUMapRegisteredListener->at(l_TypeIdToAdd)->GetCount();
		}

		return 0;
	}

	//Removes the listener bound to a particular event from that event handler registered list
	template<typename EVENT_TYPE, typename LISTENER_TYPE>
	void EventHandler::RemoveListener(EVENT_TYPE& a_pClassType, LISTENER_TYPE& a_pListener)
	{
		FuzzyList<RegisteredListener*>* l_pListRegListener = nullptr;
		const std::type_info& l_TypeIdToAdd = typeid(EVENT_TYPE);

		if (m_pUMapRegisteredListener->find(l_TypeIdToAdd) != m_pUMapRegisteredListener->end())
		{ 
			RegisteredListener* l_pRegistrationToRemove = nullptr;

			l_pListRegListener = m_pUMapRegisteredListener->at(l_TypeIdToAdd);
			FuzzyList<RegisteredListener*>& l_refListRegistration = *l_pListRegListener;

			int l_iRegListCount = l_pListRegListener->GetCount();
			RegisteredListener& l_refRegistrationToCompare = RegisteredListener(&a_pClassType, &a_pListener);

			for (int l_iRegistrationIndex = 0; l_iRegistrationIndex < l_iRegListCount; l_iRegistrationIndex++)
			{
				if (*(l_refListRegistration[l_iRegistrationIndex]) == l_refRegistrationToCompare)
				{
					l_pRegistrationToRemove = l_refListRegistration[l_iRegistrationIndex];
					break;
				}
			}

			if (l_pRegistrationToRemove != nullptr)
			{
				l_pListRegListener->Remove(l_pRegistrationToRemove);
				delete l_pRegistrationToRemove;
				l_pRegistrationToRemove = nullptr;
			}
		}
	}

	//Adds listener of type into the unordered list with type EVENT_TYPE
	template<typename EVENT_TYPE, typename LISTENER_TYPE>
	void EventHandler::AddListener(EVENT_TYPE& a_EventType, LISTENER_TYPE& a_Listener)
	{
		static_assert(std::is_base_of<IEvent, EVENT_TYPE>::value,
			"EventHandler::AddListener:: listener not added because given event type not a child of IEvent'");

		static_assert(std::is_base_of<IEventListener, LISTENER_TYPE>::value,
			"EventHandler::AddListener:: listener not added because given listener type not a child of IEventListener'");

		FuzzyList<RegisteredListener*>* l_pListRegListener = nullptr;
		const std::type_info& l_TypeIdToAdd = typeid(a_EventType);

		if (m_pUMapRegisteredListener->find(l_TypeIdToAdd) == m_pUMapRegisteredListener->end())
		{
			l_pListRegListener = new FuzzyList<RegisteredListener*>();
			m_pUMapRegisteredListener->insert({ l_TypeIdToAdd, l_pListRegListener });
		}
		else
		{
			l_pListRegListener = m_pUMapRegisteredListener->at(l_TypeIdToAdd);
		}

		IEvent* l_pIEvent = (bool)std::is_base_of<IEvent, EVENT_TYPE>::value ? static_cast<IEvent*>(&a_EventType) : nullptr ;
		IEventListener* l_pIEventListener = (bool)std::is_base_of<IEventListener, LISTENER_TYPE >::value ? static_cast<IEventListener*>(&a_Listener) : nullptr;
		
		if (l_pIEvent == nullptr || l_pIEventListener == nullptr)
		{
			return;
		}

		RegisteredListener* l_newRegisteredListener = new RegisteredListener(l_pIEvent, l_pIEventListener);
		l_pListRegListener->Add(l_newRegisteredListener);
	}
}