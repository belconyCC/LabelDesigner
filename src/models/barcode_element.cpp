#include "barcode_element.h"
#include <QJsonDocument>
#include <QJsonObject>

namespace LabelDesigner {

BarcodeElement::BarcodeElement()
    : m_format(BarcodeFormat::Code128),
      m_barWidth(100),
      m_barHeight(50),
      m_showText(true) {
    generateId();
    setName("Barcode");
}

BarcodeElement::BarcodeElement(const QString& name)
    : m_format(BarcodeFormat::Code128),
      m_barWidth(100),
      m_barHeight(50),
      m_showText(true) {
    generateId();
    setName(name);
}

std::map<QString, QVariant> BarcodeElement::getProperties() const {
    std::map<QString, QVariant> props;
    props["id"] = m_id;
    props["name"] = m_name;
    props["format"] = static_cast<int>(m_format);
    props["content"] = m_content;
    props["bar_width"] = m_barWidth;
    props["bar_height"] = m_barHeight;
    props["show_text"] = m_showText;
    return props;
}

void BarcodeElement::setProperty(const QString& key, const QVariant& value) {
    if (key == "format") {
        m_format = static_cast<BarcodeFormat>(value.toInt());
    } else if (key == "content") {
        m_content = value.toString();
    } else if (key == "bar_width") {
        m_barWidth = value.toInt();
    } else if (key == "bar_height") {
        m_barHeight = value.toInt();
    } else if (key == "show_text") {
        m_showText = value.toBool();
    }
}

QString BarcodeElement::toJson() const {
    QJsonObject obj;
    obj["id"] = m_id;
    obj["name"] = m_name;
    obj["type"] = "Barcode";
    obj["format"] = static_cast<int>(m_format);
    obj["content"] = m_content;
    obj["bar_width"] = m_barWidth;
    obj["bar_height"] = m_barHeight;
    obj["show_text"] = m_showText;
    obj["rect_x"] = m_rect.x();
    obj["rect_y"] = m_rect.y();
    obj["rect_width"] = m_rect.width();
    obj["rect_height"] = m_rect.height();

    QJsonDocument doc(obj);
    return QString::fromUtf8(doc.toJson());
}

void BarcodeElement::fromJson(const QString& json) {
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    if (!doc.isObject()) return;
    
    QJsonObject obj = doc.object();
    m_id = obj["id"].toString();
    m_name = obj["name"].toString();
    m_format = static_cast<BarcodeFormat>(obj["format"].toInt());
    m_content = obj["content"].toString();
    m_barWidth = obj["bar_width"].toInt();
    m_barHeight = obj["bar_height"].toInt();
    m_showText = obj["show_text"].toBool();
    
    m_rect = QRect(
        obj["rect_x"].toInt(),
        obj["rect_y"].toInt(),
        obj["rect_width"].toInt(),
        obj["rect_height"].toInt()
    );
}

std::unique_ptr<LabelElement> BarcodeElement::clone() const {
    auto clone = std::make_unique<BarcodeElement>();
    clone->m_id = m_id;
    clone->m_name = m_name;
    clone->m_format = m_format;
    clone->m_content = m_content;
    clone->m_barWidth = m_barWidth;
    clone->m_barHeight = m_barHeight;
    clone->m_showText = m_showText;
    clone->m_rect = m_rect;
    return clone;
}

} // namespace LabelDesigner
