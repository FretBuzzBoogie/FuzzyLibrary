#pragma once
#include "EventSystem.h"
#include "EventHandler.h"

namespace FuzzyLib
{
#pragma region Event Handler

	EventHandler::EventHandler()
		: m_pEventSystem{ EventSystem::GetInstance() }
	{
		m_pEventSystem->RegisterEventHandler(this);
		m_pUMapRegisteredListener = new std::unordered_map<std::type_index, FuzzyList<RegisteredListener*>*>();
	};

	EventHandler::~EventHandler()
	{
		m_pEventSystem->UnregisterEventHandler(this);

		delete m_pUMapRegisteredListener;
		m_pUMapRegisteredListener = nullptr;
	};

	

#pragma endregion Event Handler

#pragma region Registered Listener

	//Constructor for the Value of the unordered map
	//includes List of registered Listeners for the event of a particular type
	EventHandler::RegisteredListener::RegisteredListener(IEvent* a_pEventObject, IEventListener* a_pListenerObj)
	{

	}

	//Destructor for the Value of the unordered map
	EventHandler::RegisteredListener::~RegisteredListener()
	{

	}

#pragma endregion Registered Listener
}