#include "layout_cell.h"
#include "label_element.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <algorithm>

namespace LabelDesigner {

LayoutCell::LayoutCell()
    : m_row(0), m_column(0), m_rowSpan(1), m_columnSpan(1),
      m_hasBorder(true), m_borderStyle("solid"), m_borderWidth(1) {
}

LayoutCell::LayoutCell(int row, int col, int rowSpan, int colSpan)
    : m_row(row), m_column(col), m_rowSpan(rowSpan), m_columnSpan(colSpan),
      m_hasBorder(true), m_borderStyle("solid"), m_borderWidth(1) {
}

void LayoutCell::removeElement(const QString& elementId) {
    auto it = std::find_if(m_elements.begin(), m_elements.end(),
        [&elementId](const LabelElementPtr& elem) {
            return elem->getId() == elementId;
        });
    if (it != m_elements.end()) {
        m_elements.erase(it);
    }
}

QString LayoutCell::toJson() const {
    QJsonObject obj;
    obj["row"] = m_row;
    obj["column"] = m_column;
    obj["row_span"] = m_rowSpan;
    obj["column_span"] = m_columnSpan;
    obj["boundary_x"] = m_boundary.x();
    obj["boundary_y"] = m_boundary.y();
    obj["boundary_width"] = m_boundary.width();
    obj["boundary_height"] = m_boundary.height();
    obj["has_border"] = m_hasBorder;
    obj["border_style"] = m_borderStyle;
    obj["border_width"] = m_borderWidth;

    QJsonArray elementsArray;
    for (const auto& element : m_elements) {
        elementsArray.append(element->getId());
    }
    obj["elements"] = elementsArray;

    QJsonDocument doc(obj);
    return QString::fromUtf8(doc.toJson());
}

void LayoutCell::fromJson(const QString& json) {
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    if (!doc.isObject()) return;
    
    QJsonObject obj = doc.object();
    m_row = obj["row"].toInt();
    m_column = obj["column"].toInt();
    m_rowSpan = obj["row_span"].toInt();
    m_columnSpan = obj["column_span"].toInt();
    
    m_boundary = QRect(
        obj["boundary_x"].toInt(),
        obj["boundary_y"].toInt(),
        obj["boundary_width"].toInt(),
        obj["boundary_height"].toInt()
    );
    
    m_hasBorder = obj["has_border"].toBool();
    m_borderStyle = obj["border_style"].toString();
    m_borderWidth = obj["border_width"].toInt();
}

} // namespace LabelDesigner
