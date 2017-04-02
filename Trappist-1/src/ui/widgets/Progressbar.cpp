#include <Trappist-1\ui\widgets\Progressbar.hpp>

#include <Trappist-1\Graphics\Renderer2D.hpp>

namespace ui
{
	Progressbar::Progressbar()
		: BASE(), progressVertices(new VertexPCT2D[4]), texProgress(nullptr), progressStyle(Progressbar::Style::CUT), progressFraction(0.0f), needsProgressUpdate(true)
	{
		setProgressColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	}

	Progressbar::~Progressbar()
	{
		delete[] progressVertices;
	}

	void Progressbar::performSubmittion(Renderer2D &renderer2d) const
	{
		BASE::performSubmittion(renderer2d);

		ensureProgressUpdate();
		if (this->texProgress && this->texProgress->isSplit())
			renderer2d.submit16(progressVertices, texProgress);
		else
			renderer2d.submit4(progressVertices, texProgress);
	}

	void Progressbar::setProgressTexture(const Texture *texture)
	{
		if (texture)
		{
			bool changed = (this->texProgress && this->texProgress->isSplit()) != texture->isSplit();
			if (changed)
			{
				delete[] vertices;

				if (texture->isSplit())
					vertices = new VertexPCT2D[16];
				else
					vertices = new VertexPCT2D[4];
			}
		}
		this->texProgress = texture;
		this->needsProgressUpdate = true;
	}

	void Progressbar::setProgressColor(const glm::vec4 &progressColor)
	{
		progressVertices[0].color = progressColor;
		progressVertices[1].color = progressColor;
		progressVertices[2].color = progressColor;
		progressVertices[3].color = progressColor;

		if (texProgress && texProgress->isSplit())
		{
			progressVertices[4].color = progressColor;
			progressVertices[5].color = progressColor;
			progressVertices[6].color = progressColor;
			progressVertices[7].color = progressColor;
			progressVertices[8].color = progressColor;
			progressVertices[9].color = progressColor;
			progressVertices[10].color = progressColor;
			progressVertices[11].color = progressColor;
			progressVertices[12].color = progressColor;
			progressVertices[13].color = progressColor;
			progressVertices[14].color = progressColor;
			progressVertices[15].color = progressColor;
		}
	}

