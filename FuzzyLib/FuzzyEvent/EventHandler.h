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

	class EventHandler : public IFuzzyDebug
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

		const int GetListenerCountOfType(const std::type_info& a_type) const;

		void RemoveListener(IEvent& a_pClassType, IEventListener& a_pListener);

		void AddListener(IEvent& a_pClassType, IEventListener& a_pListener);

		void DebugLog();
	};


	

	

	
}