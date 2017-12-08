#pragma once
#include "EventHandler.h"
#include "EventSystem.h"

namespace FuzzyLib
{
	//The singleton instance of the event system
	EventSystem* EventSystem::s_pEventSystem = nullptr;

	EventSystem::EventSystem()
	{
		m_pListEventHandler = new FuzzyList<EventHandler*>();
	}

	EventSystem::~EventSystem()
	{
		delete m_pListEventHandler;
		m_pListEventHandler = nullptr;
	}

	//Returns the count of the number of event handlers stored
	const int EventSystem::GetEventHandlerCount() const
	{
		return m_pListEventHandler->GetCount();
	}

	//Destroys the singleton instance
	void EventSystem::Destroy()
	{
		if (s_pEventSystem != nullptr)
		{
			delete s_pEventSystem;
			s_pEventSystem = nullptr;
		}
	}

	//Adds the specified event handler into the List of all Event handlers
	void EventSystem::RegisterEventHandler(EventHandler* a_EventHandler)
	{
		m_pListEventHandler->Add(a_EventHandler);
	}

	//Removes the specified event handler into the List of all Event handlers
	void EventSystem::UnregisterEventHandler(EventHandler* a_EventHandler)
	{
		m_pListEventHandler->Remove(a_EventHandler);
	}

	//Gets the singleton instance
	//Creates and returns if currently null
	EventSystem* const EventSystem::GetInstance()
	{
		if (s_pEventSystem == nullptr)
		{
			s_pEventSystem = new EventSystem();
		}
		return s_pEventSystem;
	}

	//Logs the list of event handlers
	void EventSystem::DebugLog()
	{
		std::cout << "EventSystem::DebugLog:: Count of EventHandlers stored ::" << GetEventHandlerCount() << "\n";
	}
}