#include <Trappist-1\ui\widgets\TextBox.hpp>

#include <Trappist-1\Graphics\Renderer2D.hpp>
#include <Trappist-1\Util\Input.hpp>

#include <iostream>

namespace ui
{
	TextBox::TextBox()
		: BASE(), cursorBlinkInterval(TextBox::DEFAULT_CURSOR_BLINK_INTERVAL), drawCursor(true), showHint(true), maxCharacterCount(0xFFFFFFFF)
	{
		setCursorWidth(TextBox::DEFAULT_CURSOR_WIDTH);
		setCursorColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		setSelectionColor(glm::vec4(0.0f, 0.2f, 1.0f, 0.4f));
	}

	TextBox::~TextBox()
	{	}

	void TextBox::performSubmittion(Renderer2D &renderer2d) const
	{
		auto bounds = getGlobalBounds();
		renderer2d.pushScissor(static_cast<GLint>(bounds.left), static_cast<GLint>(bounds.top), static_cast<GLint>(bounds.width), static_cast<GLint>(bounds.height));

		BASE::performSubmittion(renderer2d);

		if (selectionExists())
		{
			ensureSelectionUpdate();
			renderer2d.submit4(selectionVertices);
			renderer2d.submit4(selectionMidVertices);
			renderer2d.submit4(selectionEndVertices);
		}

		if (isFocused() && drawCursor)
		{
			ensureCursorUpdate();
			renderer2d.submit4(cursorVertices);
		}

		if (cursorBlinkInterval > 0.0f)
		{
			if (blinker.elapsedMilliseconds() * 0.001f > cursorBlinkInterval)
			{
				blinker.reset();
				drawCursor = !drawCursor;
			}
		}

		renderer2d.popScissor();
	}

	void TextBox::setMaxCharacterCount(size_t count)
	{
		this->maxCharacterCount = count;
		if (getText().size() > count)
			getTextRef().erase(getText().end() - count, getText().end());
	}

	void TextBox::setCursorPosition(size_t offset, bool makeSelection)
	{
		cursorTextIndex = offset > (getText().size()) ? (getText().size()) : offset; //clamp 0 : text.getString().getSize() + 1 -> cursorTextIndex
		this->needsCursorUpdate = true;
		this->needsSelectionUpdate = true;
		if (!makeSelection)
			removeSelection();
	}

	void TextBox::moveCursor(int steps, bool makeSelection)
	{
		setCursorPosition(static_cast<int>(cursorTextIndex) + steps < 0 ? 0u : cursorTextIndex + steps, makeSelection);
	}

	void TextBox::setCursorPosition(const glm::vec2 &offset, bool selectionStart)
	{
		glm::vec2 currDiff(0.0f, 0.0f);
		glm::vec2 lastDiff(0.0f, 0.0f);
		//float currDiff = 0.0f;
		//float lastDiff = 0.0f;
		size_t itResult = 0;
		for (size_t i = 0; i < getText().size() + 2; i++)
		{
			lastDiff = currDiff;

			currDiff.x = getCharacterPosition(i).x - offset.x;
			//float lineBase = getLineBase(i - 1);
			float lineBase = getPadding().y + getLineIndex(i - 1) * getLineHeight();
			currDiff.y = lineBase - offset.y;
			if (currDiff.x < 0.0f)
				currDiff.x *= -1;

			if (i != 0)
			{
				if (lastDiff.x <= currDiff.x && glm::abs(currDiff.y) < getLineHeight())
				{
					itResult = i - 1;
					break;
				} //else continue
			} //else continue
		}

		if (selectionStart)
			selectionIndex = itResult;
		cursorTextIndex = itResult;

		//updateCursorPosition();
		//updateSelection();
		this->needsCursorUpdate = true;
		this->needsSelectionUpdate = true;
	}

