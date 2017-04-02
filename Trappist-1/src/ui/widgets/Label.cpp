#include <Trappist-1\ui\widgets\Label.hpp>

#include <Trappist-1\Graphics\Renderer2D.hpp>

#include <iostream>

namespace ui
{
	Label::Label()
		: BASE(), thickness(0.0f), outlineOffset(0.0f, 0.0f), outlineBlur(0.0f), needsUpdate(true), textAlignment(Alignment::CENTER), autoSizeMode(AutoSizeMode::NONE), padding(0.0f, 0.0f), multiLine(true)
	{	}

	Label::~Label()
	{	}

	void Label::performSubmittion(Renderer2D &renderer2d) const
	{
		BASE::performSubmittion(renderer2d);
		ensureUpdate();
		renderer2d.submitLabel(*this);
	}

	void Label::onSizeChanged(const glm::vec2 &size)
	{
		BASE::onSizeChanged(size);
		needsUpdate = true;
	}

	void Label::calculate() const
	{
		if (!font)
			return;

		// Create Line-Structure
		characterPositions.clear();
		//lineBases.clear();
		//vertices.clear();
		//indices.clear();
		lines.clear();
		lines.resize(1);
		glm::vec2 maxSize = getSize();

		CharacterInfo nullCharInfo{};
		const CharacterInfo *currCharInfo = &nullCharInfo;
		unsigned short lastCharAscii = 0;
		unsigned short currCharAscii = 0;

		std::string currentWord;
		float currWordWidth = 0.0f;
		unsigned int currLine = 0;
		unsigned int characterCount = 0;
		unsigned int spaceCount = 0;
		textIndexCount = 0;

		if (isAutoSizeMode(AutoSizeMode::X))
			maxSize.x = 0.0f;

		for (size_t i = 0; i < text.length(); ++i)
		{
			// Get information about the current glyph
			currCharAscii = static_cast<unsigned short>(text[i]);
			currCharInfo = font->getCharacterInfo(currCharAscii);

			// If first iteration in new line
			if (currWordWidth == 0.0f && lines[currLine].width == 0)
				currWordWidth -= currCharInfo->offset.x * fontSize;

			// Add letter to word and increase wordWidth
			float nextWordWidth = currWordWidth + (currCharInfo->advance - font->getKerningAmount(lastCharAscii, currCharAscii)) * static_cast<float>(fontSize);

			// If line fits
			if (isAutoSizeMode(AutoSizeMode::X) || ((this->lines[currLine].width + nextWordWidth) < maxSize.x))
			{
				switch (currCharAscii)
				{
				case ' ':
					// Add word to line and clear
					this->lines[currLine].text += currentWord;
					this->lines[currLine].text += static_cast<char>(currCharAscii);
					currentWord.clear();

					// Add word length to line length and clear
					this->lines[currLine].width += static_cast<unsigned int>(nextWordWidth);
					currWordWidth = 0.0f;

					++spaceCount;
					break;
				case '\n':
					if (isMultiLine())
					{
						// Add word to line and clear
						this->lines[currLine].text += currentWord;
						currentWord.clear();

						// Add word length to line length and clear
						this->lines[currLine].width += static_cast<unsigned int>(currWordWidth);
						currWordWidth = 0.0f;

						// Wrap
						this->lines.push_back({ "", 0 });
						++currLine;
					}
					break;
				default:
					if (i == text.size() - 1)
					{
						this->lines[currLine].text += currentWord;
						this->lines[currLine].text += static_cast<char>(currCharAscii);

						this->lines[currLine].width += static_cast<unsigned int>(nextWordWidth);

						++characterCount;
					}
					else
					{
						// Add char to word
						currentWord += static_cast<char>(currCharAscii);
						currWordWidth = nextWordWidth;
						++characterCount;
					}
					break;
				}
			}
			else
			{
				switch (currCharAscii)
				{
				case ' ':
					// Add word to line and clear
					this->lines[currLine].text += currentWord;
					currentWord.clear();

					// Add word length to line length and clear
					this->lines[currLine].width += static_cast<unsigned int>(currWordWidth);
					currWordWidth = 0.0f;

					// Warp
					this->lines.push_back({ "", 0 });
					++currLine;
					break;
					//case '\n': Impossible because '\n' has no width (last char should have made the break)
					break;
				default:
					// If the current line does not have any word pushed back (wrap letter)
					if (this->lines[currLine].text.size() == 0)
					{
						// Add word to line and clear
						this->lines[currLine].text += currentWord;
						currentWord.clear();

						// Add word length to line length and clear
						this->lines[currLine].width += static_cast<unsigned int>(currWordWidth);
						// clear to end

						// Warp (with current char)
						this->lines.push_back({ std::string(1, static_cast<char>(currCharAscii)), static_cast<unsigned int>(nextWordWidth - currWordWidth) });
						++currLine;

						++characterCount;

						currWordWidth = 0.0f;
					}
					else
					{
						// Wrap
						this->lines.push_back({ "", 0 });
						++currLine;

						// Add word to line and clear
						this->lines[currLine].text += currentWord;
						this->lines[currLine].text += static_cast<char>(currCharAscii);
						currentWord.clear();

						// Add word length to line length and clear
						this->lines[currLine].width += static_cast<unsigned int>(nextWordWidth);
						currWordWidth = 0.0f;

						++characterCount;
					}
					break;
				}
			}

			lastCharAscii = currCharAscii;
		}

		this->lineCount = lines.size();

		// If auto size x is enabled, assign x size as biggest line
		if (isAutoSizeMode(AutoSizeMode::X))
		{
			for (size_t i = 0; i < lines.size(); ++i)
			{
				if (lines[i].text.size() == 0)
					++textIndexCount;
				else
					textIndexCount += lines[i].text.size();
				if (maxSize.x < lines[i].width)
					maxSize.x = static_cast<float>(lines[i].width);
			}
		}


		// If auto size y is enabled, assign y size as line count
		if (isAutoSizeMode(AutoSizeMode::Y))
			maxSize.y = static_cast<float>(lines.size() * getLineHeight());

		// Resize
		vertices.resize(characterCount * 4);
		indices.resize(characterCount * 6);

		characterPositions.reserve(characterCount + spaceCount + lines.size());

		// Create Vertex-Structure
		glm::vec2 cursor(padding);

		int index = 0;
		for (size_t i = 0; i < lines.size(); ++i)
		{
			// If centered, pose cursor to right place
			switch (textAlignment)
			{
			default:
			case Alignment::LEFT:
				break;
			case Alignment::CENTER:
				cursor.x += static_cast<float>(maxSize.x - this->lines[i].width) * 0.5f;
				break;
			case Alignment::RIGHT:
				cursor.x += static_cast<float>(maxSize.x - this->lines[i].width);
				break;
			}

			for (size_t ch = 0; ch < lines[i].text.length(); ++ch)
			{
				//unsigned short c = static_cast<unsigned char>(lines[i].text[ch]);
				currCharAscii = static_cast<unsigned char>(lines[i].text[ch]);

				currCharInfo = font->getCharacterInfo(currCharAscii);

				if (ch == 0)
					cursor.x -= currCharInfo->offset.x * fontSize;

				glm::vec2 p(cursor.x + currCharInfo->offset.x * fontSize, cursor.y + currCharInfo->offset.y * fontSize);
				glm::vec2 pm(p.x + currCharInfo->size.x * fontSize, p.y + currCharInfo->size.y * fontSize);

				// Add information only if it's not a space
				if (currCharAscii != ' ')
				{
					glm::vec2 t(currCharInfo->texCoord.x, currCharInfo->texCoord.y);
					glm::vec2 tm(currCharInfo->texCoord.x + currCharInfo->texSize.x, currCharInfo->texCoord.y + currCharInfo->texSize.y);

					vertices[index * 4 + 0] = VertexPCT2D{ p, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), t };
					vertices[index * 4 + 1] = VertexPCT2D{ glm::vec2(pm.x, p.y), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(tm.x, t.y) };
					vertices[index * 4 + 2] = VertexPCT2D{ pm, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), tm };
					vertices[index * 4 + 3] = VertexPCT2D{ glm::vec2(p.x, pm.y), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(t.x, tm.y) };
					//vertices.push_back(VertexPCT2D{ p, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), t });
					//vertices.push_back(VertexPCT2D{ glm::vec2(pm.x, p.y), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(tm.x, t.y) });
					//vertices.push_back(VertexPCT2D{ pm, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), tm });
					//vertices.push_back(VertexPCT2D{ glm::vec2(p.x, pm.y), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(t.x, tm.y) });

					indices[index * 6 + 0] = 0 + index * 4;
					indices[index * 6 + 1] = 3 + index * 4;
					indices[index * 6 + 2] = 2 + index * 4;
					indices[index * 6 + 3] = 2 + index * 4;
					indices[index * 6 + 4] = 1 + index * 4;
					indices[index * 6 + 5] = 0 + index * 4;
					//indices.push_back(0 + index * 4);
					//indices.push_back(3 + index * 4);
					//indices.push_back(2 + index * 4); // order needs to be reverse because the faces will be flipped
					//indices.push_back(2 + index * 4);
					//indices.push_back(1 + index * 4);
					//indices.push_back(0 + index * 4);

					++index;
				}
				characterPositions.push_back(glm::vec2(cursor.x, p.y));

				// Incease cursor x
				cursor.x += (currCharInfo->advance - font->getKerningAmount(lastCharAscii, currCharAscii)) * static_cast<float>(fontSize);

				//characterPositions.push_back(glm::vec2(p.x, p.y));

				lastCharAscii = currCharAscii;
			}

