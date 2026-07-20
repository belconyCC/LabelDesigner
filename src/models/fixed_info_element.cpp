#include "fixed_info_element.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace LabelDesigner {

FixedInfoElement::FixedInfoElement()
    : m_alignment(Qt::AlignLeft | Qt::AlignVCenter) {
    generateId();
    setName("Fixed Info");
}

FixedInfoElement::FixedInfoElement(const QString& name)
    : m_alignment(Qt::AlignLeft | Qt::AlignVCenter) {
    generateId();
    setName(name);
}

std::map<QString, QVariant> FixedInfoElement::getProperties() const {
    std::map<QString, QVariant> props;
    props["id"] = m_id;
    props["name"] = m_name;
    props["text"] = m_text;
    props["font_family"] = m_font.family();
    props["font_size"] = m_font.pointSize();
    props["color"] = m_color.name();
    props["alignment"] = m_alignment;
    return props;
}

void FixedInfoElement::setProperty(const QString& key, const QVariant& value) {
    if (key == "text") {
        m_text = value.toString();
    } else if (key == "font_family") {
        m_font.setFamily(value.toString());
    } else if (key == "font_size") {
        m_font.setPointSize(value.toInt());
    } else if (key == "color") {
        m_color = QColor(value.toString());
    } else if (key == "alignment") {
        m_alignment = value.toInt();
    }
}

QString FixedInfoElement::toJson() const {
    QJsonObject obj;
    obj["id"] = m_id;
    obj["name"] = m_name;
    obj["type"] = "FixedInfo";
    obj["text"] = m_text;
    obj["rect_x"] = m_rect.x();
    obj["rect_y"] = m_rect.y();
    obj["rect_width"] = m_rect.width();
    obj["rect_height"] = m_rect.height();
    
    QJsonObject font;
    font["family"] = m_font.family();
    font["size"] = m_font.pointSize();
    font["bold"] = m_font.bold();
    font["italic"] = m_font.italic();
    obj["font"] = font;
    
    obj["color"] = m_color.name();
    obj["alignment"] = m_alignment;

    QJsonDocument doc(obj);
    return QString::fromUtf8(doc.toJson());
}

void FixedInfoElement::fromJson(const QString& json) {
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    if (!doc.isObject()) return;
    
    QJsonObject obj = doc.object();
    m_id = obj["id"].toString();
    m_name = obj["name"].toString();
    m_text = obj["text"].toString();
    
    m_rect = QRect(
        obj["rect_x"].toInt(),
        obj["rect_y"].toInt(),
        obj["rect_width"].toInt(),
        obj["rect_height"].toInt()
    );
    
    QJsonObject fontObj = obj["font"].toObject();
    m_font.setFamily(fontObj["family"].toString());
    m_font.setPointSize(fontObj["size"].toInt());
    m_font.setBold(fontObj["bold"].toBool());
    m_font.setItalic(fontObj["italic"].toBool());
    
    m_color = QColor(obj["color"].toString());
    m_alignment = obj["alignment"].toInt();
}

std::unique_ptr<LabelElement> FixedInfoElement::clone() const {
    auto clone = std::make_unique<FixedInfoElement>();
    clone->m_id = m_id;
    clone->m_name = m_name;
    clone->m_text = m_text;
    clone->m_rect = m_rect;
    clone->m_font = m_font;
    clone->m_color = m_color;
    clone->m_alignment = m_alignment;
    return clone;
}

} // namespace LabelDesigner