	void TextBox::processKeyEvent(sf::Keyboard::Key key, bool pressed, bool alt, bool control, bool shift, bool system)
	{
		if (selectionExists()) //delete selection
		{
			if (key == sf::Keyboard::Key::Delete || key == sf::Keyboard::Key::BackSpace)
			{
				if (cursorTextIndex < selectionIndex)
				{
					getTextRef().erase(cursorTextIndex, selectionIndex - cursorTextIndex);
				}
				else
				{
					getTextRef().erase(selectionIndex, cursorTextIndex - selectionIndex);
					moveCursor(selectionIndex - cursorTextIndex, false); //difference must be negative (to move left)
				}

				//updateCursorPosition();
				this->needsCursorUpdate = true;
				removeSelection();

				return;
			}
		}

		switch (key)
		{
		case sf::Keyboard::Key::BackSpace:
			if (cursorTextIndex > 0)
			{
				getTextRef().erase(cursorTextIndex - 1, 1);
				moveCursor(-1, false);
			}
			break;
		case sf::Keyboard::Key::Delete:
			if (cursorTextIndex < getText().size())
			{
				getTextRef().erase(cursorTextIndex, 1);
				//updateCursorPosition();
				this->needsCursorUpdate = true;
			}
			break;
		case sf::Keyboard::Key::Left:
			//if (mods == Keyboard::Mod::SHIFT)
			if (shift)
				moveCursor(-1, true);
			else
				if (selectionExists())
					if (cursorTextIndex > selectionIndex) // cursor is right
						setCursorPosition(selectionIndex, false);
					else //cursor is left
						removeSelection();
				else
					moveCursor(-1, false);
			break;
		case sf::Keyboard::Key::Right:
			//if (mods == Keyboard::Mod::SHIFT)
			if (shift)
				moveCursor(1, true);
			else
				if (selectionExists())
					if (cursorTextIndex < selectionIndex) // cursor is left
						setCursorPosition(selectionIndex, false);
					else //cursor is right
						removeSelection();
				else
					moveCursor(1, false);
			break;
		case sf::Keyboard::Key::Home:
			//if (mods == Keyboard::Mod::SHIFT)
			if (shift)
				setCursorPosition(static_cast<size_t>(0u), true);
			else
				setCursorPosition(static_cast<size_t>(0u), false);
			break;
		case sf::Keyboard::Key::End:
			//if (mods == Keyboard::Mod::SHIFT)
			if(shift)
				setCursorPosition(getText().size(), true);
			else
				setCursorPosition(getText().size(), false);
			break;
		case sf::Keyboard::Key::Return:
			processUnicode('\n');
			break;
		}

		checkHintVisibility();
	}

	void TextBox::processUnicode(unsigned short unicode)
	{
		if (getText().size() >= getMaxCharacterCount())
			return;

		std::string temp = getText();

		if (selectionExists()) //first delete selection
		{
			if (cursorTextIndex < selectionIndex)
			{
				temp.erase(cursorTextIndex, selectionIndex - cursorTextIndex);
			}
			else
			{
				temp.erase(selectionIndex, cursorTextIndex - selectionIndex);
				moveCursor(selectionIndex - cursorTextIndex, false); //difference must be negative (to move left)
			}
		}

		temp.insert(cursorTextIndex, 1, static_cast<char>(unicode));

		setText(temp);

		moveCursor(1, false);

		checkHintVisibility();
	}

	void TextBox::checkHintVisibility()
	{
		if (isEmpty() && !showHint)
			showHint = true;
		else if (!isEmpty() && showHint)
			showHint = false;
	}

	void TextBox::removeSelection()
	{
		selectionIndex = cursorTextIndex;
		this->needsSelectionUpdate = true;
	}

	void TextBox::onSizeChanged(const glm::vec2 &size)
	{
		BASE::onSizeChanged(size);

		//float yBottom = size.y - 2.0f;
		//
		//cursorVertices[1].position.y = yBottom;
		//cursorVertices[2].position.y = yBottom;
		//
		//selectionVertices[1].position.y = yBottom;
		//selectionVertices[2].position.y = yBottom;
		this->needsCursorUpdate = true;
		this->needsSelectionUpdate = true;
	}

	void TextBox::onMouseButtonEvent_decl
	{
		BASE::onMouseButtonEvent(button, pressed);

		if(pressed)
			if (isEnabled())
			{
				FloatRect bounds = getGlobalBounds();
				setCursorPosition(glm::vec2(static_cast<float>(Input::getMousePos().x) - bounds.left, static_cast<float>(Input::getMousePos().y) - bounds.top), true);
			}
	}

	void TextBox::onCursorPositionEvent()
	{
		BASE::onCursorPositionEvent();

		if (isEnabled() && isPressed())
		{
			FloatRect bounds = getGlobalBounds();
			setCursorPosition(glm::vec2(static_cast<float>(Input::getMousePos().x) - bounds.left, static_cast<float>(Input::getMousePos().y) - bounds.top), false);
		}
	}

	void TextBox::onKeyEvent_decl
	{
		BASE::onKeyEvent(key, pressed, alt, control, shift, system);

		if(isEnabled() /*&& isFocused()*/ && pressed)
			processKeyEvent(key, pressed, alt, control, shift, system);
	}

	void TextBox::onCharEvent_decl
	{
		BASE::onCharEvent(codepoint);

		if (isEnabled() /*&& isFocused()*/)
			processUnicode(static_cast<unsigned short>(codepoint));
	}

