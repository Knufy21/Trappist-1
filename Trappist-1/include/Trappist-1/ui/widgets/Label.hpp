#pragma once

#include <Trappist-1\ui\widgets\Image.hpp>
#include <Trappist-1\graphics\fonts\Font.hpp>

#include <string>

namespace ui
{
	class Label : public Image
	{
		using BASE = Image;
	public:
		enum class Alignment : char { LEFT = 0, CENTER = 1, RIGHT = 2 };
		enum class AutoSizeMode : char { NONE = 0, X = 1, Y = 2, BOTH = 3 };
		struct Line
		{
			std::string text;
			unsigned int width;
		};

		Label();

		virtual ~Label();

		// Returns the text of the label.
		std::string &getTextRef();

		// Returns the const text of the label.
		const std::string &getText() const;
		
		// Sets the text of the label.
		void setText(const std::string &text);
		
		// Returns the font of the label used to render the text.
		const Font &getFont() const;

		// Sets the font of the label used to render the text.
		void setFont(const Font &font);
		
		// Returns the size of the font used to render the text.
		unsigned int getFontSize() const;

		// Sets the size of the font used to render the text.
		void setFontSize(unsigned int fontSize);
		
		// Returns the count of lines in which the text is being rendered.
		unsigned int getLineCount() const;

		// Returns the line height of the text in pixels.
		unsigned int getLineHeight() const;
		
		// Returns whether the text can have multiple lines.
		bool isMultiLine() const;

		// Sets whether the text can have multiple lines.
		void setMultiLine(bool multiLine);

		// Returns the alignment in which the text will be displayed.
		Alignment getTextAlignment() const;

		// Sets the alignment in which the text will be displayed.
		void setTextAlignment(Alignment textAligment);

		bool isAutoSizeMode(AutoSizeMode autoSizeMode) const;

		AutoSizeMode getAutoSizeMode() const;

		void setAutoSizeMode(AutoSizeMode autoSizeMode);

		// Returns the thickness of the text.
		float getTextThickness() const;

		// Sets the thickness of the text.
		void setTextThickness(float thickness);
		
		// Returns the color of the text.
		const glm::vec4 &getTextColor() const;

		// Sets the color of the text.
		void setTextColor(const glm::vec4 &color);
		
		// Returns the outline thickness of the text.
		float getTextOutlineThickness() const;

		// Sets the outline thickness of the text.
		void setTextOutlineThickness(float outlineThickness);
		
		// Returns the outline color of the text.
		const glm::vec4 &getTextOutlineColor() const;

		// Sets the outline color of the text.
		void setTextOutlineColor(const glm::vec4 &outlineColor);
		
		// Returns the ouline offset of the text.
		const glm::vec2 &getTextOutlineOffset() const;

		// Returns the outline offset of the text.
		void setTextOutlineOffset(const glm::vec2 &outlineOffset);
		
		// Returns the ouline blur of the text.
		float getTextOutlineBlur() const;

		// Sets the ouline blur of the text.
		void setTextOutlineBlur(float outlineBlur);
		
		// Returns the vertices of the text.
		const std::vector<VertexPCT2D> &getTextVertices() const;

		// Returns the indices of the text vertices.
		const std::vector<GLuint> &getTextIndices() const;

		// Return the position of the character at the specified index.
		glm::vec2 getCharacterPosition(size_t index) const;

		size_t getLineIndex(size_t characterIndex) const;

		size_t getStartLineIndex(size_t characterIndex) const;

		size_t getEndLineIndex(size_t characterIndex) const;

		const glm::vec2 getPadding() const;

		size_t Label::getTextIndexCount() const;

	protected:
		virtual void performSubmittion(Renderer2D &renderer2d) const override;
		virtual void onSizeChanged(const glm::vec2 &size) override;
	private:
		void calculate() const;
		void ensureUpdate() const;

		mutable bool needsUpdate;

		std::string text;
		const Font *font;
		unsigned int fontSize;
		glm::vec2 sizeLimits;
		mutable unsigned int lineCount;
		bool multiLine;

		float thickness;
		glm::vec4 textColor;
		float outlineThickness;
		glm::vec4 outlineColor;
		glm::vec2 outlineOffset;
		float outlineBlur;

