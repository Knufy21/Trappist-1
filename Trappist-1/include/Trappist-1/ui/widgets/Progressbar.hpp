#pragma once

#include "Trappist-1\ui\widgets\Image.hpp"

namespace ui
{
	class Progressbar : public Image
	{
		using BASE = Image;
	public:
		enum class Style { CUT = 0, STRETCH = 1 };

		Progressbar();

		virtual ~Progressbar();

		// Returns the progress as a fraction.
		float getProgress() const;

		// Sets the progress as a fraction.
		void setProgress(float progressFraction);

		// Adds the progress as a fraction.
		void addProgress(float progressFraction);

		// Returns the color of the progress.
		const glm::vec4 &getProgressColor() const;

		// Sets the color of the progress.
		void setProgressColor(const glm::vec4 &progressColor);

		// Returns the texture used to render the progress.
		const Texture *getProgressTexture() const;

		// Sets the texture used to render the progress.
		void setProgressTexture(const Texture *texture);

		// Returns the style indicating how to render the progress.
		Style getProgressStyle() const;

		// Sets the style indicating how to render the progress.
		void setProgressStyle(Style progressStyle);

		// Returns the texture rect for all vertices measured by a value between 0 and 1.
		const sf::FloatRect &getProgressTextureRect() const;

		// Sets the texture rect for all vertices measured by a value between 0 and 1.
		void setProgressTextureRect(const sf::FloatRect &rect);

		// Ensures the progress to be updated.
		void ensureProgressUpdate() const;

	protected:
		virtual void performSubmittion(Renderer2D &renderer2d) const override;

		virtual void onSizeChanged(const glm::vec2 &size) override;

		virtual void onProgressChanged();

	private:
		VertexPCT2D *progressVertices;
		const Texture *texProgress;
		Style progressStyle;
		float progressFraction;
		sf::FloatRect progressTextureRect;
		mutable bool needsProgressUpdate;
	};

	// Inline

	inline float Progressbar::getProgress() const
	{
		return this->progressFraction;
	}

	inline void Progressbar::setProgress(float progressFraction)
	{
		this->progressFraction = glm::clamp(progressFraction, 0.0f, 1.0f);
		this->needsProgressUpdate = true;
		onProgressChanged();
	}

	inline void Progressbar::addProgress(float progressFraction)
	{
		this->progressFraction = glm::clamp(this->progressFraction + progressFraction, 0.0f, 1.0f);
		this->needsProgressUpdate = true;
		onProgressChanged();
	}

	inline const glm::vec4 &Progressbar::getProgressColor() const
	{
		return progressVertices[0].color;
	}

	inline const Texture *Progressbar::getProgressTexture() const
	{
		return this->texProgress;
	}

	inline Progressbar::Style Progressbar::getProgressStyle() const
	{
		return this->progressStyle;
	}

	inline void Progressbar::setProgressStyle(Progressbar::Style progressStyle)
	{
		this->progressStyle = progressStyle;
		this->needsProgressUpdate = true;
	}

	inline const sf::FloatRect &Progressbar::getProgressTextureRect() const
	{
		return this->progressTextureRect;
	}

	inline void Progressbar::setProgressTextureRect(const sf::FloatRect &rect)
	{
		this->progressTextureRect = rect;
		this->needsProgressUpdate = true;
	}
}