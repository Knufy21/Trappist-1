#pragma once

#include "Trappist-1\ui\widgets\Group.hpp"

namespace ui
{
	class View : public Group
	{
		using BASE = Group;
	public:

	protected:
		// Begins the submission by pushing the transform matrix onto the renderer.
		virtual void beginSubmission(Renderer2D &renderer2d) const override;

		// Performs the submittion by submitting the vertices to the renderer.
		virtual void performSubmittion(Renderer2D &renderer2d) const override;

		// Ends the submission by popping the transform matrix from the renderer.
		virtual void endSubmission(Renderer2D &renderer2d) const override;

	private:
	};
}