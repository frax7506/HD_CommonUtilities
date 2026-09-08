#pragma once

// The intended use of this class is:
	// 1. Use DECLARE_EVENT_ENUM from the HD_Event header to create an EventEnumType
	// 2. Use DECLARE_EVENT from the same header with the EventEnumType to create your own DECLARE_X_EVENT macro,
	//		for instance #define DECLARE_AI_EVENT(aAIEventEnumEntry) DECLARE_EVENT(AIEventType, aAIEventEnumEntry)
	// 3. (Optional) It's handy to typedef your own manager type,
	//		for instance typedef HD_EventManager<AIEventType> AIEventManager;
	// 4. New event classes are created with your DECLARE-macro in the public section, for instance
	//
	// 		class PlayerStoppedHackingAIEvent
	//		{
	//		public:
	//			DECLARE_AI_EVENT(PlayerStoppedHacking);
	//
	//			PlayerStoppedHackingAIEvent();
	//		};
	//
	// 5. Classes register and unregister to events via RegisterEventListener and UnregisterEventListener,
	//		for instance RegisterEventListener(this, &StupidGuardEventController::HandlePlayerStoppedHackingMessage);
	//		and UnregisterEventListener(this); passing in a member function that takes a const& to the event
	//		you're listening to.
	//
	//		And this is the main idea of this system. You don't need to inherit from some kind of listener class
	//		in order to listen to events. You just need to call Register/Unregister-EventListener.

// Future work:
	// * The actual event-sending code has very low complexity. Events are sent right away to all listeners as
	//		soon as SendEvent is called. If this becomes undesirable and the dispatching of events needs to
	//		happen in a more controlled manner, then a system that collects all "send-requests" and then sends
	//		them all at the same time could be implemented. In that case an aditional hook for a FlushEvents-function
	//		would have to be placed in game code.

#include "HD_GrowingArray.h"
#include "HD_HashMap.h"
#include "HD_Types.h"

#include <functional>

template<typename ListenerType, typename EventChildType>
using EventReceivedCallback = void(ListenerType::*)(const EventChildType&);

struct HD_EventListener
{
	template<typename ListenerType, typename EventChildType>
	static HD_EventListener Create(ListenerType* aListener, const EventReceivedCallback<ListenerType, EventChildType>& aEventReceivedCallback)
	{
		HD_EventListener listener;
		listener.myListener = aListener;
		listener.myCallback = std::bind([aListener, aEventReceivedCallback](const void* aEvent) { (aListener->*aEventReceivedCallback)(*static_cast<const EventChildType*>(aEvent)); }, std::placeholders::_1);

		return listener;
	}

	void* myListener;
	std::function<void(const void* aEvent)> myCallback;
};

template<typename EventEnumType>
class HD_EventManager
{
public:
	template<typename ListenerType, typename EventChildType>
	void RegisterEventListener(ListenerType* aListener, const EventReceivedCallback<ListenerType, EventChildType>& aEventReceivedCallback);

	void UnregisterEventListener(void* aListener);

	template<typename EventChildType>
	void SendEvent(const EventChildType& aEvent);

private:
	HD_HashMap<EventEnumType, HD_GrowingArray<HD_EventListener>> myEventListeners;
};

template<typename EventEnumType>
template<typename ListenerType, typename EventChildType>
void HD_EventManager<EventEnumType>::RegisterEventListener(ListenerType* aListener, const EventReceivedCallback<ListenerType, EventChildType>& aEventReceivedCallback)
{
	HD_EventListener eventListener = HD_EventListener::Create(aListener, aEventReceivedCallback);
	myEventListeners[EventChildType::GetStaticType()].PushBack(eventListener);
}

template<typename EventEnumType>
void HD_EventManager<EventEnumType>::UnregisterEventListener(void* aListener)
{
	for (auto& entry : myEventListeners)
	{
		HD_GrowingArray<HD_EventListener>& listeners = entry.mySecond;

		for (SizeType i = 0; i < listeners.GetSize(); i++)
		{
			if (listeners[i].myListener == aListener)
			{
				listeners.Remove(i);
				break;
			}
		}
	}
}

template<typename EventEnumType>
template<typename EventChildType>
void HD_EventManager<EventEnumType>::SendEvent(const EventChildType& aEvent)
{
	const HD_GrowingArray<HD_EventListener>* listeners = myEventListeners.GetIfExists(EventChildType::GetStaticType());
	if (!listeners)
	{
		return;
	}

	for (const HD_EventListener& listener : *listeners)
	{
		listener.myCallback(&aEvent);
	}
}