			characterPositions.push_back(glm::vec2(cursor.x, cursor.y));

			// Wrap
			cursor.x = padding.x;
			cursor.y += font->getLineHeight() * fontSize;
		}

		if (isAutoSizeMode(AutoSizeMode::X) || isAutoSizeMode(AutoSizeMode::Y))
		{
			// Add padding to max size
			maxSize.x += padding.x * 2.0f;
			maxSize.y += padding.y * 2.0f;
			const_cast<Label*>(this)->setSize(maxSize);
		}
	}

	glm::vec2 Label::getCharacterPosition(size_t index) const
	{
		if (index >= characterPositions.size())
			return characterPositions[characterPositions.size() - 1];
		return characterPositions[index];
	}

	size_t Label::getLineIndex(size_t characterIndex) const
	{
		if (characterIndex > getText().size())
			return getText().size();
		// Add size+1 because there are one more indices than there are characters
		size_t index = 0, passedCharacters = 0;
		while (characterIndex >= (passedCharacters += lines[index].text.size() + 1))
			++index;
		return index;
	}

	size_t Label::getStartLineIndex(size_t characterIndex) const
	{
		size_t index = 0, passedCharacters = 0;
		for (; characterIndex >= (passedCharacters += lines[index].text.size()); ++index);
		return passedCharacters - lines[index].text.size();
	}

	size_t Label::getEndLineIndex(size_t characterIndex) const
	{
		size_t index = 0, passedCharacters = 0;
		for (; characterIndex >= (passedCharacters += lines[index].text.size()); ++index);
		return passedCharacters - 1;
	}

	//float Label::getLineBase(size_t index) const
	//{
	//	if (index >= lineBases.size())
	//		return lineBases[lineBases.size() - 1];
	//	return lineBases[index];
	//}

	void Label::ensureUpdate() const
	{
		if (needsUpdate)
		{
			calculate();
			needsUpdate = false;
		}
	}
}