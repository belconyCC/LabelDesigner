#pragma once

#include <QString>
#include <QRect>
#include <vector>
#include <memory>

namespace LabelDesigner {

class LayoutCell;
using LayoutCellPtr = std::shared_ptr<LayoutCell>;

/**
 * @brief Layout engine for grid-based label layout
 * Manages the grid system and cell arrangement
 */
class LayoutEngine {
public:
    LayoutEngine();
    ~LayoutEngine();

    /**
     * @brief Initialize grid with rows and columns
     */
    void initializeGrid(int rows, int cols, int cellWidth, int cellHeight);

    /**
     * @brief Get grid dimensions
     */
    int getRowCount() const { return m_rows; }
    int getColumnCount() const { return m_columns; }

    /**
     * @brief Get cell dimensions
     */
    int getCellWidth() const { return m_cellWidth; }
    int getCellHeight() const { return m_cellHeight; }

    /**
     * @brief Set cell dimensions
     */
    void setCellDimensions(int width, int height);

    /**
     * @brief Get cell at position
     */
    LayoutCellPtr getCell(int row, int col) const;

    /**
     * @brief Add cell to layout
     */
    void addCell(LayoutCellPtr cell);

    /**
     * @brief Remove cell
     */
    void removeCell(int row, int col);

    /**
     * @brief Get all cells
     */
    const std::vector<LayoutCellPtr>& getCells() const { return m_cells; }

    /**
     * @brief Calculate actual cell boundary rectangle
     */
    QRect calculateCellBoundary(int row, int col, int rowSpan, int colSpan) const;

    /**
     * @brief Get layout as JSON
     */
    QString toJson() const;

    /**
     * @brief Load layout from JSON
     */
    void fromJson(const QString& json);

private:
    int m_rows;
    int m_columns;
    int m_cellWidth;
    int m_cellHeight;
    std::vector<LayoutCellPtr> m_cells;
};

} // namespace LabelDesigner
