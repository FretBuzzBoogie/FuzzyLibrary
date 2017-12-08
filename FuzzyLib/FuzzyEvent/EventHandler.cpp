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


		m_pUMapRegisteredListener->clear();
		m_pEventSystem->UnregisterEventHandler(this);

		delete m_pUMapRegisteredListener;
		m_pUMapRegisteredListener = nullptr;
	}

	//Get the unordered map's container count
	const int EventHandler::GetCount() const
	{
		return m_pUMapRegisteredListener->size();
	}

#pragma endregion Event Handler

#pragma region Registered Listener

	//Constructor for the Value of the unordered map
	//includes List of registered Listeners for the event of a particular type
	EventHandler::RegisteredListener::RegisteredListener(IEvent* a_pEventObject, IEventListener* a_pListenerObj)
	{
		m_pIEvent = a_pEventObject;
		m_pEventListener = a_pListenerObj;
	}

	//Destructor for the Value of the unordered map
	EventHandler::RegisteredListener::~RegisteredListener()
	{

	}

	//Returns true if RegisteredListener == a_otherRegisteredListener AND
	//Checks if this->Event == a_pRegisteredlistener->Event
	//Checks if this->Listener == a_pRegisteredlistener->Listener
	bool EventHandler::RegisteredListener:: operator==(const RegisteredListener& a_pRegisteredlistener)
	{
		return (this->m_pEventListener == a_pRegisteredlistener.m_pEventListener &&
			this->m_pIEvent == a_pRegisteredlistener.m_pIEvent);		
	}

	//Checks if this->Event == a_pRegisteredlistener->Event AND
	//Checks if this->Listener == a_pRegisteredlistener->Listener
	//Returns true if RegisteredListener != a_otherRegisteredListener
	bool EventHandler::RegisteredListener::operator!=(const RegisteredListener& a_pRegisteredlistener)
	{
		return !(*this == a_pRegisteredlistener);
	}

#pragma endregion Registered Listener
}