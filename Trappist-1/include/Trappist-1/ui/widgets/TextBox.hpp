#pragma once

#include "Trappist-1\ui\widgets\Label.hpp"

#include "Trappist-1\util\Timer.hpp"

namespace ui
{
	class TextBox : public Label
	{
		using BASE = Label;
		static constexpr float DEFAULT_CURSOR_WIDTH = 2.0f;
		static constexpr float DEFAULT_CURSOR_BLINK_INTERVAL = 0.5f;
	public:
		TextBox();
		virtual ~TextBox();

		size_t getMaxCharacterCount() const;
		void setMaxCharacterCount(size_t count);

		float getCursorBlinkInterval() const;
		void setCursorBlinkInterval(float blinkIntervalSecs);

		float getCursorWidth() const;
		void setCursorWidth(float width);

		const glm::vec4& getCursorColor() const;
		void setCursorColor(const glm::vec4 &color);

		const glm::vec4& getSelectionColor() const;
		void setSelectionColor(const glm::vec4 &color);

		//const sf::String& getHintString() const;
		//void setHintString(const sf::String& string);

		//sf::Uint32 getHintStyle() const;
		//void setHintStyle(sf::Uint32 style);
		//
		//const sf::Color& getHintColor() const;
		//void setHintColor(const sf::Color& color);

		void moveCursor(int steps, bool makeSelection);
		void setCursorPosition(size_t offset, bool makeSelection);

		inline bool selectionExists() const;
		inline bool isEmpty() const;
	protected:
		virtual void performSubmittion(Renderer2D &renderer2d) const override;

		virtual void onSizeChanged(const glm::vec2 &size) override;

		virtual void onMouseButtonEvent_decl override;
		virtual void onCursorPositionEvent_decl override;
		virtual void onKeyEvent_decl override;
		virtual void onCharEvent_decl override;

		//virtual void updatePosition() override;
		//virtual void updateAlignment() override;

		void checkHintVisibility();
		void setCursorPosition(const glm::vec2 &offset, bool selectionStart);
		void processUnicode(unsigned short unicode);
		void processKeyEvent(sf::Keyboard::Key key, bool pressed, bool alt, bool control, bool shift, bool system);
		void removeSelection();
		//void updateSelection();
		//void updateCursorPosition();

		void ensureCursorUpdate() const;
		void ensureSelectionUpdate() const;
	protected:
		mutable VertexPCT2D selectionVertices[4];
		mutable VertexPCT2D selectionMidVertices[4];
		mutable VertexPCT2D selectionEndVertices[4];
		mutable VertexPCT2D cursorVertices[4];
		size_t maxCharacterCount;
		float cursorBlinkInterval;
		size_t cursorTextIndex;
		size_t selectionIndex;
		std::string hintText;
		bool showHint;
		//sf::Text txtHint;
	private:
		mutable bool drawCursor;
		//mutable bool needsTextBoxUpdate;
		mutable bool needsSelectionUpdate;
		mutable bool needsCursorUpdate;
		mutable Timer blinker;
	};

	// Inline



	inline size_t TextBox::getMaxCharacterCount() const
	{
		return this->maxCharacterCount;
	}

	inline float TextBox::getCursorBlinkInterval() const
	{
		return this->cursorBlinkInterval;
	}

	inline void TextBox::setCursorBlinkInterval(float blinkIntervalSecs)
	{
		this->cursorBlinkInterval = blinkIntervalSecs;
	}

	inline float TextBox::getCursorWidth() const
	{
		return cursorVertices[2].position.x - cursorVertices[0].position.x;
	}

	inline void TextBox::setCursorWidth(float width)
	{
		cursorVertices[2].position.x = cursorVertices[0].position.x + width;
		cursorVertices[3].position.x = cursorVertices[1].position.x + width;
	}

	inline const glm::vec4& TextBox::getCursorColor() const
	{
		return cursorVertices[0].color;
	}

	inline void TextBox::setCursorColor(const glm::vec4 &color)
	{
		cursorVertices[0].color = color;
		cursorVertices[1].color = color;
		cursorVertices[2].color = color;
		cursorVertices[3].color = color;
	}

	inline const glm::vec4& TextBox::getSelectionColor() const
	{
		return selectionVertices[0].color;
	}

	inline void TextBox::setSelectionColor(const glm::vec4 &color)
	{
		selectionVertices[0].color = color;
		selectionVertices[1].color = color;
		selectionVertices[2].color = color;
		selectionVertices[3].color = color;

		selectionMidVertices[0].color = color;
		selectionMidVertices[1].color = color;
		selectionMidVertices[2].color = color;
		selectionMidVertices[3].color = color;

		selectionEndVertices[0].color = color;
		selectionEndVertices[1].color = color;
		selectionEndVertices[2].color = color;
		selectionEndVertices[3].color = color;
	}

	inline bool TextBox::selectionExists() const
	{
		return cursorTextIndex != selectionIndex;
	}

	inline bool TextBox::isEmpty() const
	{
		return showHint || getText().size() == 0;
	}
}