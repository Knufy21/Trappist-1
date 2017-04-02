#pragma once

#include <functional>
#include <Trappist-1\ui\listeners\Listener.hpp>

namespace ui
{
	template<Listener::Type listenerType>
	class TemplateListener : public Listener
	{
	public:
		TemplateListener(std::function<void(const void *)> onListenerEvent);
	};

	#include <Trappist-1\ui\listeners\TemplateListener.inl>
}