#pragma once

template<Listener::Type listenerType>
TemplateListener<listenerType>::TemplateListener(std::function<void(const void *)> onListenerEvent)
	: Listener(listenerType, onListenerEvent)
{  }