	void TextBox::ensureCursorUpdate() const
	{
		if (this->needsCursorUpdate)
		{
			// Update

			glm::vec2 pos = getCharacterPosition(cursorTextIndex);

			float cursorWidth = getCursorWidth();
			float left = pos.x - cursorWidth * 0.5f;
			float right = pos.x + cursorWidth * 0.5f;

			float cursorHeight = static_cast<float>(getLineHeight());
			float top = getPadding().y + (getLineIndex(cursorTextIndex)) * getLineHeight();
			float bottom = top + cursorHeight;

			cursorVertices[0].position.x = left;
			cursorVertices[1].position.x = left;
			cursorVertices[2].position.x = right;
			cursorVertices[3].position.x = right;

			cursorVertices[0].position.y = top;
			cursorVertices[1].position.y = bottom;
			cursorVertices[2].position.y = bottom;
			cursorVertices[3].position.y = top;

			// Mark as updated
			this->needsCursorUpdate = false;
		}
	}

	void TextBox::ensureSelectionUpdate() const
	{
		if (this->needsSelectionUpdate)
		{
			// Update

			glm::vec2 size = getSize();

			size_t cursorLineIndex = getLineIndex(cursorTextIndex);
			size_t selectionLineIndex = getLineIndex(selectionIndex);

			int lineDiff = glm::abs(static_cast<int>(cursorLineIndex - selectionLineIndex));
			if (lineDiff == 0)
			{
				float left = getCharacterPosition(cursorTextIndex).x;
				float right = getCharacterPosition(selectionIndex).x;

				float top = getPadding().y + (getLineIndex(cursorTextIndex)) * getLineHeight();//getLineBase(cursorTextIndex);
				float bottom = top + getLineHeight();

				selectionVertices[0].position.x = left;
				selectionVertices[1].position.x = left;
				selectionVertices[2].position.x = right;
				selectionVertices[3].position.x = right;

				selectionVertices[0].position.y = top;
				selectionVertices[1].position.y = bottom;
				selectionVertices[2].position.y = bottom;
				selectionVertices[3].position.y = top;

				selectionEndVertices[2].position.x = selectionEndVertices[0].position.x;
				selectionEndVertices[3].position.x = selectionEndVertices[0].position.x;

				selectionMidVertices[2].position.x = selectionMidVertices[0].position.x;
				selectionMidVertices[3].position.x = selectionMidVertices[0].position.x;
			}
			else
			{
				float left1 = getCharacterPosition(selectionIndex).x;

				float right1;
				float right2;
				if (cursorTextIndex < selectionIndex)
				{
					right2 = size.x - getPadding().x;
					right1 = getPadding().x;
				}
				else
				{
					right1 = size.x - getPadding().x;
					right2 = getPadding().x;
				}

				float top1 = getPadding().y + (selectionLineIndex) * getLineHeight();//getLineBase(cursorTextIndex);
				float bottom1 = top1 + getLineHeight();

				float left2 = getCharacterPosition(cursorTextIndex).x;

				float top2 = getPadding().y + (cursorLineIndex) * getLineHeight();//getLineBase(cursorTextIndex);
				float bottom2 = top2 + getLineHeight();

				selectionVertices[0].position.x = left1;
				selectionVertices[1].position.x = left1;
				selectionVertices[2].position.x = right1;
				selectionVertices[3].position.x = right1;

				selectionVertices[0].position.y = top1;
				selectionVertices[1].position.y = bottom1;
				selectionVertices[2].position.y = bottom1;
				selectionVertices[3].position.y = top1;

				selectionEndVertices[0].position.x = left2;
				selectionEndVertices[1].position.x = left2;
				selectionEndVertices[2].position.x = right2;
				selectionEndVertices[3].position.x = right2;

				selectionEndVertices[0].position.y = top2;
				selectionEndVertices[1].position.y = bottom2;
				selectionEndVertices[2].position.y = bottom2;
				selectionEndVertices[3].position.y = top2;

				// Make mid selection
				if (lineDiff > 1)
				{
					float left3 = getPadding().x;
					float right3 = size.x - left3;

					float top3;
					float bottom3;

					if (cursorTextIndex < selectionIndex)
					{
						top3 = getPadding().y + (cursorLineIndex + 1) * getLineHeight();
						bottom3 = getPadding().y + (selectionLineIndex) * getLineHeight();
					}
					else
					{
						bottom3 = getPadding().y + (cursorLineIndex) * getLineHeight();
						top3 = getPadding().y + (selectionLineIndex + 1) * getLineHeight();
					}

					selectionMidVertices[0].position.x = left3;
					selectionMidVertices[1].position.x = left3;
					selectionMidVertices[2].position.x = right3;
					selectionMidVertices[3].position.x = right3;

					selectionMidVertices[0].position.y = top3;
					selectionMidVertices[1].position.y = bottom3;
					selectionMidVertices[2].position.y = bottom3;
					selectionMidVertices[3].position.y = top3;
				}
				else
				{
					selectionMidVertices[2].position.x = selectionMidVertices[0].position.x;
					selectionMidVertices[3].position.x = selectionMidVertices[0].position.x;
				}
			}

			// Mark as updated
			this->needsSelectionUpdate = false;
		}
	}
}