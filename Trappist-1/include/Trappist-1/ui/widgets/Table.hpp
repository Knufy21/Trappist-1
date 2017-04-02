#pragma once

#include "Trappist-1\ui\widgets\Widget.hpp"

namespace ui
{
	class Table : public Widget
	{
		using BASE = Widget;
	public:
		//Table(unsigned int rowCount = 0u, unsigned int columnCount = 0u, float rowSpacing = 0.0f, float columnSpacing = 0.0f);
		Table(unsigned int rowCount = 0u, unsigned int columnCount = 0u, float rowSpacing = 0.0f, float columnSpacing = 0.0f);

		unsigned int getRowCount() const;
		unsigned int getColumnCount() const;
		float getRowSpacing() const;
		float getColumnSpacing() const;
		const glm::vec2 &getCellOrigin() const;

		Table &setRowCount(unsigned int count, bool reset);
		Table &setColumnCount(unsigned int count, bool reset);
		Table &eraseAll();
		Table &insertRow(unsigned int rowIndex, unsigned int count = 1u);
		Table &eraseRow(unsigned int rowIndex, unsigned int count = 1u);
		Table &appendRow(unsigned int count = 1u);
		Table &popRow(unsigned int count = 1u);
		Table &insertColumn(unsigned int columnIndex, unsigned int count = 1u);
		Table &eraseColumn(unsigned int columnIndex, unsigned int count = 1u);
		Table &appendColumn(unsigned int count = 1u);
		Table &popColumn(unsigned int count = 1u);
		Table &setRowSpacing(float spacing);
		Table &setColumnSpacing(float spacing);
		Table &setCellOrigin(const glm::vec2 &origin);
		Table &insert(Widget &widget, unsigned int row, unsigned int column);
		Table &clear(unsigned int row, unsigned int column);
		void apply();

	protected:
		virtual void performSubmittion(Renderer2D &renderer2d) const override;
		//virtual void onPositionChanged() override;

		void recalculate();
	private:
		unsigned int rowCount, columnCount;
		float rowSpacing, columnSpacing;
		glm::vec2 cellOrigin;
		std::vector<Widget*> elements;
	};
}