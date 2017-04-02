#include <Trappist-1\ui\widgets\View.hpp>

#include <Trappist-1\Graphics\Renderer2D.hpp>

#include <Trappist-1\Graphics\Renderer2D.hpp>

namespace ui
{
	void View::beginSubmission(Renderer2D &renderer2d) const
	{
		BASE::beginSubmission(renderer2d);
		auto bounds = getGlobalBounds();
		renderer2d.pushScissor(static_cast<GLint>(bounds.left), static_cast<GLint>(bounds.top), static_cast<GLint>(bounds.width), static_cast<GLint>(bounds.height));
	}

	void View::performSubmittion(Renderer2D &renderer2d) const
	{
		BASE::performSubmittion(renderer2d);
	}

	void View::endSubmission(Renderer2D &renderer2d) const
	{
		BASE::endSubmission(renderer2d);
		renderer2d.popScissor();
	}
}