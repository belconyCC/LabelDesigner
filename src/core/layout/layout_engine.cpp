#include "layout_engine.h"
#include "src/models/layout_cell.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <algorithm>

namespace LabelDesigner {

LayoutEngine::LayoutEngine()
    : m_rows(0), m_columns(0), m_cellWidth(0), m_cellHeight(0) {
}

LayoutEngine::~LayoutEngine() {
    m_cells.clear();
}

void LayoutEngine::initializeGrid(int rows, int cols, int cellWidth, int cellHeight) {
    m_rows = rows;
    m_columns = cols;
    m_cellWidth = cellWidth;
    m_cellHeight = cellHeight;
    m_cells.clear();
    
    // Create default grid cells
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            auto cell = std::make_shared<LayoutCell>(row, col);
            QRect boundary = calculateCellBoundary(row, col, 1, 1);
            cell->setBoundary(boundary);
            m_cells.push_back(cell);
        }
    }
}

void LayoutEngine::setCellDimensions(int width, int height) {
    m_cellWidth = width;
    m_cellHeight = height;
    
    // Update all cell boundaries
    for (auto& cell : m_cells) {
        QRect boundary = calculateCellBoundary(
            cell->getRow(),
            cell->getColumn(),
            cell->getRowSpan(),
            cell->getColumnSpan()
        );
        cell->setBoundary(boundary);
    }
}

LayoutCellPtr LayoutEngine::getCell(int row, int col) const {
    for (const auto& cell : m_cells) {
        if (cell->getRow() == row && cell->getColumn() == col) {
            return cell;
        }
    }
    return nullptr;
}

void LayoutEngine::addCell(LayoutCellPtr cell) {
    if (cell) {
        m_cells.push_back(cell);
    }
}

void LayoutEngine::removeCell(int row, int col) {
    auto it = std::find_if(m_cells.begin(), m_cells.end(),
        [row, col](const LayoutCellPtr& cell) {
            return cell->getRow() == row && cell->getColumn() == col;
        });
    
    if (it != m_cells.end()) {
        m_cells.erase(it);
    }
}

QRect LayoutEngine::calculateCellBoundary(int row, int col, int rowSpan, int colSpan) const {
    int x = col * m_cellWidth;
    int y = row * m_cellHeight;
    int width = colSpan * m_cellWidth;
    int height = rowSpan * m_cellHeight;
    return QRect(x, y, width, height);
}

QString LayoutEngine::toJson() const {
    QJsonObject root;
    root["rows"] = m_rows;
    root["columns"] = m_columns;
    root["cell_width"] = m_cellWidth;
    root["cell_height"] = m_cellHeight;
    
    QJsonArray cellsArray;
    for (const auto& cell : m_cells) {
        QJsonDocument doc = QJsonDocument::fromJson(cell->toJson().toUtf8());
        if (doc.isObject()) {
            cellsArray.append(doc.object());
        }
    }
    root["cells"] = cellsArray;

    QJsonDocument doc(root);
    return QString::fromUtf8(doc.toJson());
}

void LayoutEngine::fromJson(const QString& json) {
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    if (!doc.isObject()) return;
    
    QJsonObject root = doc.object();
    m_rows = root["rows"].toInt();
    m_columns = root["columns"].toInt();
    m_cellWidth = root["cell_width"].toInt();
    m_cellHeight = root["cell_height"].toInt();
    
    m_cells.clear();
    QJsonArray cellsArray = root["cells"].toArray();
    for (const auto& cellValue : cellsArray) {
        auto cell = std::make_shared<LayoutCell>();
        cell->fromJson(QString::fromUtf8(QJsonDocument(cellValue.toObject()).toJson()));
        m_cells.push_back(cell);
    }
}

} // namespace LabelDesigner