	void Progressbar::ensureProgressUpdate() const
	{
		if (this->needsProgressUpdate)
		{
			// Update
			glm::vec2 size = getSize();
			switch (progressStyle)
			{
			default:
			case Progressbar::Style::CUT:
				if (texProgress && texProgress->isSplit())
				{
					float splitLeft = static_cast<float>(static_cast<const SplitTexture*>(texProgress)->getSplitLeft());
					float splitTop = static_cast<float>(static_cast<const SplitTexture*>(texProgress)->getSplitTop());
					float splitRight = static_cast<float>(static_cast<const SplitTexture*>(texProgress)->getSplitRight());
					float splitBottom = static_cast<float>(static_cast<const SplitTexture*>(texProgress)->getSplitBottom());

					// Stretch texCoords

					// Set x
					progressVertices[0].texCoord.x = progressTextureRect.left;
					progressVertices[4].texCoord.x = progressVertices[0].texCoord.x;
					progressVertices[8].texCoord.x = progressVertices[0].texCoord.x;
					progressVertices[12].texCoord.x = progressVertices[0].texCoord.x;

					progressVertices[1].texCoord.x = progressTextureRect.left + splitLeft;
					progressVertices[5].texCoord.x = progressVertices[1].texCoord.x;
					progressVertices[9].texCoord.x = progressVertices[1].texCoord.x;
					progressVertices[13].texCoord.x = progressVertices[1].texCoord.x;

					progressVertices[3].texCoord.x = progressTextureRect.left + progressTextureRect.width * this->progressFraction;
					progressVertices[7].texCoord.x = progressVertices[3].texCoord.x;
					progressVertices[11].texCoord.x = progressVertices[3].texCoord.x;
					progressVertices[15].texCoord.x = progressVertices[3].texCoord.x;

					progressVertices[2].texCoord.x = progressVertices[3].texCoord.x - splitRight;
					progressVertices[6].texCoord.x = progressVertices[2].texCoord.x;
					progressVertices[10].texCoord.x = progressVertices[2].texCoord.x;
					progressVertices[14].texCoord.x = progressVertices[2].texCoord.x;

					// Set y
					progressVertices[0].texCoord.y = progressTextureRect.top;
					progressVertices[1].texCoord.y = progressVertices[0].texCoord.y;
					progressVertices[2].texCoord.y = progressVertices[0].texCoord.y;
					progressVertices[3].texCoord.y = progressVertices[0].texCoord.y;

					progressVertices[4].texCoord.y = progressTextureRect.top + splitTop;
					progressVertices[5].texCoord.y = progressVertices[4].texCoord.y;
					progressVertices[6].texCoord.y = progressVertices[4].texCoord.y;
					progressVertices[7].texCoord.y = progressVertices[4].texCoord.y;

					progressVertices[12].texCoord.y = progressTextureRect.top + progressTextureRect.height;
					progressVertices[13].texCoord.y = progressVertices[12].texCoord.y;
					progressVertices[14].texCoord.y = progressVertices[12].texCoord.y;
					progressVertices[15].texCoord.y = progressVertices[12].texCoord.y;

					progressVertices[8].texCoord.y = progressVertices[12].texCoord.y - splitBottom;
					progressVertices[9].texCoord.y = progressVertices[8].texCoord.y;
					progressVertices[10].texCoord.y = progressVertices[8].texCoord.y;
					progressVertices[11].texCoord.y = progressVertices[8].texCoord.y;

					// Fix positions

					// Set x
					progressVertices[0].position.x = 0.0f;
					progressVertices[4].position.x = progressVertices[0].position.x;
					progressVertices[8].position.x = progressVertices[0].position.x;
					progressVertices[12].position.x = progressVertices[0].position.x;

					progressVertices[1].position.x = 0.0f + splitLeft;
					progressVertices[5].position.x = progressVertices[1].position.x;
					progressVertices[9].position.x = progressVertices[1].position.x;
					progressVertices[13].position.x = progressVertices[1].position.x;

					progressVertices[3].position.x = 0.0f + size.x;
					progressVertices[7].position.x = progressVertices[3].position.x;
					progressVertices[11].position.x = progressVertices[3].position.x;
					progressVertices[15].position.x = progressVertices[3].position.x;

					progressVertices[2].position.x = progressVertices[3].position.x - splitRight;
					progressVertices[6].position.x = progressVertices[2].position.x;
					progressVertices[10].position.x = progressVertices[2].position.x;
					progressVertices[14].position.x = progressVertices[2].position.x;

					// Set y
					progressVertices[0].position.y = 0.0f;
					progressVertices[1].position.y = progressVertices[0].position.y;
					progressVertices[2].position.y = progressVertices[0].position.y;
					progressVertices[3].position.y = progressVertices[0].position.y;

					progressVertices[4].position.y = 0.0f + splitTop;
					progressVertices[5].position.y = progressVertices[4].position.y;
					progressVertices[6].position.y = progressVertices[4].position.y;
					progressVertices[7].position.y = progressVertices[4].position.y;

					progressVertices[12].position.y = 0.0f + size.y;
					progressVertices[13].position.y = progressVertices[12].position.y;
					progressVertices[14].position.y = progressVertices[12].position.y;
					progressVertices[15].position.y = progressVertices[12].position.y;

					progressVertices[8].position.y = progressVertices[12].position.y - splitBottom;
					progressVertices[9].position.y = progressVertices[8].position.y;
					progressVertices[10].position.y = progressVertices[8].position.y;
					progressVertices[11].position.y = progressVertices[8].position.y;
				}
				else
				{
					// Stretch texCoords
					progressVertices[0].texCoord.x = progressTextureRect.left;
					progressVertices[0].texCoord.y = progressTextureRect.top;
					
					progressVertices[1].texCoord.x = progressTextureRect.left;
					progressVertices[1].texCoord.y = progressTextureRect.top + progressTextureRect.height;
					
					progressVertices[2].texCoord.x = progressTextureRect.left + progressTextureRect.width * this->progressFraction;
					progressVertices[2].texCoord.y = progressTextureRect.top + progressTextureRect.height;
					
					progressVertices[3].texCoord.x = progressTextureRect.left + progressTextureRect.width * this->progressFraction;
					progressVertices[3].texCoord.y = progressTextureRect.top;

					// Fix positions
					progressVertices[1].position.y = size.y;

					progressVertices[2].position.x = size.x;
					progressVertices[2].position.y = size.y;

					progressVertices[3].position.x = size.x;
				}
				break;
			case Progressbar::Style::STRETCH:
				if (texProgress && texProgress->isSplit())
				{
					float splitLeft = static_cast<float>(static_cast<const SplitTexture*>(texProgress)->getSplitLeft());
					float splitTop = static_cast<float>(static_cast<const SplitTexture*>(texProgress)->getSplitTop());
					float splitRight = static_cast<float>(static_cast<const SplitTexture*>(texProgress)->getSplitRight());
					float splitBottom = static_cast<float>(static_cast<const SplitTexture*>(texProgress)->getSplitBottom());

					// Fix texCoords

					// Set x
					progressVertices[0].texCoord.x = progressTextureRect.left;
					progressVertices[4].texCoord.x = progressVertices[0].texCoord.x;
					progressVertices[8].texCoord.x = progressVertices[0].texCoord.x;
					progressVertices[12].texCoord.x = progressVertices[0].texCoord.x;

					progressVertices[1].texCoord.x = progressTextureRect.left + splitLeft;
					progressVertices[5].texCoord.x = progressVertices[1].texCoord.x;
					progressVertices[9].texCoord.x = progressVertices[1].texCoord.x;
					progressVertices[13].texCoord.x = progressVertices[1].texCoord.x;

					progressVertices[3].texCoord.x = progressTextureRect.left + progressTextureRect.width;
					progressVertices[7].texCoord.x = progressVertices[3].texCoord.x;
					progressVertices[11].texCoord.x = progressVertices[3].texCoord.x;
					progressVertices[15].texCoord.x = progressVertices[3].texCoord.x;

					progressVertices[2].texCoord.x = progressVertices[3].texCoord.x - splitRight;
					progressVertices[6].texCoord.x = progressVertices[2].texCoord.x;
					progressVertices[10].texCoord.x = progressVertices[2].texCoord.x;
					progressVertices[14].texCoord.x = progressVertices[2].texCoord.x;

					// Set y
					progressVertices[0].texCoord.y = progressTextureRect.top;
					progressVertices[1].texCoord.y = progressVertices[0].texCoord.y;
					progressVertices[2].texCoord.y = progressVertices[0].texCoord.y;
					progressVertices[3].texCoord.y = progressVertices[0].texCoord.y;

					progressVertices[4].texCoord.y = progressTextureRect.top + splitTop;
					progressVertices[5].texCoord.y = progressVertices[4].texCoord.y;
					progressVertices[6].texCoord.y = progressVertices[4].texCoord.y;
					progressVertices[7].texCoord.y = progressVertices[4].texCoord.y;

					progressVertices[12].texCoord.y = progressTextureRect.top + progressTextureRect.height;
					progressVertices[13].texCoord.y = progressVertices[12].texCoord.y;
					progressVertices[14].texCoord.y = progressVertices[12].texCoord.y;
					progressVertices[15].texCoord.y = progressVertices[12].texCoord.y;

					progressVertices[8].texCoord.y = progressVertices[12].texCoord.y - splitBottom;
					progressVertices[9].texCoord.y = progressVertices[8].texCoord.y;
					progressVertices[10].texCoord.y = progressVertices[8].texCoord.y;
					progressVertices[11].texCoord.y = progressVertices[8].texCoord.y;

					// Stretch positions

					// Set x
					progressVertices[0].position.x = 0.0f;
					progressVertices[4].position.x = progressVertices[0].position.x;
					progressVertices[8].position.x = progressVertices[0].position.x;
					progressVertices[12].position.x = progressVertices[0].position.x;

					progressVertices[1].position.x = 0.0f + splitLeft;
					progressVertices[5].position.x = progressVertices[1].position.x;
					progressVertices[9].position.x = progressVertices[1].position.x;
					progressVertices[13].position.x = progressVertices[1].position.x;

					progressVertices[3].position.x = 0.0f + size.x * this->progressFraction;
					progressVertices[7].position.x = progressVertices[3].position.x;
					progressVertices[11].position.x = progressVertices[3].position.x;
					progressVertices[15].position.x = progressVertices[3].position.x;

					progressVertices[2].position.x = progressVertices[3].position.x - splitRight;
					progressVertices[6].position.x = progressVertices[2].position.x;
					progressVertices[10].position.x = progressVertices[2].position.x;
					progressVertices[14].position.x = progressVertices[2].position.x;

					// Set y
					progressVertices[0].position.y = 0.0f;
					progressVertices[1].position.y = progressVertices[0].position.y;
					progressVertices[2].position.y = progressVertices[0].position.y;
					progressVertices[3].position.y = progressVertices[0].position.y;

					progressVertices[4].position.y = 0.0f + splitTop;
					progressVertices[5].position.y = progressVertices[4].position.y;
					progressVertices[6].position.y = progressVertices[4].position.y;
					progressVertices[7].position.y = progressVertices[4].position.y;

					progressVertices[12].position.y = 0.0f + size.y;
					progressVertices[13].position.y = progressVertices[12].position.y;
					progressVertices[14].position.y = progressVertices[12].position.y;
					progressVertices[15].position.y = progressVertices[12].position.y;

					progressVertices[8].position.y = progressVertices[12].position.y - splitBottom;
					progressVertices[9].position.y = progressVertices[8].position.y;
					progressVertices[10].position.y = progressVertices[8].position.y;
					progressVertices[11].position.y = progressVertices[8].position.y;
				}
				else
				{
					// Fix texCoords
					progressVertices[0].texCoord.x = progressTextureRect.left;
					progressVertices[0].texCoord.y = progressTextureRect.top;

					progressVertices[1].texCoord.x = progressTextureRect.left;
					progressVertices[1].texCoord.y = progressTextureRect.top + progressTextureRect.height;

					progressVertices[2].texCoord.x = progressTextureRect.left + progressTextureRect.width;
					progressVertices[2].texCoord.y = progressTextureRect.top + progressTextureRect.height;

					progressVertices[3].texCoord.x = progressTextureRect.left + progressTextureRect.width;
					progressVertices[3].texCoord.y = progressTextureRect.top;

					// Stretch positions
					progressVertices[1].position.y = size.y;

					progressVertices[2].position.x = size.x * this->progressFraction;
					progressVertices[2].position.y = size.y;

					progressVertices[3].position.x = size.x * this->progressFraction;
				}
				break;
			}

			// Mark as updated
			this->needsProgressUpdate = false;
		}
	}

	void Progressbar::onSizeChanged(const glm::vec2 &size)
	{
		BASE::onSizeChanged(size);
		this->needsProgressUpdate = true;
	}

	void Progressbar::onProgressChanged()
	{

	}
}