		glm::vec2 padding;

		mutable std::vector<Line> lines;

		mutable size_t textIndexCount;

		Alignment textAlignment;
		AutoSizeMode autoSizeMode;

		mutable std::vector<glm::vec2> characterPositions;

		mutable std::vector<VertexPCT2D> vertices;
		mutable std::vector<GLuint> indices;
	};

	// Inline

	inline size_t Label::getTextIndexCount() const
	{
		return textIndexCount;
	}

	inline std::string &Label::getTextRef()
	{
		this->needsUpdate = true;
		return this->text;
	}
	
	inline const std::string &Label::getText() const
	{
		return this->text;
	}
	
	inline void Label::setText(const std::string &text)
	{
		this->text = text;
		this->needsUpdate = true;
	}
	
	inline const Font &Label::getFont() const
	{
		return *this->font;
	}
	
	inline void Label::setFont(const Font &font)
	{
		this->font = &font;
		this->needsUpdate = true;
	}
	
	inline unsigned int Label::getFontSize() const
	{
		return this->fontSize;
	}

	inline void Label::setFontSize(unsigned int fontSize)
	{
		this->fontSize = fontSize;
		this->needsUpdate = true;
	}
	
	inline unsigned int Label::getLineCount() const
	{
		return this->lineCount;
	}

	inline unsigned int Label::getLineHeight() const
	{
		return static_cast<unsigned int>(this->font->getLineHeight() * this->fontSize);
	}

	inline bool Label::isMultiLine() const
	{
		return this->multiLine;
	}

	inline void Label::setMultiLine(bool multiLine)
	{
		this->multiLine = multiLine;
		this->needsUpdate = true;
	}

	inline Label::Alignment Label::getTextAlignment() const
	{
		return this->textAlignment;
	}

	inline void Label::setTextAlignment(Label::Alignment textAligment)
	{
		this->textAlignment = textAligment;
		this-> needsUpdate = true;
	}

	inline bool Label::isAutoSizeMode(Label::AutoSizeMode autoSizeMode) const
	{
		#pragma warning(suppress : 4800)
		return static_cast<bool>(static_cast<char>(this->autoSizeMode) & static_cast<char>(autoSizeMode));
	}

	inline Label::AutoSizeMode Label::getAutoSizeMode() const
	{
		return this->autoSizeMode;
	}

	inline void Label::setAutoSizeMode(Label::AutoSizeMode autoSizeMode)
	{
		this->autoSizeMode = autoSizeMode;
	}
	
	inline float Label::getTextThickness() const
	{
		return this->thickness;
	}

	inline void Label::setTextThickness(float thickness)
	{
		this->thickness = thickness;
	}
	
	inline const glm::vec4 &Label::getTextColor() const
	{
		return this->textColor;
	}

	inline void Label::setTextColor(const glm::vec4 &color)
	{
		this->textColor = color;
	}
	
	inline float Label::getTextOutlineThickness() const
	{
		return this->outlineThickness;
	}

	inline void Label::setTextOutlineThickness(float outlineThickness)
	{
		this->outlineThickness = outlineThickness;
	}
	
	inline const glm::vec4 &Label::getTextOutlineColor() const
	{
		return this->outlineColor;
	}

	inline void Label::setTextOutlineColor(const glm::vec4 &outlineColor)
	{
		this->outlineColor = outlineColor;
	}
	
	inline const glm::vec2 &Label::getTextOutlineOffset() const
	{
		return this->outlineOffset;
	}

	inline void Label::setTextOutlineOffset(const glm::vec2 &outlineOffset)
	{
		this->outlineOffset = outlineOffset;
	}
	
	inline float Label::getTextOutlineBlur() const
	{
		return this->outlineBlur;
	}

	inline void Label::setTextOutlineBlur(float outlineBlur)
	{
		this->outlineBlur = outlineBlur;
	}

	inline const glm::vec2 Label::getPadding() const
	{
		return this->padding;
	}
	
	inline const std::vector<VertexPCT2D> &Label::getTextVertices() const
	{
		return this->vertices;
	}

	inline const std::vector<GLuint> &Label::getTextIndices() const
	{
		return this->indices;
	}
}