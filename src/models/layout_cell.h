#pragma once

#include <QString>
#include <QRect>
#include <vector>
#include <memory>

namespace LabelDesigner {

class LabelElement;
using LabelElementPtr = std::shared_ptr<LabelElement>;

/**
 * @brief Layout cell for grid layout
 * Represents a cell in the layout grid that can contain multiple elements
 */
class LayoutCell {
public:
    LayoutCell();
    explicit LayoutCell(int row, int col, int rowSpan = 1, int colSpan = 1);

    /**
     * @brief Get cell position
     */
    int getRow() const { return m_row; }
    int getColumn() const { return m_column; }

    /**
     * @brief Get cell span
     */
    int getRowSpan() const { return m_rowSpan; }
    int getColumnSpan() const { return m_columnSpan; }

    /**
     * @brief Set cell span
     */
    void setRowSpan(int span) { m_rowSpan = span; }
    void setColumnSpan(int span) { m_columnSpan = span; }

    /**
     * @brief Get cell boundary rectangle
     */
    const QRect& getBoundary() const { return m_boundary; }

    /**
     * @brief Set cell boundary
     */
    void setBoundary(const QRect& rect) { m_boundary = rect; }

    /**
     * @brief Add element to cell
     */
    void addElement(LabelElementPtr element) { m_elements.push_back(element); }

    /**
     * @brief Remove element from cell
     */
    void removeElement(const QString& elementId);

    /**
     * @brief Get all elements in cell
     */
    const std::vector<LabelElementPtr>& getElements() const { return m_elements; }

    /**
     * @brief Check if has border
     */
    bool hasBorder() const { return m_hasBorder; }

    /**
     * @brief Set border visibility
     */
    void setBorder(bool visible) { m_hasBorder = visible; }

    /**
     * @brief Get border style (solid, dashed, dotted)
     */
    const QString& getBorderStyle() const { return m_borderStyle; }

    /**
     * @brief Set border style
     */
    void setBorderStyle(const QString& style) { m_borderStyle = style; }

    /**
     * @brief Get border width
     */
    int getBorderWidth() const { return m_borderWidth; }

    /**
     * @brief Set border width
     */
    void setBorderWidth(int width) { m_borderWidth = width; }

    /**
     * @brief Serialize cell
     */
    QString toJson() const;

    /**
     * @brief Deserialize cell
     */
    void fromJson(const QString& json);

private:
    int m_row;
    int m_column;
    int m_rowSpan;
    int m_columnSpan;
    QRect m_boundary;
    std::vector<LabelElementPtr> m_elements;
    bool m_hasBorder;
    QString m_borderStyle;
    int m_borderWidth;
};

using LayoutCellPtr = std::shared_ptr<LayoutCell>;

} // namespace LabelDesigner
