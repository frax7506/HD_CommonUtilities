#pragma once

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
