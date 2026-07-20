#include "binding_info_element.h"
#include <QJsonDocument>
#include <QJsonObject>

namespace LabelDesigner {

BindingInfoElement::BindingInfoElement()
    : m_alignment(Qt::AlignLeft | Qt::AlignVCenter) {
    generateId();
    setName("Binding Info");
}

BindingInfoElement::BindingInfoElement(const QString& name)
    : m_alignment(Qt::AlignLeft | Qt::AlignVCenter) {
    generateId();
    setName(name);
}

std::map<QString, QVariant> BindingInfoElement::getProperties() const {
    std::map<QString, QVariant> props;
    props["id"] = m_id;
    props["name"] = m_name;
    props["json_path"] = m_jsonPath;
    props["default_value"] = m_defaultValue;
    props["format_string"] = m_formatString;
    props["font_family"] = m_font.family();
    props["font_size"] = m_font.pointSize();
    props["color"] = m_color.name();
    props["alignment"] = m_alignment;
    return props;
}

void BindingInfoElement::setProperty(const QString& key, const QVariant& value) {
    if (key == "json_path") {
        m_jsonPath = value.toString();
    } else if (key == "default_value") {
        m_defaultValue = value.toString();
    } else if (key == "format_string") {
        m_formatString = value.toString();
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

QString BindingInfoElement::toJson() const {
    QJsonObject obj;
    obj["id"] = m_id;
    obj["name"] = m_name;
    obj["type"] = "BindingInfo";
    obj["json_path"] = m_jsonPath;
    obj["default_value"] = m_defaultValue;
    obj["format_string"] = m_formatString;
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

void BindingInfoElement::fromJson(const QString& json) {
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    if (!doc.isObject()) return;
    
    QJsonObject obj = doc.object();
    m_id = obj["id"].toString();
    m_name = obj["name"].toString();
    m_jsonPath = obj["json_path"].toString();
    m_defaultValue = obj["default_value"].toString();
    m_formatString = obj["format_string"].toString();
    
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

std::unique_ptr<LabelElement> BindingInfoElement::clone() const {
    auto clone = std::make_unique<BindingInfoElement>();
    clone->m_id = m_id;
    clone->m_name = m_name;
    clone->m_jsonPath = m_jsonPath;
    clone->m_defaultValue = m_defaultValue;
    clone->m_formatString = m_formatString;
    clone->m_rect = m_rect;
    clone->m_font = m_font;
    clone->m_color = m_color;
    clone->m_alignment = m_alignment;
    return clone;
}

} // namespace LabelDesigner
