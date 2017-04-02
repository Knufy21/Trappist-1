#include <Trappist-1\ui\widgets\Table.hpp>

namespace ui
{
	Table::Table(unsigned int rowCount, unsigned int columnCount, float rowSpacing, float columnSpacing)
		: BASE(), rowCount(0u), columnCount(columnCount), rowSpacing(rowSpacing), columnSpacing(columnSpacing), cellOrigin(0.0f, 0.0f)
	{
		elements.reserve(rowCount * columnCount);
		insertRow(0, rowCount);
	}

	unsigned int Table::getRowCount() const
	{
		return rowCount;
	}

	unsigned int Table::getColumnCount() const
	{
		return columnCount;
	}

	float Table::getRowSpacing() const
	{
		return rowSpacing;
	}

	float Table::getColumnSpacing() const
	{
		return columnSpacing;
	}

	const glm::vec2 &Table::getCellOrigin() const
	{
		return cellOrigin;
	}

	Table &Table::setRowCount(unsigned int count, bool reset)
	{
		if (reset)
			eraseAll();

		if (count < rowCount)
			popRow(rowCount - count);
		else
			appendRow(count - rowCount);

		return *this;
	}

	Table &Table::setColumnCount(unsigned int count, bool reset)
	{
		if (reset)
			eraseAll();

		if (count < columnCount)
			popColumn(columnCount - count);
		else
			appendColumn(count - columnCount);

		return *this;
	}

	Table &Table::eraseAll()
	{
		elements.clear();

		return *this;
	}

	Table &Table::insertRow(unsigned int rowIndex, unsigned int count)
	{
		rowCount += count;
		elements.insert(elements.begin() + rowIndex * columnCount, count * columnCount, nullptr);

		return *this;
	}

	Table &Table::eraseRow(unsigned int rowIndex, unsigned int count)
	{
		rowCount -= count;
		unsigned int eraseStart = rowIndex * columnCount;
		unsigned int eraseEnd = eraseStart + (count * columnCount) - 1;
		elements.erase(elements.begin() + eraseStart, elements.begin() + (eraseStart + eraseEnd));

		return *this;
	}

	Table &Table::appendRow(unsigned int count)
	{
		insertRow(rowCount - 1, count);

		return *this;
	}

	Table &Table::popRow(unsigned int count)
	{
		eraseRow(rowCount - 1, count);

		return *this;
	}

	Table &Table::insertColumn(unsigned int columnIndex, unsigned int count)
	{
		columnCount += count;
		for (auto it = elements.end(); it != elements.begin(); it -= columnCount)
			elements.insert(it + columnIndex, count, nullptr);

		return *this;
	}

	Table &Table::eraseColumn(unsigned int columnIndex, unsigned int count)
	{
		columnCount -= count;
		for (auto it = elements.end(); it != elements.begin(); it -= columnCount)
			elements.erase(it + columnIndex, it + (columnIndex + count));

		return *this;
	}

	Table &Table::appendColumn(unsigned int count)
	{
		insertColumn(columnCount - 1, count);

		return *this;
	}

	Table &Table::popColumn(unsigned int count)
	{
		eraseColumn(columnCount - 1, count);

		return *this;
	}

	Table &Table::insert(Widget &widget, unsigned int row, unsigned int column)
	{
		elements[row * columnCount + column] = &widget;

		return *this;
	}

	Table &Table::clear(unsigned int row, unsigned int column)
	{
		elements[row * columnCount + column] = nullptr;

		return *this;
	}

	Table &Table::setRowSpacing(float spacing)
	{
		rowSpacing = spacing;

		return *this;
	}

	Table &Table::setColumnSpacing(float spacing)
	{
		columnSpacing = spacing;

		return *this;
	}

	Table &Table::setCellOrigin(const glm::vec2 &origin)
	{
		cellOrigin = origin;

		return *this;
	}

	void Table::apply()
	{
		recalculate();
	}

	void Table::recalculate()
	{
		float *rowHeights = new float[rowCount]();
		float *columnWidths = new float[columnCount]();

		sf::FloatRect bounds;
		unsigned int rowIndex, columnIndex, cellIndex;
		for (rowIndex = 0; rowIndex < rowCount; ++rowIndex)
		{
			for (columnIndex = 0; columnIndex < columnCount; ++columnIndex)
			{
				cellIndex = rowIndex * columnCount + columnIndex;
				if (elements[cellIndex] != nullptr)
				{
					bounds = elements[cellIndex]->getGlobalBounds();

					//Check rows
					if (rowHeights[rowIndex] < bounds.height) //override only if old height is smaller than new
						rowHeights[rowIndex] = bounds.height;

					//Check Columns
					if (columnWidths[columnIndex] < bounds.width) //override only if old width is smaller than new
						columnWidths[columnIndex] = bounds.width;
				}
			}
		}

		//sum up widths and heights
		float sumWidth = 0.0f, sumHeight = 0.0f;
		for (rowIndex = 0; rowIndex < rowCount; ++rowIndex)
			sumHeight += rowHeights[rowIndex] + (rowIndex == rowCount - 1 ? 0 : rowSpacing);
		for (columnIndex = 0; columnIndex < columnCount; ++columnIndex)
			sumWidth += columnWidths[columnIndex] + (columnIndex == columnCount - 1 ? 0 : columnSpacing);

		setSize(glm::vec2(sumWidth, sumHeight));

		bounds = getGlobalBounds();
		sumWidth = sumHeight = 0;
		for (rowIndex = 0; rowIndex < rowCount; ++rowIndex)
		{
			for (columnIndex = 0; columnIndex < columnCount; ++columnIndex)
			{
				cellIndex = rowIndex * columnCount + columnIndex;
				//if (elements[cellIndex] != nullptr)
				//	elements[cellIndex]->setMargin(Margin::transformMargin(sf::Vector2f(bounds.left + sumWidth + columnWidths[columnIndex] * cellOrigin.x, bounds.top + sumHeight + rowHeights[rowIndex] * cellOrigin.y), getTargetSize(), elements[cellIndex]->getMargin()));
				//elements[cellIndex]->transformable.setPosition();
				sumWidth += columnWidths[columnIndex] + (columnIndex == columnCount - 1 ? 0 : columnSpacing);
			}
			sumHeight += rowHeights[rowIndex] + (rowIndex == rowCount - 1 ? 0 : rowSpacing);

			//if(rowIndex < rowCount) //keep number after loop
			sumWidth = 0.0f;
		}

		delete[] rowHeights;
		delete[] columnWidths;
	}

	//void Table::onPositionChanged()
	//{
	//	BASE::onPositionChanged();
	//	recalculate();
	//}

	void Table::performSubmittion(Renderer2D &renderer2d) const
	{
		BASE::performSubmittion(renderer2d);

		for (auto it = elements.begin(); it != elements.end(); ++it)
			(*it)->submit(renderer2d);
	}
}